#include <iostream>
#include<math.h>

using namespace std;

int main()
{
    double x, y, z, a, b, c, h;
    cout << "Vvedite x: ";
    cin >> x;
    cout << "Vvedite y: ";
    cin >> y;
    cout << "Vvedite z: ";
    cin >> z;
    a = 5 * atan(x);
    b = 1 / 4. * acos(x) * (x + 3 * fabs(x - y) + pow(x, 2));
    c = fabs(x - y) * z + pow(x, 2);
    h = a - b / c;
    cout << "Result h = " << h << endl;
    return 0;
}
