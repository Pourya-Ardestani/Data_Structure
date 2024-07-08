#include <iostream>
#include <string>
#include <cmath>
#include "Stack.h"
using namespace std; 


string fixString(string s); // add prototype and parameters 
void AddElement(string*, Stack<char>* , int);
string convertToPostfix(string );
void paranthes(string*, Stack<char>*);

//////////////////////////




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
    //+++++++++++++++++++++++++++++
    }*/
    s = fixString(s);
    cout << "\n after fix : " <<  s;
    string postfix;
    postfix = convertToPostfix(s);

    cout << "\n after convert : "<< postfix;
    
    
    
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

bool myLetter(char c)
{
    if (c == 's' or c == 'c' or c == 't' or c == 'e' or c == 'P')
        return true;
    return false;
}

bool isOperator(char c)
{
    if (c == '/' or c == '*' or c == '+' or c == '-' or c == '^' or c == '=')
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


    // Handle multiple signs    
    for (size_t i = 0; i < s.size(); ++i) {

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

        // handle the last operator exept = if exist
        if (isOperator(s.back()))
        {
            result  = "ERROR !! there was a extra operator in the end  ";
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
            postfix+=str[i];
        } 
        // age  addae add toye string 

        else if (str[i] == '(')
        {
            operators.push(str[i]);
        }
        // age ( add toye stack  


        else if(str[i] == ')')
        {
            while (operators.peek() != ')')
            {
                cout << 's';
                postfix += operators.pop();
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
                    postfix += operators.pop();
                }
            }
            operators.push(str[i]);
        }
    }
    //#TODO dar akhar harchi to stack hast bayad khaly she to post fix
    //AddElement(&postfix,& operators );
        while (!operators.isEmpty())
        {
            postfix += operators.pop();
        }
    return postfix;
}

//void AddElement(string * post ,Stack<char> *stack )
//{
//    while (!stack->isEmpty() &&  n >= stack->peek())
//    {
//        *post += stack->pop();
//    }
//
//}
