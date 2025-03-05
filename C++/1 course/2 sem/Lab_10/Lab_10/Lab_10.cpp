#include <iostream>

using namespace std;

double multiply(int n);
double multiply_not_rec(int n);
int m(int a, int b);

int main()
{
	//int n;
	//cout << "Enter n: ";
	//cin >> n;
	//cout << "Rec: " << multiply(n) << endl;
	//cout << "Not a rec: " << multiply_not_rec(n) << endl;
	cout << m(3, 5);
}

double multiply(int n)
{
	if (n < 4 && n > 1)
		return 4 / 3.0;
	else if (n <= 1)
		return 0;
	else
	{
		if (n % 2 != 0)
			n--;
		return ((n * n) / (double)(n * n - 1)) * multiply(n - 1);
	}
}

double multiply_not_rec(int n)
{
	double res = 1;
	if (n <= 1)
		return 0;
	else
	{
		for (int i = n; i > 1; i--)
		{
			if (i % 2 != 0)
				continue;
			res *= (double)((i * i) / (double)(i * i - 1));
		}
	}

	return res;
}

int m(int a, int b)
{
	if (b == 1) return a;
	return a + m(a, b-1);
}

