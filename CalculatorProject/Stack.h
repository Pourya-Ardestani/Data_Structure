#pragma once
#define MAX 100
class Stack
{
private:
	int top;
public:
	char st[MAX];
	Stack();
	bool push(char);
	char pop();
	char peek();
	bool isEmpty();

};

