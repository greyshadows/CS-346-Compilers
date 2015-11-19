#include<iostream>
#include<stack>
#include<cstdlib>
#include<string>
#include "dfa.h"

using namespace std;
int priority (char op)
{
    int weight = -1;
    switch(op)
    {
        case '+':
            weight = 1;
            break;
        case '.':
            weight = 2;
            break;
        case '*':
            weight = 3;
    }
    return weight;
}

int HigherPriority(char op1, char op2)
{
    int op1Weight = priority(op1);
    int op2Weight = priority(op2);

    return op1Weight > op2Weight ? true: false;
}


bool Is_operator(char C)
{
    if(C == '+' || C == '.' || C == '*')
        return true;

    return false;
}

bool Is_operand(char C)
{
    if(C == 'a' || C == 'b') return true;
    return false;
}

string InfixToPostfix(string expression)
{
    stack<char> S;
    string postfix = "";
    for(int i = 0;i< expression.length();i++) {

        if(Is_operator(expression[i]))
        {
            while(!S.empty() && S.top() != '(' && HigherPriority(S.top(),expression[i]))
            {
                postfix+= S.top();
                S.pop();
            }
            S.push(expression[i]);
        }
        else if(Is_operand(expression[i])) {
                postfix +=expression[i];
        }

        else if (expression[i] == '(')
        {
            S.push(expression[i]);
        }

        else if(expression[i] == ')')
        {
            while(!S.empty() && S.top() != '(') {
                postfix += S.top();
                S.pop();
            }
            S.pop();
        } else {
            cerr << "Invalid characer" << endl;
        }
    }

    while(!S.empty()) {
        postfix += S.top();
        S.pop();
    }

    return postfix;
}