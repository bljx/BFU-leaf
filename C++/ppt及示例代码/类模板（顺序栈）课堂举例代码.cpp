#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

template <typename T, int N>
class Stack
{
private:
	T s[N];
	int top;
public:
	Stack();
	int gettoppoint();
	void push(T data);
	T pop();
};

template <typename T, int N>
Stack<T, N>::Stack()
{
	top = -1;
}

template <typename T, int N>
int Stack<T, N>::gettoppoint()
{
	return top;
}

template<typename T, int N>
void Stack<T, N>::push(T data)
{
	if (top == N - 1)
		cout << "栈已满，无法进栈！" << endl;
	else
	{
		top = top + 1;
		s[top] = data;
	}
}

template<typename T, int N>
T Stack<T, N>::pop()
{
	if (top == -1)
	{
		cout << "栈已空，无法出栈！" << endl;
		return (T)"OVERFLOW";
	}
	else
	{
		T temp;
		temp = s[top];
		top = top - 1;
		return temp;
	}
}

int main()
{
	Stack<int, 50> st;
	st.push(10);
	st.push(40);
	st.push(-100);
	cout << st.gettoppoint() << endl;
	cout << st.pop() << endl;
	cout << st.pop() << endl;
	cout << st.pop() << endl;
	cout << st.pop() << endl;

	Stack<string, 10> st1;

	st1.push("aaaaaa");
	st1.push("bbbbbb");
	st1.push("ccccc");

	cout << st1.pop() << endl;
	cout << st1.pop() << endl;
	cout << st1.pop() << endl;
	cout << st1.pop() << endl;

    return 0;
}
