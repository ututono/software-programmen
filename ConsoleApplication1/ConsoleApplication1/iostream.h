#pragma once
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define IBFEASIBLE  -1


//��������
int CharCount(char *path);		//�ַ�ͳ�ƺ��� -c
int WordCount(char *path);		//����ͳ�ƺ��� -w
int LineCount(char *path);		//����ͳ�ƺ��� -l

void UebrigFunktion(char *path);	//��������ͳ�ƺ���
int EmptylineCount(char *path);		//����ͳ�ƺ���
int CoCount(char *path);			//ע����ͳ�ƺ���
int CodeCount(char *path);		//����ͳ�ƺ���

void Filefind(char *path,char *filename);		//�ݹ�����ļ