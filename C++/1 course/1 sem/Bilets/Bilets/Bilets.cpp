#include <iostream>
#include<io.h>
#include "Bilets.h"
using namespace std;

int B6();
int B21();
int B42();
int Danya();
int tby();
int old36();
int Roma();
int old33();
int B67();
int B28();
int B23Slava();
int B24();
int Lesha();
int B42();

int main()
{
	char str[] = "a      g";
	char dlm[] = " ";
	char* wrd, *cn;

	wrd = strtok_s(str, dlm, &cn);
	cout << (str[1] == '\0') << endl;
	cout << (str[2] == '\0') << endl;
	cout << (str[2] == ' ') << endl;
}

int B42()
{
	FILE* fl;
	char file_name[100];
	cout << "Vvidite file name: " << endl;
	gets_s(file_name);
	if (fopen_s(&fl, file_name, "wt+"))
	{
		return 1;
	}
	char str[100];
	cout << "Vvedite stroku " << endl;
	gets_s(str);
	fwrite(str, sizeof(char), strlen(str) + 1, fl);
	//fprintf(fl, "%s", str);
	fflush(fl);
	int n = _filelength(_fileno(fl)) / sizeof(char);
	int counter = 0;
	char ch;
	char next_ch;
	char wrd_ch = NULL;
	int ch_counter = 0;
	int need_counter;
	for (int i = 0; i < n - 1; i++)
	{
		fseek(fl, sizeof(char) * i, SEEK_SET);
		fread(&ch, sizeof(char), 1, fl);

		fseek(fl, sizeof(char) * (i + 1), SEEK_SET);
		fread(&next_ch, sizeof(char), 1, fl);
		if (ch != ' ' && (next_ch == ' ' || next_ch == '\0'))
		{
			counter++;
		}
		if ((ch == ' ' || i == 0) && (next_ch != ' ' && next_ch != '\0'))
		{
			if (ch == ' ')
				wrd_ch = next_ch;
			if (i == 0 && ch != ' ')
				wrd_ch = ch;
			need_counter = (i == 0 && ch != ' ') ? 3 : 4;
			ch_counter++;
		}
		else if (wrd_ch != NULL)
		{
			if (ch == wrd_ch)
			{
				fseek(fl, sizeof(char) * (i + 2), SEEK_SET);
				fread(&next_ch, sizeof(char), 1, fl);
				ch_counter++;
				if (ch_counter == need_counter && (next_ch == ' ' || next_ch == '\0'))
				{
					wrd_ch = NULL;
					ch_counter = 0;
					for (int j = i - 2; j <= i; j++)
					{
						fseek(fl, sizeof(char) * j, SEEK_SET);
						fread(&ch, sizeof(char), 1, fl);
						cout << ch;
					}
					cout << endl;
				}
			}
			else
			{
				wrd_ch = NULL;
				ch_counter = 0;
			}
		}
	}
	cout << "Kolvo slov " << counter << endl;
	fclose(fl);
	return 0;
}

int B6()
{
	FILE* fl;
	char file_name[100] = "aboba";
	if (fopen_s(&fl, file_name, "wb"))
	{
		return 1;
	}

	int n;
	cin >> n;
	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	fwrite(a, sizeof(int), n, fl);

	n = 0;
	delete[] a;

	fclose(fl);

	if (fopen_s(&fl, file_name, "rb"))
	{
		return 2;
	}

	n = _filelength(_fileno(fl)) / sizeof(int);
	a = new int[n];

	fread(a, sizeof(int), n, fl);
	fclose(fl);

	double sr = 0;

	for (int i = 0; i < n; i++)
	{
		sr += a[i] / (double)n;
	}
	cout << sr << endl;

	delete[] a;




	if (fopen_s(&fl, file_name, "rb+"))
	{
		return 3;
	}

	rewind(fl);
	int min, max, cur;
	int min_i, max_i;
	min_i = max_i = 0;

	rewind(fl);
	fread(&cur, sizeof(int), 1, fl);
	min = max = cur;
	
	fflush(fl);
	n = _filelength(_fileno(fl)) / sizeof(int);
	for (int i = 1; i < n; i++)
	{
		fseek(fl, sizeof(int) * i, SEEK_SET);
		fread(&cur, sizeof(int), 1, fl);
		if (min > cur)
		{
			min = cur;
			min_i = i;
		}
		if (max < cur)
		{
			max = cur;
			max_i = i;
		}
	}

	for (int i = 0; i < n; i++)
	{
		fseek(fl, sizeof(int) * i, SEEK_SET);
		fread(&cur, sizeof(int), 1, fl);
		cout << cur << " ";
	}
	cout << endl;


	fseek(fl, min_i * sizeof(int), SEEK_SET);
	fwrite(&max, sizeof(int), 1, fl);

	fseek(fl, max_i * sizeof(int), SEEK_SET);
	fwrite(&min, sizeof(int), 1, fl);


	
	for (int i = 0; i < n; i++)
	{
		fseek(fl, sizeof(int) * i, SEEK_SET);
		fread(&cur, sizeof(int), 1, fl);
		cout << cur << " ";
	}

	fclose(fl);
	return 0;
}

