#pragma once
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1


//基本功能
int CharCount(char *path);		//字符统计函数 -c
int WordCount(char *path);		//单词统计函数 -w
int LineCount(char *path);		//函数统计函数 -l

void UebrigFunktion(char *path);	//复杂行数统计函数
int EmptylineCount(char *path);		//空行统计函数
int CoCount(char *path);			//注释行统计函数
int CodeCount(char *path);		//代码统计函数

void Filefind(char *path,char *filename);		//递归查找文件