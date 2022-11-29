#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>
void sighandler(int signum);
int main(){
    pid_t pid;
    if((pid=fork())==-1){//进程分裂
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){//子进程//简单的握手机制,保证子进程已经被创建,主进程再给子进程发信号.
    signal(SIGINT,sighandler);//类似提前绑定好signal处理函数
    printf("[in proc %d]:child 子进程创建成功\n",getpid());
    printf("[in proc %d]:send signal to pid=%d\n...\n",getpid(),getppid());//先向主进程发送信号
    kill(getppid(),SIGINT);//发送创建成功信号,同步
    pause();//在pause之前需要绑定好,不然会出错
    printf("[in proc %d]:收到主进程信号\n",getpid());    
    exit(EXIT_SUCCESS);
    }
    else{//主进程
    signal(SIGINT,sighandler); 
    printf("[in proc %d]:parent\n",getpid());
    pause();  
    printf("[in proc %d]:收到子进程已经被创建成功\n",getpid());
    printf("[in proc %d]:send signal to pid=%d\n...\n",getpid(),pid);//向子进程发送信号
    kill(pid,SIGINT);
    wait(NULL);
    exit(EXIT_SUCCESS);
    }
    printf("OVER!");
}
void sighandler(int signum){
    if(signum==SIGALRM)
        printf("[in proc %d]:SIGALRM is captured\n",getpid());
    else if(signum==SIGINT) 
        printf("[in proc %d]:SIGINT is captured\n",getpid());
    else if (signum==SIGTSTP)
        printf("[in proc %d]:SIGTSTP is captured\n",getpid());
}