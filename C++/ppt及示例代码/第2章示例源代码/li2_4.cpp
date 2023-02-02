#include <iostream>
using namespace std;

class Circle 
{
protected:
	double r;
public:
	Circle(double ra)
	{
		r = ra;
	}
	double area()
	{
		return 3.14159*r*r;
	}
};
class Cylinder : public Circle
{
protected: 
	double h;
public:
	Cylinder(double rv, double hv);
	double area()
	{
		return 2*Circle::area()+2*3.14*r*h;
	}
};

Cylinder::Cylinder(double rv, double hv): Circle(rv)
{
	h = hv;
}

int main()
{
	Circle cir(5);
	Cylinder cylin(5,10);
	cout<<"圆的面积为："<<cir.area()<<"\n";
	cout<<"圆柱体的底面积为："<<cylin.Circle::area()<<"\n";
	cout<<"圆柱体的表面积为："<<cylin.area()<<endl;
	return 0;
}

#include <iostream>
#include <cmath>
using namespace std;

const double PI = acos(-1.0);

class MyCircle{
protected:
	double r;
public:
	MyCircle(double);
	double area();
};

double MyCircle::area(){return PI*r*r;}

MyCircle::MyCircle(double r){this->r = r; cout<<"MyCircle Constructor\n";}

class Cylinder : public MyCircle{
private:
	double h;
public:
	Cylinder(double r, double h) : MyCircle(r),h(h){cout<<"Cylinder Constructor\n";}
	double area(){return 2*MyCircle::area() + 2*PI*r*h;}
};

int main(){
	MyCircle c(3);
	Cylinder cy(3,3);
	cout<<c.area()<<"\t"<<cy.area()<<endl;
	cout<<cy.MyCircle::area()<<endl;
	return 0;
}