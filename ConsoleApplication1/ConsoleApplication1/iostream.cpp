#include"stdafx.h"

char str[500];

int CharCount(char * path)
{
	FILE *fp = NULL;
	int c = 0;
	char ch;
	//int laenge = strlen(path);						//�����ļ�������
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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

	if ((fp = fopen(path, "r")) == NULL)		//�п�
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
	{
		int tag = 0;
		int len = 0;
		int tag1 = 0;												//tag1<2��ʾ����ֻ�и�ʽ���Ʒ����ߵ��� '}' '{'
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
					if (len == strlen(str) - 1) n++;				//�������ֻ�и�ʽ���Ʒ����ߵ��� '}' '{'��Ϊ����
				} 
		}
		

	}
	fclose(fp);
	return n;
}

int regelwordcount(char *strtemp)					//ÿ�кϷ��ַ�����ͳ��,�������ʽ�����ַ���ע��
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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


