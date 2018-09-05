#include"stdafx.h"

char str[500];

int CharCount(char * path)
{
	FILE *fp = NULL;
	int c = 0;
	char ch;
	//int laenge = strlen(path);						//¼ÆËãÎÄ¼şÃû³¤¶È
	if ((fp = fopen(path, "r")) == NULL)		//ÅĞ¿Õ
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while(!feof(fp))
	{
		fscanf(fp, "%s", str);
		c = c + strlen(str);
	}
	fclose(fp);
	return c;
}

int WordCount(char * path)	
{
	FILE *fp = NULL;
	int n = 0;
	if ((fp = fopen(path, "r")) == NULL)		//ÅĞ¿Õ
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while(!feof(fp))
	{
		if (fscanf(fp, "%s", str)&&!(str[0]>='0'&&str[0]<='9'))
			n++;
	}
	fclose(fp);

	return n;
}

int LineCount(char * path)
{

	FILE *fp = NULL;
	int n = 0;
	if ((fp = fopen(path, "r")) == NULL)		//ÅĞ¿Õ
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		if (fgets(str,200,fp))
			n++;
	}
	fclose(fp);
	return n;
}
