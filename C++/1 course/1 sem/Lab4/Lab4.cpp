#include<iostream>
#include "Lab4.h"
using namespace std;

int MyMainVar()
{
	int n, max_n = 0, min_n = 0;
	double max, min, b;
	cout << "Vvedite razmer ";
	cin >> n;

	if (n == NULL || n <= 0)
	{
		cout << "Wrong input!";
		return 1;
	}

	double* a = new double[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Vvedite a[" << i << "] = ";
		cin >> a[i];
	}

	max = min = a[0];

	for (int i = 1; i < n; i++)
	{
		if (min >= a[i])
		{
			min = a[i];
			min_n = i;
		}
	}

	if (min != a[n - 1])
	{
		for (int j = min_n; j < n - 1; j++)
		{
			b = a[j + 1];
			a[j + 1] = a[j];
			a[j] = b;
		}
	}

	for (int i = 1; i < n; i++)
	{
		if (max <= a[i])
		{
			max = a[i];
			max_n = i;
		}
	}

	if (max != a[0])
	{
		for (int j = max_n; j > 0; j--)
		{
			b = a[j - 1];
			a[j - 1] = a[j];
			a[j] = b;
		}
	}

	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << "" << endl;

	delete[] a;
	a = nullptr;

	return 0;
}

//int Var6()
//{
//	int n;
//	cout << "Enter size of 1-st (X) array: ";
//	cin >> n;
//	if (n == NULL || n <= 0)
//	{
//		cout << "Wrong input!";
//		return 1;
//	}
//	int* x = new int[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		cout << "Element [" << i << "]: ";
//		cin >> x[i];
//		if ((x[i] < x[i - 1] && i != 0) || x[i] == NULL)
//		{
//			cout << "Wrong input!";
//			return 2;
//		}
//	}
//
//	int m;
//	cout << "Enter size of 2-nd (Y) array: ";
//	cin >> m;
//	if (m == NULL || m <= 0)
//	{
//		cout << "Wrong input!";
//		return 1;
//	}
//	int* y = new int[m];
//
//	for (int i = 0; i < m; i++)
//	{
//		cout << "Element [" << i << "]: ";
//		cin >> y[i];
//		if ((y[i] < y[i - 1] && i != 0) || y[i] == NULL)
//		{
//			cout << "Wrong input!";
//			return 1;
//		}
//	}
//
//	int i = 0, j = 0, k = 0;
//	int* z = new int[n + m];
//
//	for (; k < n + m; k++)
//	{
//		if (i < n && j < m)
//		{
//			if (x[i] <= y[j])
//			{
//				z[k] = x[i];
//				i++;
//			}
//			else if (x[i] > y[j])
//			{
//				z[k] = y[j];
//				j++;
//			}
//		}
//		else if (i == n)
//		{
//			z[k] = y[j];
//			j++;
//		}
//		else
//		{
//			z[k] = x[i];
//			i++;
//		}
//	}
//
//	cout << "Array Z: ";
//	for (int i = 0; i < n + m; i++)
//	{
//		cout << z[i] << " ";
//	}
//
//	delete[] x;
//	delete[] y;
//	delete[] z;
//	x = nullptr;
//	y = nullptr;
//	z = nullptr;
//	return 0;
//}

int Var7()
{
	int n;
	cout << "Enter size of 1-st array: ";
	cin >> n;

	if (n == NULL || n <= 0)
	{
		cout << "Wrong input!";
		return 1;
	}

	int* a = new int[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Element [" << i << "]: ";
		cin >> a[i];
		if (a[i] == NULL)
		{
			cout << "Wrong input!";
			return 1;
		}
	}

	int m;
	cout << "Enter size of 2-nd array: ";
	cin >> m;
	if (m == NULL || m <= 0)
	{
		cout << "Wrong input!";
		return 1;
	}
	int* b = new int[m];

	for (int i = 0; i < m; i++)
	{
		cout << "Element [" << i << "]: ";
		cin >> b[i];
		if (b[i] == NULL)
		{
			cout << "Wrong input!";
			return 1;
		}
	}




	int min_a = a[0];
	int pr_min_a;
	pr_min_a = min_a;

	for (int i = 0; i < n; i++)
	{
		if (min_a >= a[i])
		{
			min_a = a[i];

			for (int j = 0; j < m; j++)
			{
				if (min_a == b[j])
				{
					min_a = pr_min_a;
				}
				
			}

			pr_min_a = min_a;
		}
	}

	if (min_a == 2147483647)
		cout << "Could not find smallest element of A that is not in ";
	else
		cout << min_a;


delete[] a;
delete[] b;

a = nullptr;
b = nullptr;

return 0;
}

//int Var8()
//{
//	int n;
//	cout << "Enter size of array: ";
//	cin >> n;
//	if (n == NULL || n <= 0)
//	{
//		cout << "Wrong input!";
//		return 1;
//	}
//
//	char* a = new char[n];
//
//	for (int i = 0; i < n; i++)
//	{
//		cout << "Element [" << i << "]: ";
//		cin >> a[i];
//		if (a[i] < 'A' || a[i] > 'z')
//		{
//			cout << "Wrong input!";
//			return 2;
//		}
//	}
//	char temp;
//	char copy = NULL;
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			if (a[j] > a[j + 1])
//			{
//				temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//			}
//		}
//	}
//
//	for (int i = 0; i < n - 1; i++)
//	{
//		if (a[i] == a[i + 1] && i + 1 != n)
//		{
//			copy = a[i];
//			for (int j = i + 1; (a[j] == a[j - 1] || a[j - 1] == copy) && j <= n;)
//			{
//				for (int k = j; k < n; k++)
//				{
//					a[k - 1] = a[k];
//				}
//				a[n - 1] = '0';
//				n--;
//				i--;
//			}
//
//		}
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			if (a[j] >= 'A' && a[j] <= 'Z' && a[j + 1] >= 'Z')
//			{
//				if ((a[j] + 32) > a[j + 1])
//				{
//					temp = a[j];
//					a[j] = a[j + 1];
//					a[j + 1] = temp;
//				}
//			}
//			else if (a[j - 1] >= 'A' && a[j - 1] <= 'Z' && a[j] >= 'Z')
//			{
//				if ((a[j - 1] + 32) > a[j])
//				{
//					temp = a[j];
//					a[j] = a[j - 1];
//					a[j - 1] = temp;
//					j -= 2;
//				}
//			}
//			else
//			{
//				if (a[j] > a[j + 1])
//				{
//					temp = a[j];
//					a[j] = a[j + 1];
//					a[j + 1] = temp;
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < n; i++)
//	{
//		cout << a[i] << " ";
//	}
//	cout << endl;
//
//	delete[] a;
//	a = NULL;
//	return 0;
//}

int main()
{
	Var7();
	return 0;
}


