#include <iostream>
#include <cstdlib>

using namespace std;

struct Student
{
    int   id;
    float gpa;
};

template <class T>     // 类模板:实现对任意类型数据进行存取
class Store
{
public:
    Store(void);
    T GetElem(void);   // 提取数据函数
    void PutElem(T x); // 存入数据函数
private:
    T   item;
    int haveValue;
};

// 以下实现各成员函数
// 注意:类模板的成员函数,若在类外实现,则必须是模板函数

// 默认构造函数的实现
template <class T>
Store<T>::Store(void)
{
    haveValue = 0;
}

// 提取数据函数实现
template <class T>
T Store<T>::GetElem(void)
{
    if(0 == haveValue)
    {
        cout<<"No item present!"<<endl;
        exit(1);
    }

    return item;
}

// 存入数据函数实现
template <class T>
void Store<T>::PutElem(T x)
{
    haveValue++;
    item = x;
}


int main()
{
    Student g  = {1000,23};
    Store<int>     S1,S2;   // 声明两个 Store<int> 类对象,数据数据成员item为int类型
    Store<Student> S3;
    Store<double>  D;

    S1.PutElem(3);
    S2.PutElem(-7);
    cout<<S1.GetElem()<<" "<<S2.GetElem()<<endl;

    S3.PutElem(g);
    cout<<"The student id is "<<S3.GetElem().id<<endl;

    cout<<"Retrieving object D : ";
    cout<<D.GetElem()<<endl;

    return 0;
}

