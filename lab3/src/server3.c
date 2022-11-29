#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
//里面包含了文件I/O的宏定义
#include <string.h>
#define FIFO0R "/home/lqf/lab3/object/fifo0r"
#define FIFO0W "/home/lqf/lab3/object/fifo0w"
#define FIFO1R "/home/lqf/lab3/object/fifo1r"
#define FIFO1W "/home/lqf/lab3/object/fifo1w"
#define N 2 
// client的个数
//双工注意点:需要open和close需要快开快关,否则会阻塞
int main()
{
    int fd, i;
    pid_t pid;
    int nonnamepip1[2];//将输入读取并发送给发送进程1
    int nonnamepip2[2];//将输入读取并发送给发送进程2
    pipe(nonnamepip1);//创建无名管道
    pipe(nonnamepip2);//创建无名管道
    for (i = 0; i < N; i++)
    {
        pid = fork(); //进程分裂
        if (pid == 0)
            break; //如果是子进程就退出,防止子进程recursive create process
    }
    if (pid != 0){ //父进程
        while (1)
        {
            int n;
            char str[80];
            scanf("%d\n", &n);
            fgets(str, 80, stdin);//通过无名管道将读取数据发送给对应数据发送进程
            if(n==0){
                printf("[in proc %d] [Server]:send chars to nonnamepipe1\n",getpid());
                write(nonnamepip1[1],str,80);    
            }
            else{
                printf("[in proc %d] [Server]:send chars to nonnamepipe2\n",getpid());
                write(nonnamepip2[1],str,80);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    { //一系列子进程通过i来区分
        if (i == 0)
        { // CLinet1
            int fdW, fdR;
            char str[80];
            //删除读管道
            unlink(FIFO0R);
            unlink(FIFO0W);
            //创建读写管道
            mkfifo(FIFO0R, 0666);
            mkfifo(FIFO0W, 0666);
            //进程分裂:子进程0分裂出00和01------------------
            pid = fork();
            if (pid == 0)
            { //子进程00
                while (1)
                {
                    // printf("input chars for Client1\n");
                    // fgets(str,80,stdin);
                    read(nonnamepip1[0],str,80);
                    printf("[in proc %d] [Server]:send chars to [Client1]\n", getpid());
                    fdW = open(FIFO0W, O_WRONLY); //来自于fcntl.h
                    write(fdW, str, sizeof(str)); //管道名,字符串指针,大小
                    close(fdW);
                }
                exit(EXIT_SUCCESS);
            }
            else
            { //读进程管理读管道
                while (1)
                {
                    fdR = open(FIFO0R, O_RDONLY); //来自于fcntl.h
                    read(fdR, str, 80);
                    close(fdR);
                    printf("[in proc %d] [Server]:receive chars from [Client1]\n%s\n", getpid(), str);
                }
                exit(EXIT_SUCCESS);
            }
            printf("should not be here!");
        }
        /***************************************/
        else if (i == 1)
        { // CLinet2
            int fdW, fdR;
            char str[80];
            unlink(FIFO1R); //删除读管道
            unlink(FIFO1W); //删除写管道
            //创建读写管道
            mkfifo(FIFO1R, 0666);
            mkfifo(FIFO1W, 0666);
            //打开读写管道

            //进程分裂------------------
            pid = fork();
            if (pid == 0)
            { //写进程管理写管道
                while (1)
                {

                    // printf("input chars for Client2\n");
                    // fgets(str,80,stdin);
                    read(nonnamepip2[0],str,80);
                    printf("[in proc %d] [Server]:send chars to [Client2]\n", getpid());
                    fdW = open(FIFO1W, O_WRONLY); //来自于fcntl.h
                    write(fdW, str, sizeof(str)); //管道名,字符串指针,大小
                    close(fdW);
                }
                exit(EXIT_SUCCESS);
            }
            else
            { //读进程管理读管道
                while (1)
                {
                    fdR = open(FIFO1R, O_RDONLY); //来自于fcntl.h
                    read(fdR, str, 80);
                    close(fdR);
                    printf("[in proc %d] [Server]:receive chars from [Client2]\n%s\n", getpid(), str);
                }
                exit(EXIT_SUCCESS);
            }

            printf("should not be here!");
        }
    }
    printf("should not be here!");

    return 0;
}