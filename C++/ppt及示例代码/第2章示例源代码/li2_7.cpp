#include <iostream>
using namespace std;

class B
{
protected:
	int b;
public:
	B(int bval)
	{
		cout<<"执行类B的构造函数\n";
		b = bval;
	}
};
class D1 : virtual public B
{
protected: 
	int d1;
public:
	D1(int bval, int dval) : B(bval)
	{
		d1 = dval;
		cout<<"执行类D1的构造函数\n";
	}
};

class D2 : virtual public B
{
protected: 
	int d2;
public:
	D2(int bval, int dval) : B(bval)
	{
		d2 = dval;
		cout<<"执行类D2的构造函数\n";
	}
};

class Derive : public D1, public D2
{
protected:
	int d3;
public:
	Derive(int bval, int dval1, int dval2, int dval3): D1(bval, dval1), D2(bval, dval2), B(bval)
	{
		d3 = dval3;
		cout<<"执行类Derive的构造函数\n";
	}
	void show()
	{
		cout<<"成员b的值为："<<b<<"\n";
		cout<<"成员d1的值为："<<d1<<"\n";
		cout<<"成员d2的值为："<<d2<<"\n";
		cout<<"成员d3的值为："<<d3<<"\n";
	}
};

int main()
{
	Derive dobj(10,20,30,40);
	dobj.show();
	return 0;
}
