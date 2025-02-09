#include <iostream>
#include<cmath>

#include <iomanip>

using namespace std;

void show_table(double& a, double& b, double& eps);
double calculate_y(double& x);
double calculate_s(double& x, double& eps);
int get_another_eps(float eps);

int main()
{
	double a = -0.5;
	double b = 0.5;
	double eps = 0.001;
	show_table(a, b, eps);
}

void show_table(double& a, double& b, double& eps)
{
	double h = (b - a) / 10;
	for (double x = a; x < b + h / 2; x += h)
	{
		cout << "Pri x = " << x << " y = " << setprecision(7) << calculate_y(x) << " s = " << setprecision(get_another_eps(eps)) << calculate_s(x, eps) << endl;
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
	//return round(sum / eps) * eps;
	return sum;
}

int get_another_eps(float eps)
{
	int i;
	eps = 1 / eps;
	for (i = 0; eps >= 1; i++)
	{
		eps /= 10;
	}
	return i;
}
