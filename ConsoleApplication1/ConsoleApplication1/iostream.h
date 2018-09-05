#pragma once
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1
#define OVERFLOW    -2 

//基本功能
int CharCount(char *path);		//字符统计函数 -c
int WordCount(char *path);		//单词统计函数 -w
int LineCount(char *path);		//函数统计函数 -l