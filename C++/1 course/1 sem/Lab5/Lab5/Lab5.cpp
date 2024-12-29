#include <iostream>
#include<cmath>
using namespace std;

int main()
{
	int n, m;
	cout << "Input number of lines: ";
	cin >> n;
	if (n == NULL || n <= 0)
	{
		cout << "Wrong input!";
		return 1;
	}
	cout << "Input number of columns: ";
	cin >> m;
	if (m == NULL || m <= 0)
	{
		cout << "Wrong input!";
		return 1;
	}

	char** s = new char* [n];
	for (int i = 0; i < n; i++)
	{
		s[i] = new char[m];
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			s[i][j] = '0';
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n - i; j++)
		{
			s[i][j] = '*';

		}

		for (int j = n - i - 1; j < i + 1; j++)
		{
			s[i][j] = '*';
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << s[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++)
	{
		delete[] s[i];
	}
	delete[] s;
	s = NULL;
}
