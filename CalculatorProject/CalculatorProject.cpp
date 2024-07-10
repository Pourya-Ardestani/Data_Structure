#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <thread>
#include <stdlib.h>
#include "Stack.h"
using namespace std; 

#define SCREEN_CLEAN_TIME 8

int calculator(char, int, int);
string fixString(string s);  
string convertToPostfix(string );
void paranthes(string*, Stack<char>*);
double calculate_postfix(string);


 
int main()
{
    bool end = false;
    string equation;
    while (!end)
    {
        cout << "Enter an new expression: (or Enter 'E' to End the proggram ): ";
        getline(cin, equation);
        equation = fixString(equation);

        if (equation[0] == 'E' || equation[0] == 'e')
            end = true;
        else if (equation[0] == 'T')
            cout << equation <<"\n\n\n";
        else
        {
            cout << "\n after fix : " << equation;
            string postfix;
            postfix = convertToPostfix(equation);

            cout << "\n after convert : " << postfix;
            double Answer = calculate_postfix(postfix);
            cout << "\n" << " Answer : " << Answer << "\n";
            this_thread::sleep_for(chrono::seconds(SCREEN_CLEAN_TIME));
            system("CLS");
        }

    }

    return 0;
}


//+++++++++++++++++++++++++++
// functions implementation: 

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

int priority(char c)
{
    int r;
    switch (c)
    {
    case'-': 
    case'+':r = 1; break;
    case'/':
    case'*':r = 2; break;
    case'^':r = 3; break;

    default:return-1;
    }
    return r;
}


bool isOperator(char c)
{
    if (c == '/' or c == '*' or c == '+' or c == '-' or c == '^' )
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


    // remove equal sign if (it was in last )
    if (s[s.size() - 1] == '=')
        s.erase(s.end() - 1);

    Stack<char> parentheses;
    string result;

    //check if parantheses are EVEN
    for (size_t i = 0; i < s.size(); ++i) 
    {
        if (s[i] == '(') 
        {
            parentheses.push(s[i]);
        }
        else if (s[i] == ')')
        {
            if (parentheses.isEmpty())// detect exeption ()() for starting parentheses
            {
                result = "There is an Error!!! detected Error for not existing starting <<(>> parenthese ";
                return result;
            }
            parentheses.pop();
        }
    }

    // detect exeption ()() for end parentheses
    if (!parentheses.isEmpty())
    {
        result = "There is an Error!!! detected Error for not existing ending <<)>> parenthese ";
        return result; 
    }


    // Handle multiple signs    
    for (size_t i = 0; i < s.size(); ++i) {

        if (s[i] == '+' || s[i] == '-') {
            int minus = 0;
            size_t j = i;
            while (j < s.size() && (s[j] == '+' || s[j] == '-')) {
                if (s[j] == '-') minus++;
                j++;
            }
            i = j - 1; 

            // handle minus sign if there was even number of them or not 
            if (minus % 2 == 1) {
                if (!result.empty() && (result.back() == '*' || result.back() == '/' || result.back() == '^')) {
                    result += "(-";
                    while (++i < s.size() && (isalpha(s[i]) || isdigit(s[i]) || s[i] == '.')) {
                        result += s[i];
                    }
                    result += ')';
                    i--; 
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


        // Insert '*' sign where necessary
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

        // handle the last operator except = if exist
        if (isOperator(s.back()))
        {
            result  = "There is an ERROR !! there was a extra operator in the end \n ";
            return result ;
        }


        result += s[i];
    }


    // manfi daron parantez
    for (int i = 0; i < s.size(); i++)
    {
        if ((isdigit(s[i]) && s[i + 1] == '(') || (s[i] == ')' && s[i + 1] == '(') || (s[i] == ')' && isdigit(s[i + 1])))
            s.insert(s.begin() + i + 1, '*');
    }


    // zarb beiin parantez
    for (int i = 0; i < s.size(); i++)
    {
        if ((isdigit(s[i]) && s[i + 1] == '(') || (s[i] == ')' && s[i + 1] == '(') || (s[i] == ')' && isdigit(s[i + 1])))
            s.insert(s.begin() + i + 1, '*');
    }

    //result 
    if (s[0] == '-')
        s.insert(s.begin(), '0');

    // Ensure the string starts correctly
    if (!result.empty() && result[0] == '-') {
        result.insert(result.begin(), '0');
    }
    return result;

}

string convertToPostfix(string str)
{
    Stack<char> operators;
    string postfix;
    for (size_t i = 0; i < str.size(); ++i)
    { 
        if (isdigit(str[i]))
        {
            size_t start = i;
            while (i < str.length() && (isdigit(str[i]) || str[i] == '.'))
            {
                ++i;
            }
            string numberStr = str.substr(start, i - start);
            postfix += numberStr;
            postfix += ' ';
            --i; 
        }
    

        // if is number add in string 
        else if (str[i] == '(')
        {
            operators.push(str[i]);
        }
        // age ( add toye stack  


        else if(str[i] == ')')
        {
            while (operators.peek() != '(')
            {
                postfix += operators.pop() ;
                postfix += ' ';
            }
            operators.pop();
        }//age ) ta vaqti be ( naresidim az stack kharej mikonim toye string 

        else if (isOperator(str[i]))
        {
            int newpri = priority(str[i]);
            int inStack_pri = priority(operators.peek());

            if(newpri <=inStack_pri)
            {   
                //AddElement(&postfix, &operators, newpri);
                while (!operators.isEmpty() && newpri <= inStack_pri) 
                {
                    postfix += operators.pop() ;
                    postfix += ' ';
                }
            }
            operators.push(str[i]);
        }
    }

        while (!operators.isEmpty())
        {
            postfix += operators.pop();
            postfix += ' ';
        }
    return postfix;
}
// final calculation :
double calculate_postfix(string s)
{
    Stack<double> values;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ')
        {
            continue;
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
        else if (isOperator(s[i]))
        {
            //x-y
            double y = values.pop();
            double x = values.pop();
            double answer = calculator(s[i],x, y);
            
            values.push(answer);
        }
        else
        {
            break; 
        }
    }
    return values.pop();

}
