#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i = 0;
pthread_mutex_t mutex   = PTHREAD_MUTEX_INITIALIZER;  // 静态分配的互斥量初始化
pthread_cond_t  condvar = PTHREAD_COND_INITIALIZER;   // 静态分配的条件变量初始化


// 线程函数
void *threadfunc(void *pvoid)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);          // 获取互斥量，使调用这个函数的线程一直阻塞到互斥量可用为止
        if(i<200)
        {
            i++;
            pthread_cond_signal(&condvar);   // 只唤醒一个阻塞在 &condvar 所指向的条件变量上的线程
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);    // 释放互斥量
            break;
        }
    }

    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,&threadfunc,NULL);

    pthread_mutex_lock(&mutex);
    while(i<100)
    {
        pthread_cond_wait(&condvar,&mutex);  // 使调用这个函数的线程阻塞在这里，同时互斥量被释放
    }

    printf("i = %d\n",i);
    pthread_mutex_unlock(&mutex);
    pthread_join(tid,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condvar);

    return 0;
}

// 注意 : 等待条件变量的线程被唤醒时，并不自动获得互斥量.将与子线程一同竞争互斥量。
