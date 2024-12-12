#ifndef _STACK_H
#define _STACK_H
typedef int ElementType;
#define ERROR (-1)
typedef struct ListStack
{
    ElementType data;
    struct ListStack *next;
}ListStack,*PListStack;

PListStack CreateStack();
void DestroyStack(PListStack);
bool isEmpty(PListStack);
void Push(PListStack,ElementType);
ElementType Pop(PListStack);
ElementType GetTopStack(PListStack);
#endif
