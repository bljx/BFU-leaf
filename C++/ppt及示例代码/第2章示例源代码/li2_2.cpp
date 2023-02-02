#include <iostream>
using namespace std;

class Base
{
private:
	int b1;
protected:
	int b2;
public:
	int b3;
	void set_b1(int x)
	{
		b1 = x;
	}
	int get_b1()
	{
		return b1;
	}
};

class Derive : public Base
{
private:
	int d1;
public:
	int d2;
	void set(int a, int b, int c, int d, int e)
	{
		set_b1(a);  //b1在派生类中不可访问
		b2 = b;
		b3 = c;
		d1 = d;
		d2 = e;
	}
	void show()
	{
		cout<<"b1 = "<<get_b1()<<endl;
		cout<<"b2 = "<<b2<<endl;
		cout<<"b3 = "<<b3<<endl;
		cout<<"d1 = "<<d1<<endl;
		cout<<"d2 = "<<d2<<endl;
	}
};

int main()
{
	Derive obj;
	obj.set(1,2,3,4,5);
	obj.show();
	//在类外通过派生类的对象只能访问派生类的公有成员，所以b1,b2,d1不可访问
//	cout<<"b1 = "<<obj.b1<<endl;
//	cout<<"b2 = "<<obj.b2<<endl;
	cout<<"b3 = "<<obj.b3<<endl;
//	cout<<"d1 = "<<obj.d1<<endl;
	cout<<"d2 = "<<obj.d2<<endl;
	return 0;
}
