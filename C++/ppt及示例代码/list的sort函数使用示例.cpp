// ConsoleApplication24.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <iostream>
#include <functional>
#include<string>
using namespace std;

class Student //定义类
{
public:
	string no;
	int age;
public:
	Student(string no, int age)
	{
		this->no = no;
		this -> age = age;
	}
	 friend bool operator>(const Student &s1,const Student &s2)  //重载运算符函数>
	{
		if (s1.age > s2.age)
			return true;
		return false;
	}
};

class S   //自定义类
{
public:
	bool operator()(const Student &s1, const Student &s2)  //重载运算符（）
	{
		if (s1.age < s2.age)
			return true;
		return false;
	}
};

int main()
{
	list<int> list1;       //元素为基本数据类型
	list1.push_back(100);
	list1.push_back(20);
	list1.push_back(300);
	list1.push_back(40);
	list1.sort(greater<int>());   //将库函数greater<type>()传递给sort函数，进行升序排序
	list<int>::iterator i1;
	for (i1 = list1.begin();i1 != list1.end();i1++)
		cout << *i1 << endl;

	list<string> list2;     //元素为string类型
	list2.push_back("abc");
	list2.push_back("123");
	list2.push_back("078");
	list2.push_back("xyz");
	list2.push_back("tttt");

	list2.sort();         //不带参数，表示对基本类型的元素升序排序

	list<string>::iterator i2;
	for (i2 = list2.begin();i2 != list2.end();i2++)
		cout << *i2 << endl;

	list<Student> list3;   //元素为Student对象类型

	list3.push_back(Student("111", 21));
	list3.push_back(Student("222", 22));
	list3.push_back(Student("333", 29));
	list3.push_back(Student("444", 20));

	list3.sort(greater<Student>());  //将库函数greater<type>()传递给sort函数，由于Student类中重载了>运算符，所以升序排序
	list<Student>::iterator i3;
	for (i3 = list3.begin();i3 != list3.end();i3++)
	{
		cout << (*i3).no<<","<<(*i3).age << endl;
	}


	list3.sort(S());    //将自定类的对象传递给sort函数，由于在类S中，重载了运算符()，并定义了升序，所以升序排序。
	for (i3 = list3.begin();i3 != list3.end();i3++)
	{
		cout << (*i3).no << "," << (*i3).age << endl;
	}

	return 0;
}

