#include "./HeadFile/Config.h"
#include "./HeadFile/Stack.h"
//´´½¨¿ÕÁ´Õ»
PListStack CreateStack()
{
    PListStack S = NULL;
    S = (PListStack) malloc(sizeof(ListStack));
    S->next = NULL;
    return  S;
}
//Á´Õ»Ïú»Ù
void DestroyStack(PListStack S)
{
    PListStack tmpCell = NULL;
    while (S->next != NULL)
    {
        tmpCell = S->next;
        S->next = tmpCell->next;
        free(tmpCell);
    }
    free(S);
}
//ÅĞ¶ÏÁ´Õ»ÊÇ·ñÎª¿Õ
bool isEmpty(PListStack S)
{
    return (S-> next == NULL);
}
//ÈëÕ»
void Push(PListStack S,ElementType item)
{
    PListStack tmpCell = NULL;
    tmpCell = (PListStack) malloc(sizeof(ListStack));
    tmpCell->data = item;
    tmpCell->next = S->next;
    S->next       = tmpCell;
}
//³öÕ»
ElementType Pop(PListStack S)
{
    ElementType topitem;
    PListStack topCell = NULL;
    if(isEmpty(S))
    {
        printf("Á´Õ»Îª¿Õ£¬ÎŞ·¨POP£¡\n");
        return ERROR;
    }else{
        topCell = S->next;
        topitem = topCell->data;
        S->next = topCell->next;
        free(topCell);
        return topitem;
    }
}
//²éÑ¯Õ»¶¥ÔªËØ
ElementType GetTopStack(PListStack S)
{
    if(isEmpty(S))
    {
//        printf("Õ»ÒÑ¿Õ£¬ÎŞ·¨²éÑ¯£¡\n");
        return ERROR;
    }
    return (S->next->data);
}