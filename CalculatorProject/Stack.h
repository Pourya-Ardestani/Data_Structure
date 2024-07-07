#pragma once
#define MAX 100

template <class T>
class Stack
{
private:
	int top;

public:
	char st[MAX];
	Stack();
	bool push(T);
	T pop();
	T peek();
	bool isEmpty();

};

