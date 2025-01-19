#include <iostream>
#include<io.h>
#include "Bilets.h"
using namespace std;

int B6();
int B21();

int main()
{
	B21();
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
	cout << endl;
	int temp;
	for (int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; j++)
		{
			temp = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = temp;
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
	/*for (int i = 0; i < n-1; i++)
	{
		for (int j = i+1; j < n; j++)
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
		for (int j = 0; j < n-1; j++)
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


	delete[] b;*/
	return 0;
}
