#include<stdio.h>
#include<string.h>
#include<iostream>

using namespace std;

void Var3()
{
	char str[50] = "assssa jjjjddd 134541v23456 111";
	//gets_s(str);

	char* wrd;
	char* cn = NULL;
	char dlm[] = " ";
	int k = 1;

	wrd = strtok_s(str, dlm, &cn);
	while (wrd != NULL)
	{
		if (wrd[0] == wrd[strlen(wrd) - 1])
			puts(wrd);
		wrd = strtok_s(NULL, dlm, &cn);
	}
}

void Var1()
{
	char str[50] = "wwer qqqqqqqqqqqqqq hgh", str1[50];
	char* wrd, * cn = NULL, * max_wrd, * s;
	char dlm[] = " ";
	int k = 1, max_n = 0;

	strcpy_s(str1, str);
	wrd = strtok_s(str1, dlm, &cn);
	max_wrd = wrd;
	max_n = k;


	while (wrd != NULL)
	{
		if (strlen(max_wrd) < strlen(wrd))
		{
			max_wrd = wrd;
			max_n = k;
		}
		wrd = strtok_s(NULL, dlm, &cn);
		k++;
	}

	s = strstr(str, max_wrd);
	k = static_cast<int>(s - str);
	puts(max_wrd);
	cout << max_n << endl;
	cout << k;

}

int MyVar7_1()
{
	char str[100];
	char dlm[] = "0 ";
	char check_dlm[] = "01 ";
	char req_word[] = "11111";
	char* cn = NULL, * wrd;
	int k = 0, n;

	cout << "Enter string consisting of 0 and 1: ";
	gets_s(str, sizeof(str));

	n = strlen(str);


	wrd = strtok_s(str, check_dlm, &cn);
	while (wrd != NULL)
	{
		if (wrd != NULL)
		{
			cout << "Wrong input!";
			return 1;
		}
		wrd = strtok_s(str, check_dlm, &cn);
	}

	cn = NULL;

	wrd = strtok_s(str, dlm, &cn);

	while (wrd != NULL)
	{
		if (strcmp(wrd, req_word) == 0)
			k++;
		wrd = strtok_s(NULL, dlm, &cn);
	}
	cout << k;
	return 0;
}

int MyVar7_2()
{
	char str[50];

	cout << "Enter string consisting of 0 and 1: ";
	gets_s(str);
	int n = strlen(str);
	int k, count;

	k = count = 0;
	for (int i = 0; i < n; i++)
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' ')
		{
			cout << "Wrong input!";
			return 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (str[i] != '1')
			k = 0;
		else if (str[i] == '1')
		{
			k++;
			if (k == 5 && str[i + 1] != '1')
			{
				count++;
				k = 0;
			}
		}
	}

	cout << count;
}

//Поменять местами самое длинное слово на самое короткое без доп массивов, можно юзать буфер для одного слова. 1 вывод строки.
//Нельзя изменять длину строку
int Dop()
{
	char str[100];

	gets_s(str);

	char tmp[100];
	char dlm[] = " ";
	char* cn = NULL, * wrd;

	int min_len, max_len;
	int min_i, max_i;
	int str_len;
	int k;

	str_len = strlen(str);

	int fst_wrd_i;
	int fst_wrd_len = 0;
	
	k = 0;
	
	//Находим индекс конца первого слова
	for (int i = 0; i < str_len; i++)
	{
		if (str[i] != ' ' && str[i] != '\0')
			k++;
		else if (k != 0)
		{
			fst_wrd_i = i - 1;
			fst_wrd_len = k;
			k = 0;
			break;
		}
	}
	
	min_i = max_i = fst_wrd_i;
	min_len = max_len = fst_wrd_len;

	//Находим индексы концов min и max слов
	for (int i = 0; i < str_len + 1; i++)
	{
		if (str[i] != ' ' && str[i] != '\0')
		{
			k++;
		}
		else if (k != 0)							
		{
			if (min_len > k)
			{
				min_len = k;
				min_i = i - 1;
			}
			if (max_len < k)
			{
				max_len = k;
				max_i = i - 1;
			}
			k = 0;
		}
	}

	int temp;

	int fst_i, sec_i;
	int fst_len, sec_len;

	//Задаем значения первому и второму слову в перестановке
	if (min_i < max_i)
	{
		fst_i = min_i;
		fst_len = min_len;

		sec_i = max_i;
		sec_len = max_len;
	}
	else
	{
		fst_i = max_i;
		fst_len = max_len;

		sec_i = min_i;
		sec_len = min_len;
	}


	//Меняем слова местами
	for (int i = fst_i; i > fst_i - fst_len; i--)
	{
		for (int j = i; j < sec_i; j++)
		{
			temp = str[j + 1];
			str[j + 1] = str[j];
			str[j] = temp;

		}
		sec_i--;
	}
	sec_i = (min_i < max_i) ? max_i : min_i;


	for (int i = sec_i - sec_len - fst_len + 1; i < sec_i - fst_len + 1; i++)
	{
		for (int j = i; j > fst_i - fst_len + 1; j--)
		{
			temp = str[j - 1];
			str[j - 1] = str[j]; 
			str[j] = temp;

		}
		fst_i++;
	}

	puts(str);

	return 0;
}

int Lesha()
{
	char st[200] = "qwqw qw i qw";
	char st2[200];
	strcpy_s(st2, st);
	//puts("Input string: ");
	//gets_s(st);
	int n = strlen(st);
	char wrd[200] = "qw";
	/*puts("Input word: ");
	gets_s(wrd);*/
	int g = strlen(wrd);
	for (int i = 0; i < g; i++)
	{
		while (wrd[i] == ' ')
		{
			cout << "WRONG INPUT!" << endl;
			cout << "Input word: ";
			gets_s(wrd);
		}
	}
	//char* s = strstr(st, wrd);

	//while (s != NULL)
	//{
	//	int k = static_cast<int>(s - st);
	//	g = strlen(wrd);
	//	for (int i = k; i < k+g; i++)
	//	{
	//		if (g > 0)
	//		{
	//			for (int j = i + 1; j < n + 1; j++)
	//			{
	//				st[j - 1] = st[j];
	//			}
	//			n--;
	//			i--;
	//			g--;
	//		}
	//	}
	//	s = strstr(st, wrd);
	//}

	char* cn = NULL;
	char dlm[] = " ";

	char* a = strtok_s(st, dlm, &cn);

	int count = 0;
	while (a != NULL)
	{
		if (strcmp(a, wrd) == 0)
		{
			g = strlen(wrd);
			int k = static_cast<int>(a - st - count*g*sizeof(char));
			
			for (int i = k; i < k + g; i++)
			{
				if (g > 0)
				{
					for (int j = i + 1; j < n + 1; j++)
					{
						st2[j - 1] = st2[j];
					}
					n--;
					i--;
					g--;
				}
			}
			count++;
		}

		a = strtok_s(NULL, dlm, &cn);
	}

	puts(st2);
	return 0;
}

int main()
{
	Lesha();
}