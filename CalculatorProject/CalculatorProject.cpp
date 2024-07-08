#include <iostream>
#include <string>
#include <cmath>
#include "Stack.h"
using namespace std; 


string fixString(string s); // add prototype and parameters 




//////////////////////////

int Priority(char);


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
    ////////////////////////////test Stack
    /*Stack<char> stack1;
    stack1.push('1');
    stack1.push('2');
    stack1.push('3');
    while (!stack1.isEmpty())
    {
        cout << stack1.pop();
    }*/
    //+++++++++++++++++++++++++++++
    s = fixString(s);
    cout << s; 
 /*   for (char i; i < s.size(); i++)
      cout << s[i];*/


}


bool myLetter(char c)
{
    if (c == 's' or c == 'c' or c == 't' or c == 'e' or c == 'P')
        return true;
    return false;
}

bool isOperator(char c)
{
    if (c == '/' or c == '*' or c == '+' or c == '-' or c == '^' or c == '(' or c == ')' or c == '!' or c == '%' or c == '=')
        return true;
    return false;
}

string fixString(string s)// add prototype and parameters 
{

    // REMOVE SPACES
    for (int i = 0; i < s.size(); i++)
        if (isspace(s[i]))
        {
            s.erase(s.begin() + i), i--;
        }

    //detect minus
    if (s[0] == '-')
        s.insert(s.begin(), '0');

    // REMOVE EQUAL SIGN if (it was in last )
    if (s[s.size() - 1] == '=')
        s.erase(s.end() - 1);

    Stack<double> values;
    Stack<char> ops;
    string result;

    for (size_t i = 0; i < s.size(); ++i) 
    {
        if (s[i] == '(') 
        {
            ops.push(s[i]);

        }
        else if (isdigit(s[i])) 
        {
            size_t start = i;
            while (i < s.length() && (isdigit(s[i]) || s[i] == '.')) 
            {
                ++i;
            }
            string numberStr = s.substr(start, i - start);
            double number = stod(numberStr);
            values.push(number);
            --i; // Adjust the index after the inner loop
        }

        else if (s[i] == ')')
        {
            ops.pop();
        }

    }
    // detect exeption ()()
    if (!ops.isEmpty())
    {
        result = "ERORR!!!" ;
        return result; 
    }


    for (size_t i = 0; i < s.size(); ++i) {

        // Handle multiple signs
        if (s[i] == '+' || s[i] == '-') {
            int minus = 0;
            size_t j = i;
            while (j < s.size() && (s[j] == '+' || s[j] == '-')) {
                if (s[j] == '-') minus++;
                j++;
            }
            i = j - 1; // Adjust loop index

            if (minus % 2 == 1) {
                if (!result.empty() && (result.back() == '*' || result.back() == '/' || result.back() == '^')) {
                    result += "(-";
                    while (++i < s.size() && (isalpha(s[i]) || isdigit(s[i]) || s[i] == '.')) {
                        result += s[i];
                    }
                    result += ')';
                    i--; // Adjust loop index
                    continue;
                }
                result += '-';
            }
            else {
                if (result.empty() || isOperator(result.back())) {
                    continue; // Skip the sign
                }
                result += '+';
            }
            continue;
        }
        //for (size_t i = 0; i < s.size(); ++i) 
        //{
        //    //if (isdigit(s[i]))
        //}


        // Insert multiplication sign where necessary
        if (isdigit(s[i]) && (i + 1 < s.size()) && isalpha(s[i + 1])) {
            result += s[i];
            result += '*';
            continue;
        }

        // Handle negative sign after opening parenthesis
        if (s[i] == '(' && (i + 1 < s.size()) && s[i + 1] == '-') {
            result += "(0";
            continue;
        }

        // Insert multiplication for various cases
        if ((isdigit(s[i]) && (i + 1 < s.size()) && s[i + 1] == '(')   ||
            (s[i] == ')'   && (i + 1 < s.size()) && s[i + 1] == '(')   ||
            (s[i] == ')'   && (i + 1 < s.size()) && isdigit(s[i + 1]))){
            result += s[i];
            result += '*';
            continue;
        }

        result += s[i];
    }


    // manfi daron parantez
    for (int i = 0; i < s.size(); i++)
        if ((isdigit(s[i]) && s[i + 1] == '(') || (s[i] == ')' && s[i + 1] == '(') || (s[i] == ')' && isdigit(s[i + 1])))
            s.insert(s.begin() + i + 1, '*');

    // zarb beiin parantez
    for (int i = 0; i < s.size(); i++)
        if ((isdigit(s[i]) && s[i + 1] == '(') || (s[i] == ')' && s[i + 1] == '(') || (s[i] == ')' && isdigit(s[i + 1])))
            s.insert(s.begin() + i + 1, '*');
    //result
    if (s[0] == '-')
        s.insert(s.begin(), '0');

    // Ensure the string starts correctly
    if (!result.empty() && result[0] == '-') {
        result.insert(result.begin(), '0');
    }
    return result;

}


int Priority(char c)
{
    if (c == '-' or c == '+')
        return 0;
    if (c == '/' or c == '*')
        return 1;
    if (c == '^')
        return 2;
}
