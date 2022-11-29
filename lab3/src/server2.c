#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>//里面包含了文件I/O的宏定义
#include<string.h>
#define FIFO0 "/home/superior/lab3/object/fifo0"
#define FIFO1R "/home/superior/lab3/object/fifo1r"
#define FIFO1W "/home/superior/lab3/object/fifo1w"
#define N 2//client的个数
//双工注意点:需要open和close需要快开快关,否则会阻塞
int main(){
    int fd,i;
    pid_t pid;
    char s1[]="HELLO Client1!\n";//创建字符数组(字符串)
    for(i=0;i<N;i++){
        pid=fork();//进程分裂
        if(pid==0)
            break;//如果是子进程就退出,防止子进程recursive create process
    }

    if(pid!=0){//父进程
        for(i=0;i<N;i++){
            wait(NULL);
        }
        exit(EXIT_SUCCESS);
    }
    else{//一系列子进程通过i来区分
        if(i==0){//Client1
            unlink(FIFO0);//如果有FIFO0文件,先删除(belong to unistd,使其连接数-1,当连接数为1就删除)
            mkfifo(FIFO0,0666);//使每个用户都有读写权限
            fd=open(FIFO0,O_WRONLY);//来自于fcntl.h
            write(fd,s1,sizeof(s1));//管道名,字符串指针,大小
            printf("[in proc %d]:chars has been written to FIFO[0]!\n",getpid());
            close(fd);
            exit(EXIT_SUCCESS);
        }
        else if(i==1){//CLinet2
            int fdW,fdR;
            char str[80];
            unlink(FIFO1R);//删除读管道
            unlink(FIFO1W);//删除写管道
            //创建读写管道
            mkfifo(FIFO1R,0666);
            mkfifo(FIFO1W,0666);
            //打开读写管道
            
            //进程分裂------------------
            pid=fork();
            if(pid==0){//写进程管理写管道
                while(1){
                    printf("please input\n");
                    fgets(str,80,stdin);
                    printf("[in proc %d] [Server]:send chars to [Client2]\n",getpid());
                    fdW=open(FIFO1W,O_WRONLY);//来自于fcntl.h
                    write(fdW,str,sizeof(str));//管道名,字符串指针,大小
                    close(fdW);
                       
                }
                exit(EXIT_SUCCESS);
            }
            else{//读进程管理读管道
                while(1){
                    fdR=open(FIFO1R,O_RDONLY);//来自于fcntl.h
                    read(fdR,str,80);
                    close(fdR);
                    printf("[in proc %d] [Server]:receive chars from [Client2]\n%s\n",getpid(),str);    

                }
                exit(EXIT_SUCCESS);                
            }
            
            printf("should not be here!");
        }
    }
    printf("should not be here!");
 
    return 0;
}