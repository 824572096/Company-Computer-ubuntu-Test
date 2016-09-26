#include <stdio.h>
#include <pthread.h>

void* fun(void* arg)
{
    int i;
    for ( i = 0; i < 2; ++i )
    {
        printf( "%s\n",(char *)arg );
        sleep( 1 );
    }
}

int main( void )
{
    pthread_t id1;
    pthread_t id2;

    pthread_create( &id1, NULL, fun, "thread 1" );
    pthread_create( &id2, NULL, fun, "thread 2" );

    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    return 0;
}
