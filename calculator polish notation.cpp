#include<iostream>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

using namespace std;

  struct Calculator
{
 
    void infix_to_postfix();
    int priority(char symbol);
    int isEmpty();
    int isSpace(char);
    int count();
    void push(int symbol);
    int pop();
};

char infix[300], postfix[300];
int stack[300], counter;

int main()
{
    Calculator pnotation;
    counter = -1;
    cout << "Enter the equation : ";
    gets_s(infix);
    pnotation.infix_to_postfix();
    cout << "Reverse polish notation : " << postfix << endl;
    cout << "Result= " << pnotation.count() << endl;
    return 1;
}
//запис в польскій нотації
void  Calculator::infix_to_postfix()
{
    int i, p = 0;
    char next;
    char symbol;
    for (i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];
        if (!isSpace(symbol))
        {
            switch (symbol)
            {
            case '(':
                push(symbol);
                break;
            case ')':
                while ((next = pop()) != '(')
                    postfix[p++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!isEmpty() && priority(stack[counter]) >= priority(symbol))
                    postfix[p++] = pop();
                push(symbol);
                break;
                // для запису цифр
            default: 
                postfix[p++] = symbol;
            }
        }
    }
    while (!isEmpty())
        postfix[p++] = pop();
    //перетворюємо масив в рядок
    postfix[p] = '\0'; 
}

//пріоритет операцій
int  Calculator::priority(char symbol)
{
    switch (symbol)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void  Calculator::push(int symbol)
{
    if (counter > 300)
    {
        cout << "Stack overflow"<<endl;
        exit(1);
    }
    stack[++counter] = symbol;
}

int  Calculator::pop()
{
    if (isEmpty())
    {
        cout << "Stack is empty"<<endl;
        exit(1);
    }
    return (stack[counter--]);
}


int  Calculator::isEmpty()
{
    if (counter == -1)
        return 1;
    else
        return 0;
}
//зайві пробіли
int  Calculator::isSpace(char symbol)
{
    if (symbol == ' ' || symbol == '\n'|| symbol=='\t')
        return 1;
    else
        return 0;
}
//підрахунок
int  Calculator::count()
{
    int a, b, i, value, result;
    for (i = 0; i < strlen(postfix); i++)
    {
        if (postfix[i] <= '9' && postfix[i] >= '0')
            push(postfix[i] - '0');
        else
        {
            a = pop();
            b = pop();
            switch (postfix[i])
            {
            case '+':
                value = b + a;
                break;
            case '-':
                value = b - a;
                break;
            case '*':
                value = b * a;
                break;
            case '/':
                value = b / a;
                break;
            case '%':
                value = b % a;
                break;
            case '^':
                value = pow(b, a);
            }
            push(value);
        }
    }
    result = pop();
    return result;
}