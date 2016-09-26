#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *thread_function(void *arg);


int main()
{
    char message[] = "Hello World";
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_create(&a_thread,NULL,thread_function,(void *)message);
    if(res != 0)
    {
        printf("Thread creation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\n");

    // 主线程在此阻塞，等待子线程执行完
    // a_thread         要等待的线程ID
    // &thread_result   用于存放返回值地址的指针的地址
    res = pthread_join(a_thread,&thread_result);
    if(res != 0)
    {
        printf("Thread join failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined, it returned %s\n",(char *)thread_result);
    printf("Message is now %s\n",message);
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg)
{
    char *message;
    message = (char*)arg;
    printf("thread_funciton is running. Argument was %s\n",message);
    sleep(3);
    strcpy(message,"Bye!");
    pthread_exit("Thank you for the CPU time");
}
