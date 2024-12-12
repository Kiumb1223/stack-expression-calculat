# Readme

> 计算机如何对表达式进行求值
>
> 本文档主要参考于:point_right:[ 表达式求值---（中缀表达式转后缀表达式及后缀表达式求值结合）_Hunter_Kevin的博客-CSDN博客](https://blog.csdn.net/Hunter_Kevin/article/details/110661922?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-1.no_search_link&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~default-1.no_search_link)

* 代码中可能有笔者暂时还未发现的BUG，发现的同学欢迎指正。

## 中缀表达式&后缀表达式

* 中缀表达式：运算符号位于两个运算数之间。如，$a+b*c-d/e$
* 后缀表达式：运算符号位于两个运算数之后。如，$a bc*+de/-$
	* 转换方式：（方法之一）
		1. 先按照运算符的优先级对中缀表达式加括号  -----> $((a+(b*c))-(d/e))$
		2. 将运算符移到括号的后面                                   ----->$((a(bc)*)+(de)/)-$
		3. 去掉括号                                                                ----->$abc*+de/-$

### 意义

* 中缀表达式对于计算机求值是比较复杂的。如$a+b*c-d/e$ 

	​	**运算符号放在操作数中间**对于计算机来说是非常复杂的结构。

* 反之，碰到运算符号的时候，我们已经实现知道两个操作数了。这种特点的表达式（后缀表达式）对于计算机来说结构更加简单。如$abc*+de/-$

	​    **从左往右扫描，逐个处理运算数和运算符号**

* 因此，我们需要算法实现至少需要两步走：

	1. 将中缀表达式转换为后缀表达式
	2. 后缀表达式如何求值

	* 需要有种存储方法，能顺序存储运算数；并在需要的时候，"倒序"输出

		也就是，”后进先出（Last In First Out）“特点的堆栈这样的逻辑存储结构。

## 堆栈

> 堆栈（Stack）：具有一定操作约束的线性表；**只在一端（栈顶，TOP）**做插入、删除操作。

### 堆栈的抽象数据类型描述

* 类型名称：堆栈（stack）
* 数据对象集：一个有0个或者多个元素的有穷线性表
* 操作集：长度为**MaxSize**的堆栈S∈Stack，堆栈元素item∈ElementType

```c
// 创建一个空栈
void CreatStack(&S);
//将元素X插入到栈S中
ElementType StackPush(&S,X);
//删除栈S中的栈顶元素
ElementType StackPop(&S);
//取栈S中的栈顶元素
ElementType StackGetTop(&S);
//判断栈S是否为空
Bool IsEmpty(&S);
```

### **栈的顺序存储** (顺序栈）

> 栈的物理存储结构是顺序存储结构，通常使用一维数组和一个记录栈顶元素位置的变量组成。

* 数据类型

	```C
	#define MaxSize maxlen  //定义顺序栈的最大容量为maxlen
	#define ERROE   -1      //ERROR是ElementType的特殊值，标志错误 
	typedef int ElementType;
	typedef struct SeqStack
	{
	    ElementType *data;	//数组存放数据
	    int maxsize;		//堆栈的最大容量
	    int top;			//记录栈顶元素位置
	}SeqStack,*PtrSeqStack;
	```

* 操作集（源码）

	```C
	//创建空栈
	PtrSeqStack CreateSeqStack(int max)
	{
	    PtrSeqStack S;
	    S = (PtrSeqStack) malloc(sizeof(SeqStack));
	    S->data = (ElementType *) malloc(sizeof(ElementType)*max);
	    S->maxsize = max;
	    S->top = -1;
	    return S;
	}
	//销毁栈
	void DestroySeqStack(PtrSeqStack S)
	{
	    //先销毁结构体中有分配动态内存的元素，再销毁栈
	    free(S->data);
	    free(S);
	}
	//判断是否满栈
	bool SeqStackisFull(PtrSeqStack S)
	{
	    return (S->top == S ->maxsize-1);
	}
	//判断是否空栈
	bool SeqStackisEmpty(PtrSeqStack S)
	{
	    return (S->top == -1);
	}
	//进栈
	bool SeqStackPush(PtrSeqStack S,ElementType item)
	{
	    if(SeqStackisFull(S))
	    {
	        printf("栈已满！\n");
	        return false;
	    }else{
	        S->data[++(S->top)] = item;
	        return true;
	    }
	}
	//出栈
	ElementType SeqStackPop(PtrSeqStack S)
	{
	    if (SeqStackisEmpty(S))
	    {
	        printf("栈已空！\n");
	        return ERROR;
	    }else{
	        return (S->data[(S->top)--]);
	    }
	}
	//顺序栈栈顶元素查询
	ElementType SeqStackTop(PtrSeqStack S)
	{
	    if (SeqStackisEmpty(S))
	    {
	        printf("栈已空！\n");
	        return ERROR;
	    }else{
	        return (S->data[S->top]);
	    }
	}
	//顺序栈元素遍历
	void SeqStackShow(PtrSeqStack S)
	{
	    for (int i = 0; i < S->top; ++i) {
	        printf("StackData[%d] is %d\n",i,S->data[i]);
	    }
	}
	//清空顺序栈
	void SeqStackClear(PtrSeqStack S)
	{
	    S->top = -1;
	}
	```

### **栈的链式存储**（链式栈）

> 栈的链式存储结构是一种限制运算的链表——规定链表中的插入和删除运算只能在链表的开头进行

* 数据结构

	```C
	typedef int ElementType;
	typedef struct ListStack
	{
	    ElementType data;
	    struct ListStack *next;
	}ListStack,*PListStack;
	```

* 操作集（源码）

	```C
	//链表的head指针每个人的理解都存在差异，故每个人的链表的实现方式都有所不同
	//比如：head指针可以理解为栈顶元素或者head指针结构于结构体栈一样被分配了动态内存而独立于堆栈元素或者head指针单纯的指向栈顶元素。
	//创建链栈、判断空链栈、入栈、出栈、销毁栈、清空栈、遍历栈、查询栈顶元素
	//by Kiumb
	//创建链栈
	PListStack CreateListStack()
	{
	    PListStack S = NULL;
	    S = (PListStack) malloc(sizeof(ListStack));
	    S->next = NULL;
	    return S;
	}
	//判断链栈是否空栈
	bool ListStackIsEmpty(PListStack S)
	{
	    return (S->next == NULL);
	}
	//入栈
	void ListStackPush(PListStack S,ElementType item)
	{
	    //S为head指针或者栈顶指针，指向栈顶元素
	    PListStack tmp = NULL;
	    tmp = (PListStack) malloc(sizeof(ListStack));
	    //头插法
	    tmp->data = item;
	    tmp->next = S->next;
	    S->next   = tmp;
	}
	//出栈
	ElementType ListStackPop(PListStack S)
	{
	    PListStack TopCell = NULL;
	    ElementType topElem;
	    if(ListStackIsEmpty(S))
	    {
	        printf("链栈为空，无法操作！\n");
	        return ERROR;
	    }else{
	        TopCell = S -> next;
	        topElem = TopCell->data;
	        S->next = TopCell->next;
	        free(TopCell);
	        return topElem;
	    }
	}
	//链栈清空
	void ListStackClear(PListStack S)
	{
	    PListStack tmpCell = NULL;
	    while (S->next != NULL)
	    {
	        tmpCell = S->next;
	        S->next = tmpCell->next;
	        free(tmpCell);
	    }
	}
	//链栈销毁
	void ListStackDestroy(PListStack S)
	{
	    ListStackClear(S);
	    free(S);
	}
	//遍历栈内元素
	void ListStackShow(PListStack S)
	{
	    PListStack tmp = NULL;
	    int count;
	    for (tmp = S->next,count = 0;tmp;tmp = tmp->next,count++)
	    {
	        printf("The %d-th number is %d\n",count,tmp->data);
	    }
	    putchar('\n');
	}
	//查询栈顶元素
	ElementType ListStackGetTop(PListStack S)
	{
	    return(S->next->data);
	}
	```

### 顺序栈&链式栈对比

* 顺序栈和链式栈的Push和Pop的时间复杂度都为O(1)；
* 顺序栈存在存储元素个数限制和空间浪费的问题；
* 链栈无栈满问题，只有当内存没有可用空间时才会出现栈满，但是每个元素都需要指针域，从而产生结构性开销；
* 当栈在使用过程中元素个数变化较大时，用链栈比较好，反之，应该采用顺序栈。

## 中缀表达式转换为后缀表达式

> 这里我选择使用堆栈的链式存储结构

### 算法流程为：

> 参数表：Opstack(操作符栈)、SuffixExpression(后缀表达式)、InfixExpression(中缀表达式)

1. 循环遍历InfixExpression中的每个元素，并且对不同的元素做如下操作。

	* 如果遇到操作数，则直接输入到SuffixExpression中
		* 并且在操作数后面添加’#‘以表示该操作数结束
		
	* 如果第一次遇到操作符（此时堆栈为空），则直接Push到OpStack中

	* 如果遇到‘ ’ 和‘=’，则直接跳过不处理

	* 如果遇到左括号’('，则直接Push到Opstack中

	* 如果遇到右括号‘)'，则将OpStack中的操作符依次Pop出保存到SuffixExpression中

	* 如果不是第一次遇到操作符，则需**比较当前读取到的操作符和栈顶元素的操作符的优先级**

		1. 如果栈顶元素优先级比当前操作符高：

			则需从栈中弹出元素保存到SuffixExpression中，直到发现更低优先级的元素或者栈为空为止。

		2. 如果栈顶元素优先级比当前操作符低：
	
			则需直接Push当前操作符到OpStack中。
		
		* 对于两个符号优先级，就是正常的优先级。同时，同一优先级是自左向右运算的。
		
			i.e.栈顶元素相较于栈外元素而言，如果两者优先级相同，则栈内元素优先级
	
2. 如果读到了infixExpression的末尾，则将OpStack中的所有元素依次Pop出保存到SuffixExpression中。

### 源码展示：

```C
//Expression.c
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
```

## 后缀表达式求值

### 算法流程

> NumStack(数字栈)、SuffixExpression（后缀表达式）

1. 遍历后缀表达式，并且对不同的元素做如下操作：
	* 如果遇到操作数，则一直读取直到读到数字结束符’#‘，并且将读取到的数字Push到NumStack中
	* 如果遇到操作符，则向栈Pop出两个数字进行对应的运算，并且将运算的结果继续Push到栈内
2. 遍历结束后缀表达式之后，将栈内的最后一个数字Pop出来，当作整个后缀表达式求值的结果。

### 源码展示

```C
//Expression.c
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
```

## 工程文件获取

> 我将整个工程文件打包上传到:point_right:[码云](https://gitee.com/Kiumb/stack_-expression-calculate/):point_left:，以方便管理

### 工程文件结构

![image-20211208002824715](https://gitee.com/Kiumb/pic-bed_typora/raw/master/img/image-20211208002824715.png)

## 算法不足

> 针对于整个工程，我将从一个程序编写过程IPO[^1]三个部分来反思这个项目的不足。

### Input

* 命令行输入，可以尝试使用QT设置基本界面

* 没有检查表达式合法性的功能、只简单地检查了一下表达式中有没有不合法字符

### Process

* ElementType设置为int型，说明能进行运算的数字范围为0~2147483647。不能进行更大数字运算。
* 同时因为ElementType为int型，所以只能进行整数的运算。
* 只支持四则运算，还缺少^、log等等操作符
* 输入数据还不够多，暂时还无法检查出BUG

### Output

* 命令行输出，可以尝试使用QT设置基本UI界面

## FootNotation

[^1]:I-input;P-process;O-output







