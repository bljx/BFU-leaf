// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Complex
{
protected:
	double r;
	double i;
public:
	Complex(double r = 0.0, double i = 0.0);
	void show();
	Complex operator+(Complex c);
	friend Complex operator- (Complex c1, Complex c2);
	friend Complex operator--(Complex c1);
	Complex operator++();
	Complex operator++(int);
};

Complex Complex::operator++(int)
{
	Complex t;
	t.r = this->r;
	t.i = this->i;
	this->r = this->r +1;
	this->i = this->i + 1;
	return t;
}

Complex operator--(Complex c1)
{
	c1.r = c1.r - 1;
	c1.i = c1.i - 1;
	return c1;
}

Complex Complex::operator++()
{
	this->r = this->r + 1;
	this->i = this->i + 1;
	return *this;
}

Complex operator- (Complex c1, Complex c2)
{
	double r1, i1;
	r1=c1.r - c2.r;
	i1 = c1.i - c2.i;
	Complex t(r1, i1);
	return t;
}

Complex Complex::operator+(Complex c)
{
	double r1;
	double i1;
	r1 = this->r + c.r;
	i1=this->i + c.i;
	Complex t(r1, i1);
	return t;
}
Complex::Complex(double r, double i)
{
	this->r = r;
	this->i = i;
}
void Complex::show()
{
	cout << "(" << r << "+" << i << "i)";
}

int main()
{
	Complex c1(10, 20);
	Complex c2(100, 200);
	/*
	Complex c3;
	c3= ++c2;
	cout << endl;
	c3.show();

	Complex c4;
	c4 = --c1;
	cout << endl;
	c4.show();
	*/
	Complex c5;
	c5 = c2++;

	cout << endl;
	c2.show();
	cout << endl;
	c5.show();

    return 0;
}

