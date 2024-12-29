#include <iostream>
#include<cmath>
using namespace std;

int main()
{
	double a = -0.1, b = 1.3, x, k, h, s, y, an, e = 1000;
	h = (b - a) / 10;

	cout << "Vvedite kolishestvo chlenov ryada Teylora: ";
	cin >> k;
	if (k <= 0)
	{
		cout << "Wrong input";
		return 1;
	}

	for (x = a; x < b + h / 2; x += h)
	{
		y = pow(2, x);
		an = 1;
		s = an;

		for (int n = 1; n <= k; n++)
		{
			an *= x * log(2) / n;
			s += an;
		}
		cout << "Pri x = " << x << " y(x) = " << y << "  s(x) = " << round(s * e) / e << endl;
	}

	return 0;
}

