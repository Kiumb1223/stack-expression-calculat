#include "./HeadFile/Config.h"
#include "./HeadFile/Expression.h"
#include "./HeadFile/Stack.h"
//�Ƚ�����ջ���������͵�ǰ���ŵ����ȼ�
//return true  ջ�����������ȼ��ȵ�ǰ���Ÿ�
//return false ջ�����������ȼ��ȵ�ǰ���ŵ�
bool ComparePriority(PListStack S,char CurOp)
{
    //ջ��������������ͬ��ȴ����ջ�ڵĲ�����������Ȼ�ĸ����ȼ�
    //��Ϊ������������Ĳ�������˵��ͬ���ȼ����������ͨ��������˳�����������ҵ�
    switch (GetTopStack(S)) {
        case '+':
        case '-':
            if(CurOp == '+' || CurOp == '-')
                return true;
            break;
        case '*':
        case '/':
            return true;
        case '(':
            return false;
        default:
            break;
    }
    return false;
}
//����a op b
//�����opΪ˫Ԫ�����
//��ʱֻ֧��+-*/����Ԫ�����
int Calculate(char op,int a,int b)
{
    int result = 0;
    switch (op) {
        case '+':result = a+b;break;
        case '-':result = a-b;break;
        case '*':result = a*b;break;
        case '/':result = a/b;break;
        default:break;
    }
    return result;
}
//�����Ƿ��ַ������ˡ�+������-������*������/������ ������ =������ǿ���˳�����
bool CheckExpression(char *Expression)
{
    int index = 0;
    while(Expression[index] != '\0')
    {
        if(isdigit(Expression[index]))
        {
            break;
        }else{
            //����������
            switch (Expression[index]) {
                case '+':
                case '-':
                case '*':
                case '/':
                case ' ':
                case '=':
                    break;
                default:
                    return false;
            }
        }
        index++;
    }
    return true;
}
//����׺���ʽ��ɺ�׺���ʽ������
char *ToSuffixExperssion(char *infixExpression)
{
    static char suffix[MaxSize];    //��̬�ֲ���������������Ϊ��������������Ϊ�ú���
    int index_infix = 0,index_suffix = 0;
    //����������ջOpStack
    PListStack Opstack = NULL;
    Opstack = CreateStack();
    while(infixExpression[index_infix] != '\0')
    {
        if(isdigit(infixExpression[index_infix]))
        {//������������ֱ�ӽ������
            suffix[index_suffix++] = infixExpression[index_infix];
            if(!isdigit(infixExpression[index_infix+1]))
            {//ʹ��#���ָ����֣��Դ���ʵ�ֶ�λ���ֵ�����
                suffix[index_suffix++] = '#';
            }
        }else if(infixExpression[index_infix] == ' ' || infixExpression[index_infix] == '=')
        {
            //No operation!
        } else {//��ȡ��������
            if(infixExpression[index_infix] == '(' || isEmpty(Opstack))
            {//������������(���ߵ�ǰջΪ�գ���ֱ����ջ
                Push(Opstack,infixExpression[index_infix]);
            } else if(infixExpression[index_infix] == ')')
            {//�������Ĳ�������')'ʱ����Ҫһֱ��ջ��������ֱ��ջ��Ԫ��Ϊ'('
                do {
                    suffix[index_suffix++]=Pop(Opstack);
                } while (GetTopStack(Opstack) == ')');
                Pop(Opstack);   //����'('
            } else if(ComparePriority(Opstack,infixExpression[index_infix]) == true)
            {//ջ�������������ȼ��ȵ�ǰ���������ȼ��ߣ�����Ҫ��ջ��һֱ��ջ��������ֱ��ջ�������ȼ��ȵ�ǰ�������ͣ�����ջΪ��
                do {
                    suffix[index_suffix++] = Pop(Opstack);
                } while (ComparePriority(Opstack,infixExpression[index_infix]) == true && !isEmpty(Opstack));
                Push(Opstack,infixExpression[index_infix]);
            } else if(ComparePriority(Opstack,infixExpression[index_infix]) == false)
            {//ջ��Ԫ�ص����ȼ����ڵ�ǰ����������ֱ����ջ
                Push(Opstack,infixExpression[index_infix]);
            }
        }
        //if���ִ����ϣ���ת��׺���ʽ����һ�ַ�
        index_infix++;
    }
    //ȡ��������ջ��suffix��,ֱ����ջΪ��
    do {
        suffix[index_suffix++] = Pop(Opstack);
    }while(!isEmpty(Opstack));
    //��ӽ�����
    suffix[index_suffix] = '\0';
    //���ٲ�����ջ
    DestroyStack(Opstack);
    return suffix;
}
//��׺���ʽ��ֵ
// ����Ϊָ�����ĳ���ָ�룬��ֹ�������ڶԺ�׺���ʽ���޸��Լ��޸�ָ��ָ��
int TackleSuffixExpression(const char * const SuffixExpression)
{
    int value;
    int index_suffix = 0;
    ElementType num = 0;        //��ջ�ܱ�������ַ�ΧΪ0~2147483647
    //��������ջ
    PListStack NumStack = CreateStack();
    while(SuffixExpression[index_suffix] != '\0')
    {
        if(isdigit(SuffixExpression[index_suffix]))
        {//��������,����һֱ����#���������Ա�֤��λ���ܽ�������
            while(SuffixExpression[index_suffix] != '#')
            {
                num = num*10 + SuffixExpression[index_suffix++]-'0';
            }
            Push(NumStack,num);
            num = 0;
        } else {//����������
            int topItem = 0,nextItem = 0;
            topItem  = Pop(NumStack);
            nextItem = Pop(NumStack);
            value    = Calculate(SuffixExpression[index_suffix],nextItem,topItem);
            Push(NumStack,value);
        }
        index_suffix ++;
    }
    value = Pop(NumStack);
    DestroyStack(NumStack);
    return value;
}