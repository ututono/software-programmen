#include"stdafx.h"

char str[500];

int CharCount(char * path)
{
	FILE *fp = NULL;
	int c = 0;
	char ch;
	//int laenge = strlen(path);						//计算文件名长度
	if ((fp = fopen(path, "r")) == NULL)		//判空
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
	if ((fp = fopen(path, "r")) == NULL)		//判空
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
	if ((fp = fopen(path, "r")) == NULL)		//判空
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		if (fgets(str, sizeof(str),fp))
			n++;
	}
	fclose(fp);
	return n;
}

void UebrigFunktion(char * path)
{
	int emptylinecount = 0;
	printf("Emptylinecount: %d\n", EmptylineCount(path));
	printf("Codelinecount: %d\n", CodeCount(path));
	printf("Commentoutlinecount: %d\n", CoCount(path));
}

int EmptylineCount(char * path)
{
	FILE *fp = NULL;
	int n = 0;

	if ((fp = fopen(path, "r")) == NULL)		//判空
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		int tag = 0;
		int len = 0;
		int tag1 = 0;												//tag1<2表示行内只有格式控制符或者单个 '}' '{'
		if (fgets(str, sizeof(str), fp))
		{
				for(len = 0;(len<strlen(str)&&(tag1<2));len++)
				{
					if (str[0] == '\n')
					{
						n++;
						break;
					}
					else if (!(str[len] == '\n' || str[len] == '\t' || str[len] == ' '))
					{
						if (str[len] == '{' || str[len] == '}'&& !tag1)
							tag1=1;
						else tag1 = 2;
					}
					if (len == strlen(str) - 1) n++;				//如果行内只有格式控制符或者单个 '}' '{'则为空行
				} 
		}
		

	}
	fclose(fp);
	return n;
}

int regelwordcount(char *strtemp)					//每行合法字符个数统计,不计入格式控制字符和注释
{
	int n = 0;
	int len = 0;
	int tag1 = 0;
	for (len = 0; (len < strlen(strtemp) && (tag1 < 2)); len++)
		if (!(strtemp[len] == '\n' || strtemp[len] == '\t' || strtemp[len] == ' '))
			if ((strtemp[len] == '/'&& strtemp[len + 1] == '/') || (strtemp[len] == '/'&& strtemp[len + 1] == '*'))
				break;
			else n++;
	return n;
}

int CodeCount(char * path)
{
	FILE *fp = NULL;
	int n = 0;
	int len = 0;
	int tag1 = 0;
	if ((fp = fopen(path, "r")) == NULL)		//判空
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		if (fgets(str, sizeof(str), fp))
		{
			if (regelwordcount(str) > 2) n++;
		}
	}
	fclose(fp);
	return n;
}

int CoCount(char * path)
{
	return LineCount(path)-EmptylineCount(path)-CodeCount(path);
}


