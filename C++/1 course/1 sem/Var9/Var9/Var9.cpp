#include <iostream>
#include<cmath>
#include<cstring>
#include<string.h>

using namespace std;

int Ex3();
int Ex4();
int Ex5();
int Ex6();
int Ex7();

int main()
{
	Ex7();
}

int Ex3()
{
	int k = 140;
	int b = 1;
	double a = 0.1, h, x, s, an;

	h = (b - a) / 10;

	for (x = a; x < b + h / 2; x += h)
	{
		cout << exp(2 * x) << "   ";

		an = 1;
		s = an;

		for (int n = 1; n <= k; n++)
		{
			an *= 2 * x / n;
			s += an;
		}

		cout << s << endl;
	}
	return 0;
}

int Ex4()
{
	int n;
	cin >> n;
	int* a = new int[n];

	int max, min, max_i, min_i;



	for (int i = 0; i < n; i++)
	{
		cout << "a[" << i << "] ";
		cin >> a[i];
	}

	max = min = a[0];
	max_i = min_i = 0;

	for (int i = 1; i < n; i++)
	{
		if (a[i] < min)
		{
			min = a[i];
			min_i = i;
		}
		if (a[i] > max)
		{
			max = a[i];
			max_i = i;
		}
	}

	for (int i = min_i; i < n; i++)
	{
		a[i] = a[i + 1];
	}
	n--;

	if (min_i < max_i)
		max_i--;

	for (int i = max_i; i < n; i++)
	{
		a[i] = a[i + 1];
	}
	n--;

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}

	delete[] a;

	return 0;
}

int Ex5()
{
	int n, m;
	cin >> n;
	cin >> m;
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << "a[" << i << "][" << j << "] ";
			cin >> a[i][j];
		}
	}

	int max, min;
	int max_i, min_i;

	max = min = a[0][0];
	max_i = min_i = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (a[i][j] < min)
			{
				min = a[i][j];
				min_i = i;
			}
			if (a[i][j] > max)
			{
				max = a[i][j];
				max_i = i;
			}
		}
	}

	int temp;
	for (int j = 0; j < m; j++)
	{
		temp = a[min_i][j];
		a[min_i][j] = a[max_i][j];
		a[max_i][j] = temp;
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		delete[] a[i];
	}
	delete[] a;
	a = NULL;
	return 0;
}

int Ex6()
{
	char str[100];
	gets_s(str);

	int n = strlen(str);

	for (int i = 0; i < n; i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i; j < n; j++)
			{
				str[j] = str[j + 1];
			}
			n--;
			i--;
		}
	}
	puts(str);
	return 0;
}

int Ex7()
{
	struct ride
	{
		char departure_time[100];
		char destination[100];
		int count_free_places;
	};

	int n;
	char str_n[100];
	//cin >> n;
	n = atoi(gets_s(str_n));
	ride* rides = new ride[n];

	char brest[100] = "Brest";

	char str_places[100];

	for (int i = 0; i < n; i++)
	{
		puts("Departure time: ");
		gets_s(rides[i].departure_time);
		puts("Destination: ");
		gets_s(rides[i].destination);
		puts("Count of free places: ");
		rides[i].count_free_places = atoi(gets_s(str_places));
	}

	ride temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (rides[i].count_free_places < rides[j].count_free_places &&
				strcmp(rides[i].destination, brest) == 0 &&
				strcmp(rides[j].destination, brest) == 0)
			{
				temp = rides[i];
				rides[i] = rides[j];
				rides[j] = temp;
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (strcmp(rides[i].destination, brest) == 0)
		{
			cout << rides[i].departure_time << endl;
			cout << rides[i].destination << endl;
			cout << rides[i].count_free_places << endl;
		}
		cout << endl;
	}

	delete[] rides;
	return 0;
}
