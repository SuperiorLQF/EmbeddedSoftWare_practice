/***********<读优先>*****************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#include<string.h>

#include<pthread.h>
#include<semaphore.h>
//https://blog.csdn.net/a04171283/article/details/115451949?ops_request_misc=&request_id=&biz_id=102&utm_term=%E8%AF%BB%E8%80%85%E4%BC%98%E5%85%88&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-115451949.nonecase&spm=1018.2226.3001.4187

/***********<读函数>*****************/
void reader()
{
    // pend(readercount_mutex);
    // if(readercount == 0) 
    //     pend(writer_mutex);//获得写锁
    // //第一个读者需占据写锁
    // readercount++;
    // post(readercount_mutex);
    // //reading the shared file
    // pend(readercount_mutex);
    // readercount--;
    // if(readercount == 0) post(writer_mutex);
    // //最后一个读者释放写锁
    // post(readercount_mutex);

}
typedef struct thread_args{
    int a;
    int b;
}thread_args,*p_thargs;
/***********<写函数>*****************/
void *writer(p_thargs p1){
    // pend(writer_mutex);//获得写锁

    // //wirting the shared file
    printf("ok");
    printf("the num is\n%d\n%d\n",p1->a,p1->b);
    // post(writer_mutex);
}
/***********<主程序>*****************/
int *main(){
    int i=3;
    int j=5;
    p_thargs p1;
    p1=(p_thargs)malloc(sizeof(thread_args));
    p1->a=i;
    p1->b=j;
    pthread_t writernum[10],readernum[10];
    pthread_create(&writernum[0],NULL,(void *)writer,p1);//创建线程
    sleep(1);
    return 0;
}