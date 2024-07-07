#include "Stack.h"
#include <iostream>
Stack::Stack()
{
	top = -1;
}

bool Stack::push(char new_item)
{
	if (top >= MAX-1)
	{
		std::cout << "Stack Overflow";
		return false;
	}
	else
	{
		st[top] = new_item;
		top++;
	}
}
char Stack::pop()
{
	if (top < 0)
	{
		std::cout << "error there is no element to pop ";
		return 0;
	}
	else
	{
		char x = st[--top];
		return x;
	}
}
char Stack::peek()
{
	if (top < 0) {
		std::cout << "Stack is Empty";
		return 0;
	}
	else
	{
		return st[top];
	}
}
bool Stack::isEmpty()
{
	if (top < 0)
	{
		return true;
	}
	return false;
}