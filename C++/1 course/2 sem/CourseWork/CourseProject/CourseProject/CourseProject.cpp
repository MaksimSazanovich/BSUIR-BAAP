#include <iostream>
#include<cmath>

using namespace std;

const double EPSILON = 10E-4;

double f(double x);
double phi(double x);
double f_derivative(double x);

double simple_interation_method(double a, double b);
double newton_method(double a, double b);
double parabola_method(double a, double b);

void print_roots(double root1, double root2, double root3);

int main()
{
	int a = 3;
	int b = 9;
	double root1 = 0, root2 = 0, root3 = 0;

	cout << "Simple iteration method:" << endl;
	root1 = simple_interation_method(a, b);
	root2 = simple_interation_method(root1 + EPSILON, b);
	root3 = simple_interation_method(root2 + EPSILON, b);
	print_roots(root1, root2, root3);


	cout << "Newton method:" << endl;
	root1 = newton_method(a, b);
	root2 = newton_method(root1 + EPSILON, b);
	root3 = newton_method(root2 + EPSILON, b);
	print_roots(root1, root2, root3);

	cout << "Parabola method:" << endl;
	root1 = parabola_method(a, b);
	root2 = parabola_method(root1 + EPSILON, b);
	root3 = parabola_method(root2 + EPSILON, b);
	print_roots(root1, root2, root3);
}

void print_roots(double root1, double root2, double root3)
{
	if (isnan(root1) || isnan(root2) || isnan(root3))
	{
		cout << "Unable to find all three roots.\n";
	}
	else
	{
		cout << "Root 1: " << root1 << endl;
		cout << "Root 2: " << root2 << endl;
		cout << "Root 3: " << root3 << endl;
		cout << endl;
	}
}

double phi(double x)
{
	return 5 * pow(sin(x), 2) + 5;
}

double f(double x)
{
	return x - 5 * pow(sin(x), 2) - 5;
}

double f_derivative(double x)
{
	return 1 - 5 * sin(2 * x);
}


double simple_interation_method(double a, double b)
{
	double x0 = (a + b) / 2.0;
	double x1 = 0;

	while (fabs(x0 - x1) > EPSILON)
	{
		x1 = x0;
		x0 = phi(x0);
	}

	return x1;
}

double newton_method(double a, double b)
{
	double x0 = (a + b) / 2.0;
	double x1 = x0 - (f(x0) / f_derivative(x0));
	while (fabs(x1 - x0) > EPSILON)
	{
		x0 = x1;
		x1 = x0 - (f(x0) / f_derivative(x0));
	}

	return x1;
}

double parabola_method(double a, double b)
{
	int m = 3;
	double h = (b - a) / m;
	double x0 = (a + b) / 2.0;

	double x1 = x0 - h;
	double x2 = x0;
	double x3 = x0 + h;

	int max_it = 100;

	double y1 = f(x1);
	double y2 = f(x2);
	double y3 = f(x3);

	for (int it = 0; it < max_it; it++)
	{
		double z1 = x1 - x3;
		double z2 = x2 - x3;
		double r = y3;

		double p = ((y1 - y3) * z2 - (y2 - y3) * z1) / (z1 * z2 * (z1 - z2));
		double q = ((y1 - y3) - p * z1 * z1) / z1;

		double discriminant = q * q - 4 * p * r;
		if (discriminant < 0)
		{
			cout << "Discriminant <0" << endl;
			return x2;
		}

		double zm1 = (-q - sqrt(discriminant)) / (2 * p);
		double zm2 = (-q + sqrt(discriminant)) / (2 * p);
		double zm = (fabs(zm1) < fabs(zm2)) ? zm1 : zm2;

		double x4 = x3 + zm;

		if (fabs(f(x4)) < EPSILON)
			return x4;

		if (x4 < x2)
		{
			x3 = x2;
			x2 = x4;
		}
		else
		{
			x1 = x2;
			x2 = x4;
		}

		y1 = f(x1);
		y2 = f(x2);
		y3 = f(x3);
	}
	return x2;
}
