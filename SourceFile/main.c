#include "./HeadFile/Config.h"
#include "./HeadFile/Expression.h"
int main()
{
    char infixExpression[MaxSize];
    char *SuffixExpression;
    printf("请输入标准形式的表达式(支持运算符为‘+’、‘-’、‘*’、’/‘）：\n");
    gets(infixExpression);
    if(CheckExpression(infixExpression))
    {
        SuffixExpression = ToSuffixExperssion(infixExpression);
        printf("后缀表达式为：");
        puts(SuffixExpression);
        printf("表达式的计算值为：%d\n", TackleSuffixExpression(SuffixExpression));
    } else {
        printf("输入的表达式存在错误!\n程序异常退出!\n");
        exit(1);
    }
    return 0;
}