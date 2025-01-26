#include <iostream>

using namespace std;

double multiply(int n);
int fact(int n);
int fizz_buzz_sum(int n);

int main()
{
	int n;
	cin >> n;
	cout << fizz_buzz_sum(n);
}

double multiply(int n)
{
	if (n < 4 && n > 0)
		return 4 / 3.0;
	else if (n <= 0)
		return 0;
	else
	{
		if (n % 2 != 0)
			n--;
		return ((n * n) / (double)(n * n - 1)) * multiply(n - 1);
	}
}

int fact(int n)
{
	if (n <= 0)
		return 1;
	else return n * fact(n - 1);
}

int fizz_buzz_sum(int n)
{
	n--;
	if (n < 3)
		return 0;
	if (n == 3)
		return 3;
	else if (n % 3 == 0 || n % 5 == 0)
		return n + fizz_buzz_sum(n);
	else return fizz_buzz_sum(n);
}
