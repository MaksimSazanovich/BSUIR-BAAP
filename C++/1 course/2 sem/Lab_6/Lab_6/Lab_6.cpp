#include <iostream>
#include<cmath>

using namespace std;

void show_table(double& a, double& b, double& eps);
double calculate_y(double& x);
double calculate_s(double& x, double& eps);

int main()
{
	double a = -0.5;
	double b = 0.5;
	double eps = 0.0001;
	show_table(a, b, eps);
}

void show_table(double& a, double& b, double& eps)
{
	double h = (b - a) / 10;
	for (double x = a; x < b + h / 2; x += h)
	{
		cout << "Pri x = " << x << " y = " << calculate_y(x) << " s = " << calculate_s(x, eps) << endl;
	}
}

double calculate_y(double& x)
{
	return cos(sin(x));
}

double calculate_s(double& x, double& eps)
{
	double an, c, sum;

	c = an = sum = 1;
	for (int n = 1; fabs(c) > eps; n++)
	{
		c = (sin(x) * sin(x)) / (2 * n * (2 * n - 1));
		an *= -1 * c;
		sum += an;
	}
	return sum;
}


