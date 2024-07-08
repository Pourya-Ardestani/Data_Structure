#pragma once
#include<iostream>

template <class T>
struct Stack
{
	Stack* top;
	Stack* next;
	T value;

	Stack();
	void push(T);
	T pop();
	T peek();
	bool isEmpty();

};



template <class T>
Stack<T>::Stack()
{
	top = NULL;
	next = NULL;
}


template <class T>
void Stack<T>::push(T new_item)
{
	Stack* newStack = new Stack();
	newStack->value = new_item;
	newStack->next = top;
	top = newStack;

}


template <class T>
T Stack<T>::pop()
{
	if (top != NULL)
	{	
		T x = top->value;
		top = top->next;
		return x;
	}

	////////////////khodam
}


template <class T>
T Stack<T>::peek()
{
	if (top != NULL)
	{
		return top->value;
	}
	return 'E';
}

template <class T>
bool Stack<T>::isEmpty()
{
	return (top == NULL);
}
