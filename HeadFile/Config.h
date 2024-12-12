#ifndef _CONFIG_H
#define _CONFIG_H
//标准库文件引用
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>   //调用isdigit()

#define DEBUG_PRINT(format,...) printf(# format,## __VA_ARGS__); //调试接口
#define MaxSize 100   //限制后缀表达式的长度，也即限制输入的中缀表达式长度
#endif
