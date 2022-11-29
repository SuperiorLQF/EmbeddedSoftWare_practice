//单个父进程创建多个子进程示例
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#define N 3//创建子进程个数
int main(){
    pid_t pid;
    int i,status,pid_zombie;
    int num=200;//初始值200,用来验证进程/线程之间数据共享
    for(i=0;i<N;i++){
        pid=fork();//连续创建三个子进程,从这时刻开始进程分裂(拷贝副本)------

        if(pid==0){
            break;//用来使产生的子进程退出循环,防止子进程创建新的子进程
        }
    }
    if(pid>0){//父进程执行
        printf("parent pid %d\n sleeping..\n",getpid());//getpid()获得本进程的pid
        //捕获结束的三个子进程
        for(i=0;i<N;i++){
            pid_zombie=wait(&status);//阻塞等待直到子进程退出
            printf("child proc(%d) has finished\n",pid_zombie);
        }
        exit(EXIT_SUCCESS);//父进程退出
    }
    else if(pid==0){
        if(i==0){//通过退出的i值来表征子进程
            printf("child proc(%d) No.%d\n",getpid(),i);
            //子进程0的任务主体
            pid=vfork();//子进程0强制等待其子进程先执行完毕.进程再次分裂----
            if(pid==0){//子进程0的子进程先执行
                printf("[in proc %d]This is child of child proc NO.0\n",getpid());
                num+=20;
                printf("[in proc %d]num=%d\n",getpid(),num);
                exit(EXIT_SUCCESS);//子进程0的子进程退出
            }
            else{//子进程0执行
                printf("[in proc %d]child of child proc NO.0 has finished\n",getpid());
                num+=20;
                printf("[in proc %d]num=%d\n",getpid(),num);
            }
            exit(EXIT_SUCCESS);
        }
        
        else if(i==1){//通过退出的i值来表征子进程
            printf("child proc(%d) No.%d\n",getpid(),i);
            //子进程1做的事情
            num+=10;
            printf("[in proc %d]num=%d\n",getpid(),num);
            exit(EXIT_SUCCESS);
        }
        
        else if(i==2){//通过退出的i值来表征子进程
            printf("child proc(%d) No.%d\n",getpid(),i);
            //子进程2做的事情
            num+=15;
            printf("[in proc %d]num=%d\n",getpid(),num);
            exit(EXIT_SUCCESS);//退出后为zombie状态,被wait捕获,一个wait捕获一个zombie

        }
    }
    return 0;
}
