#include "./HeadFile/Config.h"
#include "./HeadFile/Expression.h"
#include "./HeadFile/Stack.h"
//比较两个栈顶操作符和当前符号的优先级
//return true  栈顶操作符优先级比当前符号高
//return false 栈顶操作符优先级比当前符号低
bool ComparePriority(PListStack S,char CurOp)
{
    //栈顶操作符对于相同的却不在栈内的操作符具有天然的高优先级
    //因为对于四则运算的操作符来说：同优先级的运算符，通常的运算顺序是自左向右的
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
//运算a op b
//运算符op为双元运算符
//暂时只支持+-*/这四元运算符
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
//读到非法字符（除了’+‘、’-‘、’*‘、’/‘、’ ‘、’ =‘）会强制退出程序
bool CheckExpression(char *Expression)
{
    int index = 0;
    while(Expression[index] != '\0')
    {
        if(isdigit(Expression[index]))
        {
            break;
        }else{
            //读到非数字
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
//将中缀表达式变成后缀表达式并返回
char *ToSuffixExperssion(char *infixExpression)
{
    static char suffix[MaxSize];    //静态局部变量的生命周期为整个程序，作用域为该函数
    int index_infix = 0,index_suffix = 0;
    //创建操作符栈OpStack
    PListStack Opstack = NULL;
    Opstack = CreateStack();
    while(infixExpression[index_infix] != '\0')
    {
        if(isdigit(infixExpression[index_infix]))
        {//遇到操作数，直接将其输出
            suffix[index_suffix++] = infixExpression[index_infix];
            if(!isdigit(infixExpression[index_infix+1]))
            {//使用#来分隔数字，以此来实现多位数字的运算
                suffix[index_suffix++] = '#';
            }
        }else if(infixExpression[index_infix] == ' ' || infixExpression[index_infix] == '=')
        {
            //No operation!
        } else {//读取到操作符
            if(infixExpression[index_infix] == '(' || isEmpty(Opstack))
            {//当读到操作符(或者当前栈为空，则直接入栈
                Push(Opstack,infixExpression[index_infix]);
            } else if(infixExpression[index_infix] == ')')
            {//当读到的操作符是')'时，需要一直出栈操作符，直到栈顶元素为'('
                do {
                    suffix[index_suffix++]=Pop(Opstack);
                } while (GetTopStack(Opstack) == ')');
                Pop(Opstack);   //丢弃'('
            } else if(ComparePriority(Opstack,infixExpression[index_infix]) == true)
            {//栈顶操作符的优先级比当前操作符优先级高，则需要从栈中一直出栈操作符，直到栈顶的优先级比当前操作符低，或者栈为空
                do {
                    suffix[index_suffix++] = Pop(Opstack);
                } while (ComparePriority(Opstack,infixExpression[index_infix]) == true && !isEmpty(Opstack));
                Push(Opstack,infixExpression[index_infix]);
            } else if(ComparePriority(Opstack,infixExpression[index_infix]) == false)
            {//栈顶元素的优先级低于当前操作符，则直接入栈
                Push(Opstack,infixExpression[index_infix]);
            }
        }
        //if语句执行完毕，跳转中缀表达式的下一字符
        index_infix++;
    }
    //取出操作符栈到suffix中,直到堆栈为空
    do {
        suffix[index_suffix++] = Pop(Opstack);
    }while(!isEmpty(Opstack));
    //添加结束符
    suffix[index_suffix] = '\0';
    //销毁操作符栈
    DestroyStack(Opstack);
    return suffix;
}
//后缀表达式求值
// 参数为指向常量的常量指针，防止函数体内对后缀表达式中修改以及修改指针指向
int TackleSuffixExpression(const char * const SuffixExpression)
{
    int value;
    int index_suffix = 0;
    ElementType num = 0;        //堆栈能保存的数字范围为0~2147483647
    //建立数字栈
    PListStack NumStack = CreateStack();
    while(SuffixExpression[index_suffix] != '\0')
    {
        if(isdigit(SuffixExpression[index_suffix]))
        {//读到数字,必须一直读到#结束符，以保证多位数能进行运算
            while(SuffixExpression[index_suffix] != '#')
            {
                num = num*10 + SuffixExpression[index_suffix++]-'0';
            }
            Push(NumStack,num);
            num = 0;
        } else {//读到操作符
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