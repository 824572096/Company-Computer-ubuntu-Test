#include <iostream>

using namespace std;

class complex
{
public:
    complex(double r = 0.0,double i = 0.0){real = r; imag = i;};
    complex operator + (complex c2);
    complex operator - (complex c2);
    void display();
private:
    double real;
    double imag;
};

complex complex::operator + (complex c2)
{
    return complex(real + c2.real,imag + c2.imag);
}

complex complex::operator - (complex c2)
{
    return complex(real - c2.real,imag - c2.imag);
}

void complex::display()
{
    cout<<"("<<real<<","<<imag<<")"<<endl;
}

int main()
{
    complex c1(5,4),c2(2,10),c3;

    cout<<"c1 = ";c1.display();
    cout<<"c2 = ";c2.display();

    c3 = c1 - c2;
    cout<<"c3 = c1 - c2 = ";
    c3.display();

    c3 = c1 + c2;
    cout<<"c3 = c1 + c2 = ";
    c3.display();

    return 0;
}

