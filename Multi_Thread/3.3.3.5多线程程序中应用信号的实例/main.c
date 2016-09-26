#include <stdio.h>
#include <pthread.h>
#include <signal.h>

void *threadfunc(void *pvoid)
{
    pthread_t *main_tid = (pthread_t*)pvoid;
    printf("Child thread says:Hello!World!\n");
    pthread_kill(*main_tid,SIGUSR1); // 将指定的信号发送给指定的线程
}

// 进程可以通过阻塞信号暂时地阻止信号的传递。在传递之前，被阻塞的信号不会影响进程的行为。
// 进程的信号掩码(signal mask)给出了一个信号的集合，对哪些信号进行阻塞，需要通过信号掩码进行设置。
// 信号掩码的类型为 sigset_t 。

int main()
{
    sigset_t sigs;
    int sig;
    pthread_t tid;
    pthread_t main_tid;

    sigemptyset(&sigs);                // 对信号集 sigs 进行初始化，使其不包含任何信号
    sigaddset(&sigs,SIGUSR1);          // 将 SIGUSR1 加入信号集 sigs
    sigprocmask(SIG_BLOCK,&sigs,NULL); // 对于进程来说，可以通过sigprocmask来检查或修改它的进程信号掩码

    main_tid = pthread_self();
    pthread_create(&tid,NULL,&threadfunc,&main_tid);
    sigwait(&sigs,&sig);               // 将调用这个函数的线程挂起，直到sigmask指定的信号集中的信号被挂起

    // 注意:
    // signmask指定的信号集中的信号必须在sigwait调用之前被阻塞，并且不能被忽略的，
    // 如果为这些信号指定处理函数，这些处理函数也不会被调用。

    printf("Main thread says:Hello!World!\n");

    return 0;
}
