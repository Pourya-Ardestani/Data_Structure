#include "Stack.h"
#include <iostream>

template <class T>
Stack<T>::Stack()
{
	top = -1;
}


template <class T>
bool Stack<T>::push(T new_item)
{
	if (top >= MAX - 1)
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


template <class T>
T Stack<T>::pop()
{
	if (top < 0)
	{
		std::cout << "error there is no element to pop ";
		return 0;
	}
	else
	{
		T x = st[--top];
		return x;
	}
}


template <class T>
T Stack<T>::peek()
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

template <class T>
bool Stack<T>::isEmpty()
{
	if (top < 0)
	{
		return true;
	}
	return false;
}

