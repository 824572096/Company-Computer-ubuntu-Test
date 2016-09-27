#include <iostream>
#include <iomanip>
#include "array_class.h"

using namespace std;

// Array 类的应用
// 求范围 2~n 中的质数,n在程序运行时由键盘输入

int main()
{
    Array<int> A(10);        // 用来存放质数的数组,初始状态有10个元素
    int n;                   // 质数范围的上限,运行输入
    int primecount = 0,i,j;

    cout<<"Enter a value >= 2 as upper limit for prime numbers: ";
    cin>>n;

    A[primecount++] = 2;     // 2是一个质数
    for(i = 3; i < n; i++)
    {
        // 如果质数表满了,便再申请分配10个元素的空间
        if(primecount == A.ListSize())
        {
            A.Resize(primecount + 10);
        }

        // 大于2的偶数不是质数,因此略过本次循环的后续部分,进入下一次循环
        if(i%2 == 0)
        {
            continue;
        }

        // 检查 3,5,7,...,i/2 是否是 i 的因子
        j = 3;
        while((j <= i/2) && (i%j != 0))
        {
            j += 2;
        }

        // 若上述均部位i的因子,则i为质数
        if(j > i/2)
        {
            A[primecount++] = i;
        }
    }

    // 输出质数
    for(i = 0; i < primecount; i++)
    {
        cout<<setw(5)<<A[i];

        // 每输出10个数换行一次
        if((i + 1)%10 == 0)
        {
            cout<<endl;
        }
    }
    cout<<endl;

    return 0;
}

