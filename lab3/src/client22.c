#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#include<string.h>
#define FIFO1W "/home/lqf/lab3/object/fifo1r"
#define FIFO1R "/home/lqf/lab3/object/fifo1w"
int main(){
    //等待管道创建完毕
    int fdW,fdR,i;
    int nonnamepip[2];
    char buffer[80];
    pid_t pid;
    pipe(nonnamepip);//创建无名管道

    
    for(i=0;i<2;i++){//创建2个子进程
        pid=fork();
        if(pid==0)
            break;
    }
    if(pid!=0){//主进程,用来显示接受的消息
        while(1){
            read(nonnamepip[0],buffer,80);
            printf("[in proc %d] [Client2]:receive chars from nonnamepipe\n%s\n",getpid(),buffer);
        }
    }
    else{//两个子进程,用来发送和接受消息
        if(i==0){//读管道进程
            while(1){
                //打开读写管道
                fdR=open(FIFO1R,O_RDONLY);//来自于fcntl.h
                read(fdR,buffer,80);
                close(fdR); 
                printf("[in proc %d] [Client2]:send chars to nonnamepipe\n",getpid());
                write(nonnamepip[1],buffer,80);//指定了1发送0接受,这是规定好的,否则会发送失败          
            }
            exit(EXIT_SUCCESS);     
        }
        else{//发送进程
            while(1){
                fgets(buffer,80,stdin);
                printf("[in proc %d] [Client2]:send chars to [Server]\n",getpid());
                fdW=open(FIFO1W,O_WRONLY);//来自于fcntl.h   
                write(fdW,buffer,sizeof(buffer));//管道名,字符串指针,大小
                close(fdW); 
            } 
            exit(EXIT_SUCCESS);
        }
    }

    printf("should not be here!\n");
    return 0;
}