int B21()
{
	int a[10][10];
	int n;
	int sum = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i][j] > 0)
			{
				sum += a[i][j];
			}
		}
	}

	cout << "sum " << sum << endl;


	int* b = new int[n];
	bool is_upper = true;

	for (int i = 0; i < n; i++)
	{
		is_upper = true;
		for (int j = 0; j < n - 1; j++)
		{
			if (a[j][i] >= a[j + 1][i])
			{
				is_upper = false;
				break;
			}
		}
		b[i] = is_upper ? 0 : 1;
	}

	for (int i = 0; i < n; i++)
	{
		cout << b[i] << " ";
	}


	delete[] b;
	return 0;
}

int Danya()
{
	int n;
	cin >> n;

	double* a = new double[n];
	double sr = 0;

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	for (int i = 0; i < n; i++)
	{
		sr += a[i] / (double)n;
		if (a[i] < 0)
			a[i] *= 2;
	}

	cout << "sr " << sr << endl;
	sr = 0;

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
		if (i % 2 == 0 && i > 0)
			a[i] = (sum - a[i]) / i;
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	delete[] a;
	return 0;
}

int tby()
{
	char str[100];
	char* cn, * wrd;
	char dlm[] = " ";
	gets_s(str);
	wrd = strtok_s(str, dlm, &cn);
	while (wrd != NULL)
	{
		if (wrd[0] == 't')
			puts(wrd);
		if (strstr(wrd, "by") && wrd[strlen(wrd)] == '\0')
			puts(wrd);
		wrd = strtok_s(NULL, dlm, &cn);
	}
	return 0;
}

int old36()
{
	struct product
	{
		char name[100];
		int amount;
		float price;
		int date;
	};

	int n;
	cout << "Enter amount of products " << endl;
	cin >> n;
	product* products = new product[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the name of product " << i + 1 << ": ";
		cin >> products[i].name;
		cout << "Enter amount of " << products[i].name << ": ";
		cin >> products[i].amount;
		cout << "Enter price for one " << products[i].name << ": ";
		cin >> products[i].price;
		cout << "Enter the date of arriving (1--31): ";
		cin >> products[i].date;
		if (products[i].date < 1 || products[i].date > 31)
		{
			cout << "Date input error!";
			return 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (products[i].date >= 8 && products[i].date <= 18)
			cout << products[i].name << endl;
	}

	cout << "Ex2" << endl;
	int cur_date;
	cout << "Enter date: ";
	cin >> cur_date;
	product tmp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (products[i].price > products[j].price && products[i].date - cur_date > 8 && products[j].date - cur_date > 8)
			{
				tmp = products[i];
				products[i] = products[j];
				products[j] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (products[i].date - cur_date > 8)
			cout << products[i].name << endl;
	}

	delete[] products;
	return 0;
}

int Roma()
{
	double x, y, a, b, s, h, an = 1;
	int n = 853;

	a = 1;
	b = 3;
	h = (b - a) / 10;

	for (x = a; x < b + h / 2; x += h)
	{
		an = 1;
		s = 0;
		y = log(1 / (2 + 2 * x + x * x));
		for (int m = 1; m < n; m++)
		{
			an *= (-1) * (x + 1) * (x + 1);
			s += an / m;
		}
		cout << y << "   " << s << endl;
	}
	return 0;
}

int old33()
{
	int n;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		cout << "a[" << i << "]: ";
		cin >> a[i];
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i] < 0)
			sum += a[i];
		if (a[i] % 2 == 0)
			a[i] += 5;
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "sum " << sum << endl;

	int tmp;
	for (int i = 0; i < n; i++)
	{
		if (a[i] < 0)
		{
			for (int j = i - 1; j >= 0 && a[j] >= 0; j--)
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}

	delete[] a;
	return 0;
}

int B67()
{
	char str[100];
	char dlm[] = " ";
	char* wrd, * cn;
	gets_s(str);
	int len = strlen(str);
	wrd = strtok_s(str, dlm, &cn);
	while (wrd != NULL)
	{
		if (wrd[0] == 's')
			puts(wrd);
		wrd = strtok_s(NULL, dlm, &cn);
	}


	for (int i = 0; i < len; i++)
	{
		if (str[i] == '\0')
			str[i] = ' ';
	}

	char pascal[] = "Pascal";
	char c[] = "C++";
	int counter = 0;
	int c_len = strlen(c);
	int pascal_len = strlen(pascal);

	for (int i = 0; i < len; i++)
	{
		if (str[i] == pascal[counter++] && counter == pascal_len)
		{
			counter = 0;
			for (int j = i - pascal_len + 1; j < i - c_len + 1; j++)
			{
				str[j] = c[counter++];
			}

			for (int j = i - c_len + 1; j < i + 1; j++)
			{
				for (int k = i - c_len + 2; k <= len; k++)
				{
					str[k - 1] = str[k];
				}
				len--;
			}
		}

		else if (str[i + 1] != pascal[counter])
		{
			counter = 0;
		}
	}
	puts(str);
	return 0;
}

