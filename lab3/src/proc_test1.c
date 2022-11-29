#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//头文件
#include <wait.h>
int main(void)
{
	pid_t pid;
	int bound = 100;

	if((pid=fork())==-1){//在这之后进程隐式分裂,子进程和父进程共用代码
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0){//子进程执行
		puts("This is child proc");
		bound += 200;
		printf("pid=%d,ppid=%d\n",getpid(),getppid());
		printf("bound=%d\n\n",bound);
		execl("/usr/bin/firefox", "firefox", "www.baidu.com", NULL);
		printf("ERROR:program should not be here!");
		exit(EXIT_SUCCESS);
	}
	else{//父进程执行
		puts("This is parent proc");
		bound += 800;
		printf("pid=%d,ppid=%d\n",getpid(),getppid());
		printf("bound=%d\n\n",bound);
		//这里必须指定home而不是~
		//**这块不知道参数以什么方式传给自己写的程序
		execl("/home/superior/lab3/object/hello.o", "hello.o",NULL, NULL);
		exit(EXIT_SUCCESS);
	}

}