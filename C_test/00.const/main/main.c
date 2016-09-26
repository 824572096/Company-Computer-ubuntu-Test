#include <stdio.h>

int main()
{
    const int a = 3;

    int *pa = &a;
    *pa = 21;
    printf("*pa = %d\n",*pa);

    const int *cpa = &a;
    // *cpa = 42; // 出错
    printf("*cpa = %d\n",*cpa);

    return 0;
}