int B28()
{
	FILE* fl, * fl2;
	char file_name[100] = "file";
	char file_name2[100] = "file2";
	char str[100];
	char str2[100] = "\0";
	char str3[100] = "\0";

	gets_s(str);

	if (fopen_s(&fl, file_name, "w+t"))
	{

		cout << "Error creating 1";
		return 1;
	}


	fprintf(fl, "%s", str);
	rewind(fl);
	fread(str2, sizeof(char) * 100, 1, fl);
	puts(str2);


	if (fopen_s(&fl2, file_name2, "w+t"))
	{
		cout << "Error creating 2";
		return 2;
	}
	fread(str2, sizeof(char) * 100, 1, fl);

	fprintf(fl2, "%s", str2);

	rewind(fl2);
	//Удалить слова из 5 букв 
	int n = _filelength(_fileno(fl2)) / sizeof(char);
	char ch;
	char next_ch;
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		rewind(fl2);
		fseek(fl2, sizeof(char) * i, SEEK_SET);
		fread(&ch, sizeof(char), 1, fl2);
		rewind(fl2);
		fseek(fl2, sizeof(char) * (i + 1), SEEK_SET);
		fread(&next_ch, sizeof(char), 1, fl2);
		/*cout << ch;
		cout << next_ch;*/
		if (ch != ' ')
		{
			counter++;
			if (counter == 5 && (next_ch == ' ' || i == n - 1))
			{
				for (int j = 0; j < counter; j++)
				{

					for (int k = i + 1 - counter; k < n; k++)
					{
						rewind(fl2);
						fseek(fl2, sizeof(char) * k + 1, SEEK_SET);
						fread(&next_ch, sizeof(char), 1, fl2);

						rewind(fl2);
						fseek(fl2, sizeof(char) * (k), SEEK_SET);
						fprintf(fl2, "%c", next_ch);
					}
					n--;
				}
				i -= counter;
				_chsize(_fileno(fl2), sizeof(char) * n);

				counter = 0;

			}


		}
		else
		{
			counter = 0;
		}
	}

	rewind(fl2);
	fread(str3, sizeof(char) * n, 1, fl2);
	puts(str3);

	fclose(fl);
	fclose(fl2);
	return 0;
}

int B23Slava()
{
	FILE* fl;
	char file_name[100];
	char str[100];

	cout << "Vvedite imya fayla" << endl;
	gets_s(file_name);
	if (fopen_s(&fl, file_name, "wb+"))
	{
		cout << "Error create" << endl;
		return 1;
	}

	cout << "Vvedite strochenku " << endl;
	gets_s(str);
	int n = strlen(str) + 1;
	fwrite(str, sizeof(char), n, fl);

	char ch;
	char w = 'w';
	int counter = 0;

	for (int i = 0; i < n; i++)
	{
		fseek(fl, sizeof(char) * i, SEEK_SET);
		fread(&ch, sizeof(char), 1, fl);
		if (ch == 'z' || ch == 'Z')
		{
			counter++;
			n++;
			_chsize(_fileno(fl), sizeof(char) * n);
			for (int k = n - 2; k > i; k--)
			{
				fseek(fl, sizeof(char) * k, SEEK_SET);
				fread(&ch, sizeof(char), 1, fl);
				fseek(fl, sizeof(char) * (k + 1), SEEK_SET);
				fwrite(&ch, sizeof(char), 1, fl);
			}
			rewind(fl);
			fseek(fl, sizeof(char) * (i + 1), SEEK_SET);
			//fwrite(&w, sizeof(char), 1, fl);
			fputc('w', fl);
		}
	}

	cout << "count " << counter << endl;
	rewind(fl);
	char str2[200];
	fread(str2, sizeof(char), n, fl);
	puts(str2);
	fclose(fl);
	return 0;
}

int B24()
{
	int n;
	cin >> n;
	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	int k = n / 2 - 1;

	for (int i = k; i > 0; i--)
	{
		for (int j = i - 1; j < n; j++)
		{
			a[j - 1] = a[j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}

	delete[] a;
	return 0;
}

int Lesha()
{
	char str[100];
	char svo[] = "svo";
	char zov[] = "zov";
	gets_s(str);
	int n = strlen(str);

	char space[] = "   ";
	for (int i = 0; i < n; i++)
	{
		if (strncmp(&str[i], svo, 3) == 0)
		{

			strcat_s(str, space);
			n += 3;
			for (int j = n - 1; j > i + 3; j--)
			{
				str[j] = str[j - 3];
			}

			for (int k = 0; k < 3; k++)
			{
				str[i + 3 + k] = zov[k];
			}

		}
	}
	puts(str);
	return 0;
}