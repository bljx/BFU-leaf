// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

class Student
{
private:
	int num;
	char *name;
	char sex;
	int age;
public:
	void show();
	Student();
	Student(int num,char *name,char sex,int age);
	~Student();
	Student(Student &x);
};

void Student::show()
{
	cout << num << "," << name << "," << sex << "," << age << endl;
}
Student::Student()
{
	num = -1;
	this->name = new  char[30];
	strcpy_s(name, sizeof("no name")+1,"no name");
	sex = '!';
	age = -1;
}

Student::Student(int num, char *name, char sex, int age)
{
	this->num = num;
	this->name = new char[30];
	
	strcpy_s(this->name, sizeof(name)+1, name);
	this->sex = sex;
	this->age = age;
}

Student::Student(Student &x)
{
	num = x.num;
	name = new char[sizeof(x.name)+1];
	//strcpy(name, x.name);
	strcpy_s(name, sizeof(x.name)+1, x.name);
	sex = x.sex;
	age = x.age;

}
Student::~Student()
{
	delete []name;
}

int main()
{
	Student s;
	s.show();

	Student s2(s);
	s2.show();


	/*int a;
	char b[30];
	char c;
	int d;
	cout << "学号：";
	cin >> a;
	getchar();
	cout << "姓名：";
	cin.getline(b, sizeof(b));
	cout << "性别：";
	cin >> c;
	cout << "年龄：";
	cin >> d;
	Student s1(a, b, c, d);
	s1.show();*/
    return 0;
}

