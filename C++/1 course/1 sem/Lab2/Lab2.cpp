#include <iostream>
#include<cmath>

using namespace std;

int main()
{
   /* double x, y, f, s;
    int n;

    cout << "Enter the value of x: ";
    cin >> x;
    cout << "Enter the value of y: ";
    cin >> y;

    cout << "Choose the function: \n1 - sh(x)\n2 - x^2\n3 - e^x" << endl;
    cin >> n;

    switch (n)
    {
    case 1: f = sinh(x);
        
    case 2: f = pow(x, 2);
        
    case 3: f = exp(x);
        

    }

    if (x + fabs(y) == 0)
    {
        s = pow(sin(x), 2) - f;
    }
    else if (x + fabs(y) < 0)
    {
        s = pow(fabs(x*y), 1/3.0);
    }
    else
    {
        s = 3 * pow(f, 2);
    }
    cout << "Result: s = " << s << endl;
    if (5)cout << (1 > 5);*/

    double x, y, a, m;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << "a: ";
    cin >> a;

    //m = (((x > y) ? x : y) > ((y > z) ? y : z) ? ((x > y) ? x : y) : ((y > z) ? y : z)) / ((((x < y) ? x : y) < z) ? ((x < y) ? x : y) : z);

    m = a < 0 ? (((pow(x, 2) < pow(y, 2)) ? pow(x , 2)  : pow(y , 2)) + a ) : (a > 0) ? (abs(x - y) + y * (x + sqrt(pow(a , 3)))) : (y > x ? (y > a ? y : a) : (x > a ? x : a));

    cout << m;
    return 0;
}
