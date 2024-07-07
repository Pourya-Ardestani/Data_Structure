#include <iostream>
#include <string>
#include <cmath>
//#include "Stack.h"
using namespace std; 


#define MAX 100

template <class T>
struct Stack
{
	Stack* top;
	Stack* next;
	T value;
	/// 
	/// 
	/// 

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
    T x = top->value;
    top = top->next;
    return x;
    ////////////////khodam
}


template <class T>
T Stack<T>::peek()
{
    return top->value;
}

template <class T>
bool Stack<T>::isEmpty()
{
    return (top == NULL);
}


//////////////////////////

int pri(char ch) //precedence checking
{
    switch (ch)
    {
    case '-':
    case '+': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    case '(':
    case ')': return 4;
    default: return -1;
    }
}

int calculator(char ch, int a, int b)
{
    switch (ch)
    {
    case '+':return a + b;
    case '-':return a - b ;
    case '*':return a * b;
    case '/':
        if (b != 0)
            return a / b;
        else
            return 0;
    case '^':return int(pow(a, b));
    default:return -1;
    }
}


// 
int main()
{
    string s;
    cout << "Enter an expression: ";
    getline(cin,s);
    Stack<char> stack1;
    stack1.push('1');
    stack1.push('2');
    stack1.push('3');
    while (!stack1.isEmpty())
    {
        cout << stack1.pop();
    }


}

//string fixString(string s)// add prototype and parameters 
//{
//    // REMOVE SPACES
//    for (int i = 0; i < s.size(); i++)
//        if (isspace(s[i]))
//        {
//            s.erase(s.begin() + i), i--;
//        }
//
//    //detect minus
//    if (s[0] == '-')
//        s.insert(s.begin(), '0');
//
//    // REMOVE EQUAL SIGN if (it was in last )
//    if (s[s.size() - 1] == '=')
//        s.erase(s.end() - 1);
//    Stack<double> values;
//    Stack<char> ops;
//    for (size_t i = 0; i < s.length(); ++i) 
//    {
//        if (s[i] == '(') 
//        {
//            ops.push(s[i]);
//        }
//        else if (std::isdigit(s[i])) 
//        {
//            size_t start = i;
//            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) 
//            {
//                ++i;
//            }
//            string numberStr = s.substr(start, i - start);
//            double number = stod(numberStr);
//            values.push(number);
//            --i; // Adjust the index after the inner loop
//        }
//    }
//}

