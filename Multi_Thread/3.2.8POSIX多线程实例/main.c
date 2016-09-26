#include <stdio.h>
#include <pthread.h>

void *threadfunc(void *pvoid)
{
    int id = *(int*)pvoid;
    printf("child thread%d says : Hello World\n",id);
    return NULL;
}

int main()
{
    int thread_num1 = 1;
    int thread_num2 = 2;
    pthread_t tid1,tid2;

    pthread_create(&tid1,NULL,threadfunc,&thread_num1);
    pthread_create(&tid2,NULL,threadfunc,&thread_num2);
    // sleep(1);
    pthread_join(tid1,NULL); // 使调用这个函数的线程阻塞，等待 tid1 线程运行完成再继续执行
    pthread_detach(tid1);    // 就是非阻塞版本的 pthread_join
    pthread_join(tid2,NULL);

    // pthread_exit(NULL);
    printf("Main thread says : Hello World\n");
    
    return 0;
}
