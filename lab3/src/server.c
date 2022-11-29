#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>//里面包含了文件I/O的宏定义
#define FIFO0 "/home/superior/lab3/object/fifo0"
#define FIFO1 "/home/superior/lab3/object/fifo1"
#define N 2//client的个数
int main(){
    int fd,i;
    pid_t pid;
    char s1[]="HELLO Client1!\n";//创建字符数组(字符串)
    char s2[]="HELLO Client2!\n";//创建字符数组(字符串)
    char buffer[80];
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
            unlink(FIFO1);//如果有FIFO0文件,先删除(belong to unistd,使其连接数-1,当连接数为1就删除)
            mkfifo(FIFO1,0666);//使每个用户都有读写权限
            fd=open(FIFO1,O_WRONLY);//来自于fcntl.h
            write(fd,s2,sizeof(s2));//管道名,字符串指针,大小
            close(fd); 
            printf("[in proc %d]:chars has been written to FIFO[1]!\n",getpid());

            fd=open(FIFO1,O_RDONLY);//来自于fcntl.h
            read(fd,buffer,80);
            printf("[in proc %d]:Server received from Client2\n%s\n",getpid(),buffer);
            close(fd); 
            
            exit(EXIT_SUCCESS);
        }
    }
    printf("should not be here!");
 
    return 0;
}