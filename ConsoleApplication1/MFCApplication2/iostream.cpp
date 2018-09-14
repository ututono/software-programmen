#include"stdafx.h"
#pragma warning(disable:4996)；

char str[500];

struct m_PATH				//递归查询时储存符合条件的地址
{
	char filename[100];

}m_path[50], m_path1;

const LPCWSTR charstrtowcharstr(char *charstr);
char * wchartochar(const wchar_t* wchar);

int CharCount(char * path)
{

	FILE *fp = NULL;
	int c = 0;
	char ch;
	if ((fp = fopen(path, "r")) == NULL)		//判空
	{
		printf("File read failure.\n");
		exit(-1);
	}
	while (!feof(fp))
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
	while (!feof(fp))
	{
		if (fscanf(fp, "%s", str) && !(str[0] >= '0'&&str[0] <= '9')&&str[0]!='\0')
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
		if (fgets(str, sizeof(str), fp))
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
			for (len = 0; (len < strlen(str) && (tag1 < 2)); len++)
			{
				if (str[0] == '\n')
				{
					n++;
					break;
				}
				else if (!(str[len] == '\n' || str[len] == '\t' || str[len] == ' '))
				{
					if (str[len] == '{' || str[len] == '}' && !tag1)
						tag1 = 1;
					else
					{
						tag1 = 2;
						continue;
					}
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
	unsigned int len = 0;
	for (len = 0; len < strlen(strtemp); len++)
		if (!(strtemp[len] == '\n' || strtemp[len] == '\t' || strtemp[len] == ' '))
		{
			if ((strtemp[len] == '/'&& strtemp[len + 1] == '/') || (strtemp[len] == '/'&& strtemp[len + 1] == '*'))
				break;
			else n++;
		}
		else;
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
			if (regelwordcount(str) > 2 || (regelwordcount(str) == 1 && (str[0] != '}'&&str[0] != '{'))) n++;
		}
	}
	fclose(fp);
	return n;
}

int CoCount(char * path)
{
	return LineCount(path) - EmptylineCount(path) - CodeCount(path);
}

char * wchartochar(const wchar_t* wchar)					//WCHAR转换为CHAR
{
	char * m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

const LPCWSTR charstrtowcharstr(char *charstr)
{

	WCHAR wszClassName[256];
	memset(wszClassName, 0, sizeof(wszClassName));
	MultiByteToWideChar(CP_ACP, 0, charstr, strlen(charstr) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
	return wszClassName;
}


void liemain(char *path)
{
	int charcount = 0;
	int wordcount = 0;
	int linecount = 0;

	while (1)
	{
		char ch[5];
		printf("Please input the key %s: \t", path);
		scanf("%s", ch);
		if (ch[0] == 'c')
		{
			charcount = CharCount(path);
			printf("Gesamtheit: %d\n", charcount);
		}
		else if (ch[0] == 'w')
		{
			wordcount = WordCount(path);
			printf("Gesamtheit: %d\n", wordcount);
		}
		else if (ch[0] == 'l')
		{
			linecount = LineCount(path);
			printf("Gesamtheit: %d\n", linecount);
		}
		else if (ch[0] == 'a')
		{
			UebrigFunktion(path);
		}
		else {
			printf("ERROR\n");
			break;
		}
	}
}

bool MatchWithAsteriskW(char* str1, char* pattern)
{
	if (str1 == NULL) return false;
	if (pattern == NULL) return false;
	int len1 = strlen(str1);
	int len2 = strlen(pattern);
	int mark = 0;//用于分段标记,'*'分隔的字符串
	int p1 = 0, p2 = 0;

	while (p1 < len1 && p2 < len2)
	{
		if (pattern[p2] == '?')
		{
			p1++;
			p2++;
			continue;
		}
		if (pattern[p2] == '*')
		{
			/*如果当前是*号，则mark前面一部分已经获得匹配，
			*从当前点开始继续下一个块的匹配
			*/
			p2++;
			mark = p2;
			continue;
		}
		if (str1[p1] != pattern[p2])
		{
			if (p1 == 0 && p2 == 0)	//如果是首字符，特殊处理，不相同即匹配失败
			{
				return false;
			}
			/*
			* p2返回到mark处，
			* p1需要返回到下一个位置。
			* 因为*前已经获得匹配，所以mark打标之前的不需要再比较
			*/
			p1 -= p2 - mark - 1;
			p2 = mark;
			continue;
		}
		/*
		* 此处处理相等的情况
		*/
		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			/*
			* 两个字符串都结束了，说明模式匹配成功
			*/
			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			/*
			* str1还没有结束，但pattern的最后一个字符是*，所以匹配成功
			*
			*/
			return true;
		}
	}
	while (p2 < len2)
	{
		/*
		* pattern多出的字符只要有一个不是*,匹配失败
		*
		*/
		if (pattern[p2] != '*')
			return false;
		p2++;
	}
	return true;
}




void Filefind(char * path, char *filename)					//$ review:check chinese word
{
	HANDLE Find;
	WIN32_FIND_DATA finddata;
	char dir[200];
	char dirChoose[200];
	int n = 0;

	strcpy(dir, path);
	strcat(dir, "\\*.*");							//这里一定要指明通配符，不然不会读取所有文件和目录
	Find = FindFirstFile(charstrtowcharstr(dir), &finddata);
	do
	{
		if ((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0))				//判断是否具有某个属性，可以用按位and运算符（&）
		{
			if (strcmp(wchartochar(finddata.cFileName), ".") != 0 && strcmp(wchartochar(finddata.cFileName), "..") != 0)		//一旦找到'.'或".."，则不为空文件夹
			{
				strcpy(dir, path);
				strcat(dir, "\\");
				strcat(dir, wchartochar(finddata.cFileName));
				Filefind(dir, filename);
			}
		}
		else
		{

			if (MatchWithAsteriskW(wchartochar(finddata.cFileName), filename))
			{
				strcpy(m_path[n++].filename, wchartochar(finddata.cFileName));
				printf("%2d Lage ist:%s\\%s\n", n, path, wchartochar(finddata.cFileName));
			}
		}
	} while (FindNextFile(Find, &finddata));
	m_path;
	printf("choose the num(nur Num):");
	scanf("%d", &n);
	strcat(path, "\\");
	liemain(strcat(path, m_path[n - 1].filename));
	FindClose(Find);
}


