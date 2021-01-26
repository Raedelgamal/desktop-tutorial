#ifndef STACK_LINK_H_INCLUDED
#define STACK_LINK_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>


typedef char StackEntry;

typedef struct stacknode
{
    StackEntry entry ;
    struct stacknode *next;
}stacknode;
typedef struct stack
{
    stacknode *top;
}stack;

void CreateStack   (stack *);
void push          (StackEntry ,stack *);
int pop		   (StackEntry *, stack *);
int	 StackEmpty	   (stack *);
int	 StackFull	   (stack *);
void ClearStack	   (stack *);
int	 StackSize	   (stack *);
int StackTop	   (stack *);
void TraverseStack (stack *, void (*)(StackEntry));



#endif // STACK_LINK_H_INCLUDED
