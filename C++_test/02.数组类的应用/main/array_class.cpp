#include "array_class.h"


// 以下为类成员函数的定义

// 模板函数Error实现输出错误信息的功能
template <class T>
void Array<T>::Error(ErrorType error, int badIndex) const
{
    cout<<errorMsg[error];        // 根据错误类型,输出相应的错误信息
    if(error == indexOutOfRange)
    {
        cout<<badIndex;           // 如果是下标越界,输出错误下标
    }
    cout<<endl;
    exit(1);
}

// 构造函数
template <class T>
Array<T>::Array(int sz)
{
    if(sz < 0)                        // sz 为数组大小(元素个数),若小于0,则输出错误信息
    {
        Error(invalidArraySize);
    }
    size  = sz;                       // 将元素个数赋值给变量 size
    alist = new T[size];
    if(NULL == alist)
    {
        Error(memoryAllocationError);
    }
}

// 析构函数
template <class T>
Array<T>::~Array(void)
{
    delete [] alist;
}

// 拷贝构造函数
template <class T>
Array<T>::Array(const Array<T>& X)
{
    // 从对象 X 取得数组大小,并赋值给当前对象的成员
    int n = X.size;
    size = n;

    // 为对象申请内存并进行出错检查
    alist = new T[n];
    if(alist == NULL)
    {
        Error(memoryAllocationError);
    }

    // 从对象 X 复制数组元素到本对象
    T* srcptr  = X.alist;
    T* destptr = alist;
    while(n > 0)
    {
        *destptr = *srcptr;
        destptr++;
        srcptr++;
        n--;
    }
}

// 重载"="运算符,将对象rhs赋值给本对象.实现对象之间的整体赋值
template <class T>
Array<T>& Array<T>::operator = (const Array<T>& rhs)
{
    int n = rhs.size; // 取 rhs 的数组大小

    // 如果本对象中数组大小与rhs数组大小不同,则删除数组原有内存,然后重新分配
    if(size != n)
    {
        delete [] alist;    // 删除数组原有内存
        alist = new T[n];   // 重新分配n个元素的内存
        if(NULL == alist)   // 如果分配内存不成功,输出错误信息
        {
            Error(memoryAllocationError);
        }
        size = n;           // 记录本对象的数组大小
    }

    // 从 rhs 向本对象赋值元素
    T* destptr = alist;
    T* srcptr  = rhs.alist;
    while(n > 0)
    {
        *destptr = *srcptr;
        destptr++;
        srcptr++;
        n--;
    }

    return *this;
}


// 重载下标运算符,实现与普通数组一样通过下标访问元素,并且具有越界检查功能
template <class T>
T& Array<T>::operator [] (int n)
{
    if(( n < 0 ) || (n > size -1)) // 检测下标是否越界
    {
        Error(indexOutOfRange,n);
    }
    return alist[n];               // 返回下标为 n 的数组元素
}


// 重载指针转换运算符,将Array类的对象名转换为T类型的指针
// 指向当前对象中的私有数组
// 因而可以向使用普通数组首地址一样使用Array类的对象名
template <class T>
Array<T>::operator T* (void) const
{
    return alist;
}


// 取当前数组的大小
template <class T>
int Array<T>::ListSize(void) const
{
    return size;
}


// 将数组大小修改为 sz
template <class T>
void Array<T>::Resize(int sz)
{
    if(sz <= 0)                       // 检查是否 sz<= 0
    {
        Error(invalidArraySize);
    }

    if(sz == size)                    // 如果指定的大小与原有大小一样,什么也不做
    {
        return;
    }

    T* newlist = new T[sz];           // 申请新的数组内存
    if(NULL == newlist)               // 测试申请内存是否申请成功
    {
        Error(memoryAllocationError);
    }

    int n = (sz <= size)?sz:size;     // 将 sz 与 size 中较小的一个赋值给 n

    // 将原有数组中前 n 个元素复制到新数组中
    T* srcptr  = alist;
    T* destptr = newlist;

    while(n > 0)
    {
        *destptr = *srcptr;
        destptr++;
        srcptr++;
        n--;
    }

    delete [] alist; // 释放原数组所占据的内存
    alist = newlist; // 使 alist 指向新数组
    size  = sz;      // 更新 size
}
