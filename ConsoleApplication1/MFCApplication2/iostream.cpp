#include"stdafx.h"
#pragma warning(disable:4996)��

char str[500];

struct m_PATH				//�ݹ��ѯʱ������������ĵ�ַ
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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
	if ((fp = fopen(path, "r")) == NULL)		//�п�
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

char * wchartochar(const wchar_t* wchar)					//WCHARת��ΪCHAR
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
	int mark = 0;//���ڷֶα��,'*'�ָ����ַ���
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
			/*�����ǰ��*�ţ���markǰ��һ�����Ѿ����ƥ�䣬
			*�ӵ�ǰ�㿪ʼ������һ�����ƥ��
			*/
			p2++;
			mark = p2;
			continue;
		}
		if (str1[p1] != pattern[p2])
		{
			if (p1 == 0 && p2 == 0)	//��������ַ������⴦������ͬ��ƥ��ʧ��
			{
				return false;
			}
			/*
			* p2���ص�mark����
			* p1��Ҫ���ص���һ��λ�á�
			* ��Ϊ*ǰ�Ѿ����ƥ�䣬����mark���֮ǰ�Ĳ���Ҫ�ٱȽ�
			*/
			p1 -= p2 - mark - 1;
			p2 = mark;
			continue;
		}
		/*
		* �˴�������ȵ����
		*/
		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			/*
			* �����ַ����������ˣ�˵��ģʽƥ��ɹ�
			*/
			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			/*
			* str1��û�н�������pattern�����һ���ַ���*������ƥ��ɹ�
			*
			*/
			return true;
		}
	}
	while (p2 < len2)
	{
		/*
		* pattern������ַ�ֻҪ��һ������*,ƥ��ʧ��
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
	strcat(dir, "\\*.*");							//����һ��Ҫָ��ͨ�������Ȼ�����ȡ�����ļ���Ŀ¼
	Find = FindFirstFile(charstrtowcharstr(dir), &finddata);
	do
	{
		if ((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY != 0))				//�ж��Ƿ����ĳ�����ԣ������ð�λand�������&��
		{
			if (strcmp(wchartochar(finddata.cFileName), ".") != 0 && strcmp(wchartochar(finddata.cFileName), "..") != 0)		//һ���ҵ�'.'��".."����Ϊ���ļ���
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


