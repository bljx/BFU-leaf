#include <iostream>
using namespace std;

class B1
{
protected:
	int b1;
public:
	B1(int i)
	{
		cout<<"执行基类B1的构造函数\n";
		b1 = i;
	}
	~B1()
	{
		cout<<"执行基类B1的析构函数\n";
	}
};
class B2
{
protected: 
	int b2;
public:
	B2(int n)
	{
		b2 = n;
		cout<<"执行基类B2的构造函数\n";
	}
	~B2()
	{
		cout<<"执行基类B2的析构函数\n";
	}
};

class Derive : public B2, public B1
{
protected:
	int d;
public:
	Derive(int a, int b, int c): B1(a), B2(b)
	{
		d = c;
		cout<<"执行派生类D的构造函数\n";
	}
	~Derive()
	{
		cout<<"执行派生类D的析构函数\n";
	}
};

int main()
{
	{Derive dobj(10,20,30);}
	return 0;
}


#include <iostream>
using namespace std;

class B1
{
protected:
	int b;
public:
	B1(int i)
	{
		cout<<"执行基类B1的构造函数\n";
		b = i;
	}
	~B1()
	{
		cout<<"执行基类B1的析构函数\n";
	}
};
class B2
{
protected: 
	int b;
public:
	B2(int n)
	{
		b = n;
		cout<<"执行基类B2的构造函数\n";
	}
	~B2()
	{
		cout<<"执行基类B2的析构函数\n";
	}
};

class Derive : public B2, public B1
{
protected:
	int d;
public:
	Derive(int a, int b, int c): B1(a), B2(b)
	{
		d = c;
		cout<<"执行派生类D的构造函数\n";
	}
	~Derive()
	{
		cout<<"执行派生类D的析构函数\n";
	}
	void showb(){cout<<B1::b<<"\t"<<B2::b<<endl;}
};

int main()
{
	{
		Derive dobj(10,20,30);
		dobj.showb();
	}
	return 0;
}
