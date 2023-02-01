#include <iostream>
using namespace std;

class Point
{
private:
	int x;
	int y;
public:
	Point(int a, int b)
	{
		cout<<"基类Point的构造函数被执行\n";
		x = a;
		y = b;
	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
};

class Circle : public Point
{
private:
	int r;
public:
	Circle(int a, int b, int c):Point(a,b)
	{
		cout<<"派生类Circle的构造函数被执行\n";
		r = c;
	}
	int getr()
	{
		return r;
	}
	double area()
	{
		return 3.14159*r*r;
	}
};

int main()
{
	Circle c(10,20,5);
	cout<<"圆的圆心为：("<<c.getx()<<","<<c.gety()<<")"<<"\n";
	cout<<"圆的半径为："<<c.getr()<<"\n";
	cout<<"圆的面积为："<<c.area()<<endl;
	return 0;
}

#include <iostream>
#include <cmath>
using namespace std;
const double PI = acos(-1.0);
class MyPoint{
protected:
	int x;
	int y;
public:
	MyPoint(int, int);
};

MyPoint::MyPoint(int x, int y){ this->x = x; this->y = y; }

class MyCircle : public MyPoint{
private:
	double r;
public:
	MyCircle(int, int, double);
	double area();
	void show();
};

MyCircle::MyCircle(int x, int y, double r) : MyPoint(x, y), r(r){}
double MyCircle::area(){ return PI*r*r; }
void MyCircle::show(){ cout << "圆心：(" << x << "," << y << ")；圆面积：" << area() << endl; }

int main(){
	MyCircle c(5, 5, 3);
	c.show();

	return 0;
}
