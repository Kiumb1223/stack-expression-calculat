#include "./HeadFile/Config.h"
#include "./HeadFile/Stack.h"
//��������ջ
PListStack CreateStack()
{
    PListStack S = NULL;
    S = (PListStack) malloc(sizeof(ListStack));
    S->next = NULL;
    return  S;
}
//��ջ����
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
//�ж���ջ�Ƿ�Ϊ��
bool isEmpty(PListStack S)
{
    return (S-> next == NULL);
}
//��ջ
void Push(PListStack S,ElementType item)
{
    PListStack tmpCell = NULL;
    tmpCell = (PListStack) malloc(sizeof(ListStack));
    tmpCell->data = item;
    tmpCell->next = S->next;
    S->next       = tmpCell;
}
//��ջ
ElementType Pop(PListStack S)
{
    ElementType topitem;
    PListStack topCell = NULL;
    if(isEmpty(S))
    {
        printf("��ջΪ�գ��޷�POP��\n");
        return ERROR;
    }else{
        topCell = S->next;
        topitem = topCell->data;
        S->next = topCell->next;
        free(topCell);
        return topitem;
    }
}
//��ѯջ��Ԫ��
ElementType GetTopStack(PListStack S)
{
    if(isEmpty(S))
    {
//        printf("ջ�ѿգ��޷���ѯ��\n");
        return ERROR;
    }
    return (S->next->data);
}