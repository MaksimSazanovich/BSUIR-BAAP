#include <iostream>

double multiply(int n)
{
	if (n <= 2) return 4/3.;
	else return (n / (n - 1)) * (n / (n + 1)) * (multiply(n - 2) / multiply(n - 3)) * (multiply(n - 2) / multiply(n - 1));
}

int main()
{
	int n;
	std::cin >> n;
	if (n <= 2)
		exit(2);
	else
		std::cout << multiply(n);
}

