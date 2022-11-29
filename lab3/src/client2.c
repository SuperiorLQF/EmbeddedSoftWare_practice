#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#define FIFO1 "/home/superior/lab3/object/fifo1"
int main(){
    //等待管道创建完毕
    int fd;
    int nonnamepip[2];
    char buffer[80];
    pid_t pid;
    pipe(nonnamepip);//创建无名管道

    if((pid=fork())==0){//子进程
        fd=open(FIFO1,O_RDONLY);//打开有名管道
        read(fd,buffer,80);//管道名,存储块指针,存储快大小
        close(fd);//关闭有名管道
        printf("[in proc %d] [Client2]:send chars to nonnamepipe\n",getpid());
        write(nonnamepip[1],buffer,80);//指定了1发送0接受,这是规定好的,否则会发送失败
        exit(EXIT_SUCCESS);
    }
    else{//主进程
        //wait(NULL);//会自动同步
        char s[]="Client2 has received!\n";
        read(nonnamepip[0],buffer,80);
        printf("[in proc %d] [Client2]:receive chars from nonnamepipe\n%s\n",getpid(),buffer);
        /****/
        wait(NULL);
        fd=open(FIFO1,O_WRONLY);//打开有名管道  
        write(fd,s,sizeof(s));
        close(fd);//关闭有名管道
        exit(EXIT_SUCCESS);
    }
    printf("should not be here!\n");
    return 0;
}