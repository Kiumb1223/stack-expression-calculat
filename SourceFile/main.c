#include "./HeadFile/Config.h"
#include "./HeadFile/Expression.h"
int main()
{
    char infixExpression[MaxSize];
    char *SuffixExpression;
    printf("�������׼��ʽ�ı��ʽ(֧�������Ϊ��+������-������*������/������\n");
    gets(infixExpression);
    if(CheckExpression(infixExpression))
    {
        SuffixExpression = ToSuffixExperssion(infixExpression);
        printf("��׺���ʽΪ��");
        puts(SuffixExpression);
        printf("���ʽ�ļ���ֵΪ��%d\n", TackleSuffixExpression(SuffixExpression));
    } else {
        printf("����ı��ʽ���ڴ���!\n�����쳣�˳�!\n");
        exit(1);
    }
    return 0;
}