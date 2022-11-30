/***********<写优先>*****************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<wait.h>
#include<string.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdint.h>
/***********<全局变量>*****************/
struct timespec startT;
typedef struct thread_args{
    int a;
    int b;
    int rw_num;
}thread_args,*p_thargs;
static int readercount=0;//读者计数变量，初始化为0
static int writercount=0;//写者计数变量，初始化为0
static pthread_mutex_t  readercount_mutex,
                        writercount_mutex,
                        reader_mutex,
                        writer_mutex;
static sem_t datarecv_sem;
/***********<读线程函数>*****************/
void *reader(p_thargs p1);
/***********<写线程函数>*****************/
void *writer(p_thargs p1);
/***********<主程序>*****************/
int main(){
    clock_gettime(CLOCK_MONOTONIC,&startT);//获取初始时间
    //创建线程参数结构指针
    int i=3;
    int j=5;
    int k=0;
    p_thargs p1;
    p1=(p_thargs)malloc(sizeof(thread_args));
    p1->a=i;
    p1->b=j;
    p1->rw_num=k;
    
    //创建互斥锁
    pthread_mutex_init(&readercount_mutex,NULL);
    pthread_mutex_init(&writer_mutex,NULL);
    
    //创建数据传输同步信号量
    sem_init(&datarecv_sem,0,0);//初始值为0
    
    //创建线程
    pthread_t writernum[10],readernum[10];
    for(k=0;k<5;k++){
        p1->rw_num=k;//为传递参数赋值
        pthread_create(&writernum[k],NULL,(void *)writer,p1);//创建写线程
        //等待信号接受数据完毕
        sem_wait(&datarecv_sem);
    }

    for(k=0;k<10;k++){
        p1->rw_num=k;//为传递参数赋值
        pthread_create(&readernum[k],NULL,(void *)reader,p1);//创建读线程
        //等待信号接受数据完毕
        sem_wait(&datarecv_sem);
    }
    
    for(k=5;k<10;k++){
        p1->rw_num=k;//为传递参数赋值
        pthread_create(&writernum[k],NULL,(void *)writer,p1);//创建写线程
        //等待信号接受数据完毕
        sem_wait(&datarecv_sem);
    }

    for(k=0;k<10;k++){
        pthread_join(readernum[k],NULL);   //回收线程
        pthread_join(writernum[k],NULL);   //回收线程       
    } 
    return 0;
}
/***********<读线程函数>*****************/
void *reader(p_thargs p1)
{   

    //信号同步接受
    thread_args thag1=*p1;
    //接收完毕释放信号
    sem_post(&datarecv_sem);
    
    pthread_mutex_lock(&reader_mutex);
    pthread_mutex_lock(&readercount_mutex);
    if(readercount == 0) 
        pthread_mutex_lock(&writer_mutex);  //第一个读者需占据写锁
    readercount++;
    pthread_mutex_unlock(&readercount_mutex);
    pthread_mutex_unlock(&reader_mutex);
   
    //读文件操作
    struct timespec endT;
    clock_gettime(CLOCK_MONOTONIC,&endT);
    uint32_t delta_ms = (endT.tv_sec - startT.tv_sec) * 1000 + (endT.tv_nsec - startT.tv_nsec) / 1000000;
    printf("[%d ms][reader %d]:reading...\n",delta_ms,thag1.rw_num);  
    sleep(1);
    
    //进入计数临界区
    pthread_mutex_lock(&readercount_mutex);
    readercount--;
    
    if(readercount == 0) 
        pthread_mutex_unlock(&writer_mutex); //最后一个读者释放写锁
    
    pthread_mutex_unlock(&readercount_mutex);
    //退出计数临界区

}
/***********<写线程函数>*****************/
void *writer(p_thargs p1)
{   
    //信号同步接受
    thread_args thag1=*p1;
    //接收完毕释放信号
    sem_post(&datarecv_sem);

    //进入写计数临界区//
    pthread_mutex_lock(&writercount_mutex);    
    if(writercount==0)
        pthread_mutex_lock(&reader_mutex);
    writercount++;
    pthread_mutex_unlock(&writercount_mutex); 
    //退出写计数临界区//       
    
    //进入写临界区//
    pthread_mutex_lock(&writer_mutex);//获得写锁，否则一直阻塞等待
    
    //写文件操作
    struct timespec endT;
    clock_gettime(CLOCK_MONOTONIC,&endT);
    uint32_t delta_ms = (endT.tv_sec - startT.tv_sec) * 1000 + (endT.tv_nsec - startT.tv_nsec) / 1000000;
    printf("[%d ms][writer %d]:wrting...\n",delta_ms,thag1.rw_num); 
    
    //可以添加一些实际写文件，例如写txt
    sleep(1);
    //释放写锁
    pthread_mutex_unlock(&writer_mutex);
    //退出写临界区//

    //进入写计数临界区//
    pthread_mutex_lock(&writercount_mutex);
    writercount--;    
    if(writercount==0)
        pthread_mutex_unlock(&reader_mutex);
    pthread_mutex_unlock(&writercount_mutex); 
    //退出写计数临界区//

    //退出线程
    pthread_exit(NULL);
}