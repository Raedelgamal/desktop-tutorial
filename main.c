#include "stack.h"
#include <stdbool.h>
#define MAX 20

int compitable(char ,char);
int arebalanced (char[]);

int main()
{   int i=0;
    char c, exp[MAX];
    printf("enter some braces \n");
    while ((c=getchar())!='\n')
    {
        if (c!='\0')
        {
            exp[i++]=c;

        }
        else
            continue;
    }


    if (arebalanced (exp))
        printf(" balanced");
    else
        printf(" not balanced ");


    return 0;
}

int arebalanced (char exp[])
{
    int i=0;
     StackEntry poped;
    stack stack1;
    CreateStack(&stack1);

    while (exp[i])
    {
        if (exp[i]=='{' || exp[i]=='[' || exp[i]=='(')
                {
                    push(exp[i],&stack1);
                }
        else if (exp[i]=='}' || exp[i]==']' ||exp[i]==')')
        {
            if (StackEmpty(&stack1))
                {return 0;}
            else if(!compitable(pop(&poped,&stack1),exp[i]))
                {return 0;}
         }
        i++;
    }
    return !StackEmpty(&stack1);
}

int compitable(char ch1,char ch2)
{
    if (ch1=='{' && ch2=='}')
        return 1;
    else if (ch1=='[' && ch2==']')
        return 1;
    else if (ch1== '(' && ch2==')')
        return 1;
    else
        return 0;
}
