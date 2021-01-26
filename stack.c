#include "stack.h"

void CreateStack(stack *pstack)
{
    pstack->top=NULL;
}

void push (StackEntry e,stack *pstack)
{
    stacknode *pnode=(stacknode *) malloc (sizeof (stacknode));
    pnode->entry=e;
    pnode->next=pstack->top;
    pstack->top=pnode;
}

int pop (StackEntry *pe,stack *pstack)
{
    stacknode *pnode;
    *pe=pstack->top->entry;
    pnode=pstack->top;
    pstack->top=pstack->top->next;
    free(pnode);
    return *pe;
}

int StackEmpty(stack *pstack)
{
    return pstack->top==NULL;
}

int StackFull(stack *pstack)
{
    return 0;
}

void ClearStack (stack *pstack)
{
    stacknode *pnode=pstack->top;
    while (pnode)
        {
           pnode=pnode->next;
           free(pstack->top);
           pstack->top=pnode;
        }
}

void TraverseStack(stack *pstack ,void (*pf)(StackEntry))
{
    stacknode *pnode=pstack->top;
    while (pnode)
    {
        (*pf) (pnode->entry);
        pnode=pnode->next;
    }

}

int StackSize(stack *pstack)
{
    int x;
    stacknode *pnode=pstack->top;
    for ( x =0;pnode;pnode=pnode->next)
    {
        x++;
    }
    return x;
}
