#include <iostream>
using namespace std;

class Base 
{
private:
	int b;
public:
	Base(int i)
	{
		cout<<"执行基类Base的构造函数\n";
		b = i;
	}
	~Base()
	{
		cout<<"执行基类Base的析构函数\n";
	}
};
class A
{
private: 
	int a;
public:
	A(int n)
	{
		a = n;
		cout<<"执行类A的构造函数\n";
	}
	~A()
	{
		cout<<"执行类A的析构函数\n";
	}
};

class Derive : public Base
{
private:
	int d;
	A aobj;
public:
	Derive(int a, int b, int c): Base(b), aobj(a)
	{
		d = c;
		cout<<"执行派生类Derive的构造函数\n";
	}
	~Derive()
	{
		cout<<"执行派生类Derive的析构函数\n";
	}
};

int main()
{
	{Derive dobj(10,20,30);}
	return 0;
}
