// 下面是一个简单的读写锁应用实例。程序中有一个读写所的全局变量，供各个线程操作。
// 主线程首先获得先锁，然后创建一百个读线程或写线程，之后释放锁。
// 此后，读线程和写线程开始竞争读写锁。读线程会争取读锁，写线程会争取写锁。
// 读者可以自己运行一下这个程序，然后分析线程的创建顺序和执行顺序的差别，来了解读写锁是怎样协调线程的运行的。

#include <stdio.h>
#define __USE_UNIX98
#include <pthread.h>
#include <stdlib.h>

#define THREADCOUNT 100

pthread_rwlock_t rwlock; // 定义一个读写锁

// 读线程
void *reader(void *pvoid)
{
    pthread_rwlock_rdlock(&rwlock);          // 为读操作获取一个读写锁，阻塞线程，直到获取读写锁
    printf("reader%d worked.\n",*(int*)pvoid);
    if(pthread_rwlock_unlock(&rwlock))       // pthread_rwlock_unlock 释放读写锁，成功返回 0
    {
        printf("reader%d unlock error!\n",*(int*)pvoid);
    }

    return NULL;
}

// 写线程
void *writer(void *pvoid)
{
    pthread_rwlock_wrlock(&rwlock);          // 为写操作获取一个读写锁，阻塞线程，直到获取读写锁
    printf("writer%d worked.\n",*(int*)pvoid);
    if(pthread_rwlock_unlock(&rwlock))
    {
        printf("writer%d unlock error!\n",*(int*)pvoid);
    }

    return NULL;
}

int main(void)
{
    pthread_t reader_id;       // 用于存放读线程ID
    pthread_t writer_id;       // 用于存放写线程ID
    pthread_attr_t threadattr; // 定义一个线程属性对象
    int i,rand;
    int readercount = 1,writercount = 1;
    int halfmax = RAND_MAX / 2;

    // 初始化读写锁
    if(pthread_rwlock_init(&rwlock,NULL))
    {
        printf("initialize rwlock error!\n");
    }

    // 用默认值对线程属性对象初始化
    pthread_attr_init(&threadattr);

    // 设置线程属性对象中线程的状态为 PTHREAD_CREATE_DETACHED
    pthread_attr_setdetachstate(&threadattr,PTHREAD_CREATE_DETACHED);

    // 为写操作获取一个读写锁，阻塞线程，直到获取读写锁
    pthread_rwlock_wrlock(&rwlock);

    for(i = 0; i < THREADCOUNT; i++)
    {
        rand = random();
        if(rand < halfmax)
        {
            pthread_create(&reader_id,&threadattr,reader,&readercount);
            printf("Create reader%d\n",readercount++);
        }
        else
        {
            pthread_create(&writer_id,&threadattr,writer,&writercount);
            printf("Create reader%d\n",writercount++);
        }
    }
    pthread_rwlock_unlock(&rwlock);

    pthread_exit(NULL);
    return 0;
}
