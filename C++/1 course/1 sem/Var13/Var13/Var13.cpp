#include <iostream>
#include<cmath>
#include<string.h>
#include<cstring>

using namespace std;

int Lab3();
int Lab4();
int Lab5();
int Lab6();

int main()
{
	Lab6();
}

int Lab3()
{
	double a = -2, b = -0.1, x, y, h, s, an;
	int k = 140;

	h = (b - a) / 10;

	for (x = a; x < b + h / 2; x += h)
	{
		y = x * cos(x);
		cout << y << "  ";

		an = x;
		s = an;

		for (int n = 1; n < k; n++)
		{
			an *= (-1 * x * x / (2 * n * (2 * n - 1)));
			s += an;
		}
		cout << s << endl;
	}

	return 0;
}

int Lab4()
{
	int n;
	cin >> n;

	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	int max, max_i;
	max = a[0];
	max_i = 0;

	for (int i = 1; i < n; i++)
	{
		if (max < a[i])
		{
			max = a[i];
			max_i = i;
		}
	}

	for (int i = 0; i < n - max_i + 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			a[j - 1] = a[j];
		}
		i--;
		n--;
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i];
	}

	delete[] a;
	a = NULL;

	return 0;
}

int Lab5()
{
	int n, m;
	cin >> n;
	cin >> m;

	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
	}

	int count = 0;
	int sum;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> a[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		sum = 0;
		for (int j = 0; j < m; j++)
		{
			sum += a[i][j];


		}
		for (int k = 0; k < m; k++)
		{
			if (a[i][k] < sum - a[i][k])
			{
				count++;
			}
		}
	}

	cout << count;

	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	a = NULL;

	return 0;
}

int Lab6()
{
	char str[100] = "qw k hh lk";
	int n;
	int len = 0;

	n = strlen(str);

	for (int i = 0; i < n; i++)
	{
		if (str[i] != ' ')
		{
			len++;
			if (len % 2 == 0 && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			{
				i -= len - 1;
				while (str[i] != ' ' && str[i] != '\0')
				{
					for (int k = i + 1; k < n+1; k++)
					{
						str[k - 1] = str[k];
					}

					n--;
				}
				
				len = 0;
			}
		}
		else
			len = 0;
	}

	puts(str);
	return 0;
}