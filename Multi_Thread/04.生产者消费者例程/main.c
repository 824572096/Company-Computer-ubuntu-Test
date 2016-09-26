#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define BUFFER_SIZE 16

// 设置一个整数的圆形缓冲区
struct prodcons
{
    int buffer[BUFFER_SIZE];  // 缓冲区数组
    pthread_mutex_t lock;     // 互斥锁
    int readpos,writepos;     // 读写的位置
    pthread_cond_t notempty;  // 缓冲区非空信号
    pthread_cond_t notfull;   // 缓冲区非满信号
};

// 初始化缓冲区
void init(struct prodcons *b)
{
    pthread_mutex_init(&b->lock,NULL);
    pthread_cond_init(&b->notempty,NULL);
    pthread_cond_init(&b->notfull,NULL);
    b->readpos  = 0;
    b->writepos = 0;
}

// 向缓冲区中写入一个整数
void put(struct prodcons *b,int data)
{
    pthread_mutex_lock(&b->lock);

    while((b->writepos+1)%BUFFER_SIZE == b->readpos)
    {
        printf("wait for not full\n");
        pthread_cond_wait(&b->notfull,&b->lock); // 等待缓冲区非满信号
    }

    // 写数据并且指针前移
    b->buffer[BUFFER_SIZE] = data;
    b->writepos++;
    if(b->writepos >= BUFFER_SIZE)
    {
        b->writepos = 0;
    }

    pthread_cond_signal(&b->notempty); // 设置缓冲区非空信号
    pthread_mutex_unlock(&b->lock);
}

// 从缓冲区读出一个整数
int get(struct prodcons *b)
{
    int data;

    pthread_mutex_lock(&b->lock);

    while(b->writepos == b->readpos)
    {
        printf("wait for not empty\n");
        pthread_cond_wait(&b->notempty,&b->lock); // 等待缓冲区非空信号
    }

    // 读数据并且指针前移
    data = b->buffer[b->readpos];
    b->readpos++;
    if(b->readpos >= BUFFER_SIZE)
    {
        b->readpos = 0;
    }

    return data;
}

#define OVER(-1)

struct prodcons buffer;

// 生产者线程
void *producer(void *data)
{
    int n;

    for(n = 0; n < 1000; n++)
    {
        printf("put-->%d\n",n);
        put(&buffer,n);
    }

    put(&buffer,OVER);
    printf("producer stopped!\n");

    return NULL;
}

// 消费者线程
void *consumer(void *data)
{
    int d;

    while(1)
    {
        d = get(&buffer);
        if(d == OVER)
            break;
        printf("%d-->get\n",d);
    }
    printf("consumer stopped!\n");

    return NULL;
}

int main(void)
{
    pthread_t th_a,th_b;
    void *retval;
    int(&buffer);

    pthread_create(&th_a,NULL,producer,NULL);
    pthread_create(&th_b,NULL,consumer,NULL);

    // 等待生产者和消费者结束
    pthread_join(th_a,&retval);
    pthread_join(th_b,&retval);

    return 0;
}
