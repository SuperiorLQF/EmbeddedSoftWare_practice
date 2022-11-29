#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#define FIFO0 "/home/superior/lab3/object/fifo0"
int main(){
    //等待管道创建完毕
    int fd;
    int nonnamepip[2];
    char buffer[80];
    pid_t pid;
    pipe(nonnamepip);//创建无名管道
    if((pid=fork())==0){//子进程
        fd=open(FIFO0,O_RDONLY);
        read(fd,buffer,80);//管道名,存储块指针,存储快大小
        printf("[in proc %d]:THE chars received in Client1 has been send by nonnamepipe\n",getpid());
        write(nonnamepip[1],buffer,80);//指定了1发送0接受,这是规定好的,否则会发送失败
        close(fd);
        exit(EXIT_SUCCESS);
    }
    else{//主进程
        //wait(NULL);//会自动同步
        read(nonnamepip[0],buffer,80);
        printf("[in proc %d]:THE chars received in Client1 is\n%s\n",getpid(),buffer);
        exit(EXIT_SUCCESS);
    }
    printf("should not be here!\n");
    return 0;
}