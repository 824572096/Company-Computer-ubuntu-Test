#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* child1(void *arg)
{
    pthread_t tid = pthread_self();
    printf("1 thread %lu\n",tid);
}

int main(void)
{
    int res;
    pthread_t a_thread;
    pthread_t tid = pthread_self();

    printf("main thread %lu enter\n",tid);
    res = pthread_create(&a_thread,NULL,child1,NULL);
    if(res != 0)
    {
        printf("Thread creation failed\n");
        exit(-1);
    }

    // if do not have sleep(1) , child1 will not be executed.
    // sleep(1);



    printf("main ByeBye.\n");

    return 0;
}
