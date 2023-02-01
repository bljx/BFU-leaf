// ConsoleApplication2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Point
{
private:
	double x;
	double y;
public:
	Point(double x, double y);
	double getx();
	double gety();
	~Point();
};
Point::Point(double x, double y)
{
	cout << "执行Point类的构造函数" << endl;
	this->x = x;
	this->y = y;
}
Point::~Point()
{
	cout << "执行Point类的析构函数" << endl;
}

double Point::getx()
{
	return x;
}
double Point::gety()
{
	return y;
}

class Circle :public Point
{
private:
	double r;
public:
	Circle(double x, double y, double r);
	double area();
	double getr();
	~Circle();
};
Circle::Circle(double x, double y, double r):Point(x,y)
{
	cout << "执行Circle类的构造函数" << endl;
	this->r = r;
}
Circle::~Circle()
{
	cout << "执行Circle类的析构函数" << endl;
}
double Circle::area()
{
	return 3.14*r*r;
}
double Circle::getr()
{
	return r;
}

class Cylinder :public Circle
{
private:
	double h;
public:
	Cylinder(double x, double y, double r, double h);
	double volume();
	double geth();
	~Cylinder();
	double area();
};
double Cylinder::area()
{
	return 2 * 3.14*getr()*h + 3.14*getr()*getr() * 2;
}
Cylinder::Cylinder(double x, double y, double r, double h):Circle(x,y,r)
{
	cout << "执行Cylinder类的构造函数" << endl;
	this->h = h;
}
Cylinder::~Cylinder()
{
	cout << "执行Cylinder类的析构函数" << endl;
}
double Cylinder::volume()
{
	return Circle::area()*h;
	//return getr()*getr()*3.14*h;
}

double Cylinder::geth()
{
	return h;
}

int main()
{
	Cylinder c(100, 200, 10, 50);
	cout << "圆心坐标：(" << c.getx() << "," << c.gety() << ")" << endl;
	cout << "圆的半径：" << c.getr() << endl;
	cout << "底圆面积：" << c.Circle::area() << endl;
	cout << "高度：" << c.geth() << endl;
	cout << "体积：" << c.volume() << endl;
	cout << "表面积" << c.area() << endl;

    return 0;
}

