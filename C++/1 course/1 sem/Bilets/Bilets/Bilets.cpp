#include <iostream>
#include<io.h>
#include "Bilets.h"
using namespace std;

int B6();
int B21();
int Danya();
int tby();
int old36();
int Roma();
int main()
{
	Roma();

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
	long min_p, max_p;
	min_p = max_p = ftell(fl);

	fread(&cur, sizeof(int), 1, fl);
	min = max = cur;


	n = _filelength(_fileno(fl)) / sizeof(int);
	for (int i = 1; i < n; i++)
	{
		fread(&cur, sizeof(int), 1, fl);
		if (min > cur)
		{
			min = cur;
			min_p = ftell(fl);
		}
		if (max < cur)
		{
			max = cur;
			max_p = ftell(fl);
		}
	}

	rewind(fl);
	for (int i = 0; i < n; i++)
	{
		fread(&cur, sizeof(int), 1, fl);
		cout << cur << " ";
	}
	cout << endl;


	fseek(fl, min_p - sizeof(int), SEEK_SET);
	fwrite(&max, sizeof(int), 1, fl);

	fseek(fl, max_p - sizeof(int), SEEK_SET);
	fwrite(&min, sizeof(int), 1, fl);



	for (int i = 0; i < n; i++)
	{
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
	cout << "Enter amount of products";
	cin >> n;
	product* products = new product[n];
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the name of product " << i + 1 << " :";

	}

	return 0;
}

int Roma()
{
	double x, y, a, b, s, h, an=1;
	int n = 853;

	a = 1;
	b = 3;
	h = (b - a) / 10;

	for (x = a; x<b+h/2; x += h)
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