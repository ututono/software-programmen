// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE

#include "stdafx.h"


int main()
{
	int charcount = 0;
	int wordcount = 0;
	int linecount = 0;


	while (1)
	{
		char ch[5];
		char path[500];
		char filename[500];
		printf("Please input the key:WC.exe \t");
		scanf("%s", ch);
		if (ch[1] == 'c')
		{
			printf("Lage der Datei: \n");
			scanf("%s", path);
			charcount = CharCount(path);
			printf("Char Gesamtheit: %d\n", charcount);
		}
		else if (ch[1] == 'w')
		{
			printf("Lage der Datei: \n");
			scanf("%s", path);
			wordcount = WordCount(path);
			printf("Word Gesamtheit: %d\n", wordcount);
		}
		else if (ch[1] == 'l')
		{ 
			printf("Lage der Datei: \n");
			scanf("%s", path);
			linecount = LineCount(path);
			printf("Line Gesamtheit: %d\n", linecount);
		}
		else if (ch[1] == 'a')
		{
			printf("Lage der Datei: \n");
			scanf("%s", path);
			UebrigFunktion(path);
		}
		else if (ch[1] == 's')
		{
			printf("Lage der Datei: \n");
			scanf("%s", path);
			printf("Filename(support wildcard): \n");
			scanf("%s", filename);
			Filefind(path, filename);
		}
		else if (ch[1] == 'x')
		{
			system("start W:\\GITrepository\\software-programmen\\ConsoleApplication1\\Debug\\MFCApplication2.exe");		//位置写死
		}
		else {
			printf("%s Commend is no fund. \n",ch);
			printf("-x;-w;-a;-c;-s\n");
		}
	}
    return 0;
	getchar();
}

