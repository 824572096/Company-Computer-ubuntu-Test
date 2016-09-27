#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H

// 本程序来自 << C++语言程序设计(第3版) >>  郑莉 P291 ~ P301
// 在第6章我们介绍了静态数组,静态数组是具有固定元素个数的群体,其中的元素可以通过下标直接访问.
// 尽管静态数组是十分重要的数据结构,但也存在缺憾,因为其大小在编译时就已经确定,在运行时无法修改.
// 而且使用静态数组时,不能有效地避免下标越界问题.

// 针对静态数组的不足之处,现在我们来设计一个动态数组类模板Array,
// 它由任意多个位置连续的,类型相同的元素组成,其元素个数可以在程序运行时改变.

#include <iostream>
#include <cstdlib>

using namespace std;

#ifndef NULL
const int NULL = 0;
#endif

// 错误类型集合,共有三种类型的错误:
// 数组大小错误
// 内存分配错误
// 下标越界
typedef enum
{
    invalidArraySize,
    memoryAllocationError,
    indexOutOfRange,
}ErrorType;

// 错误信息
char *errorMsg[] =
{
    "Invalid array size",
    "Memory allocation error",
    "Invalid index:"
};

// 数组类模板声明
template <class T>
class Array
{
private:
    T*  alist;                                         // T类型指针，用于存放动态分配的数组内存首地址
    int size;                                          // 数组大小(元素个数)
    void Error(ErrorType error,int badIndex = 0)const; // 错误处理函数
public:
    Array(int sz = 50);                                // 构造函数
    Array(const Array<T>& A);                          // 拷贝构造函数
    ~Array(void);                                      // 析构函数
    Array<T>& operator = (const Array<T>& rhs);        // 重载"="使数组对象可以整体赋值
    T& operator [] (int);                              // 重载"[]",使Array对象可以起到C++普通数组的作用
    operator T* (void)const;                           // 重载 T* ,使Array对象可以起到C++普通数组的作用
    int ListSize(void)const;                           // 取数组大小
    void Resize(int sz);                               // 修改数组大小
};


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


#endif // ARRAY_CLASS_H
