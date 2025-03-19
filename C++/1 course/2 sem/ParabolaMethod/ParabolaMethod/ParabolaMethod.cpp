#include <iostream>
#include <cmath>

using namespace std;

const double EPSILON = 10E-4;
// Функция f(x) = x - 5*sin^2(x) - 5
double f(double x) {
    return x - 5 * pow(sin(x), 2) - 5;
}

// Функция для метода парабол
double parabolicMethod(double a, double b) 
{
    int m = 3;
    double h = (b - a) / m;
    double x0 = (a + b) / 2.0;

    int maxIter = 100;

    double x1 = x0 - h;
    double x2 = x0;
    double x3 = x0 + h;

    double y1 = f(x1), y2 = f(x2), y3 = f(x3);

    for (int i = 0; i < maxIter; i++) {
        // Вычисляем коэффициенты интерполяционного многочлена второго порядка
        double z1 = x1 - x3, z2 = x2 - x3;
        double r = y3;
        double p = ((y1 - y3) * z2 - (y2 - y3) * z1) / (z1 * z2 * (z1 - z2));
        double q = ((y1 - y3) - p * z1 * z1) / z1;

        // Вычисляем корни уравнения P(x) = 0
        double discriminant = q * q - 4 * p * r;
        if (discriminant < 0) {
            cout << "Дискриминант отрицательный, метод не применим.\n";
            return x2; // Возвращаем текущее приближение
        }

        double zm1 = (-q + sqrt(discriminant)) / (2 * p);
        double zm2 = (-q - sqrt(discriminant)) / (2 * p);

        // Выбираем корень с наименьшим модулем
        double zm = (fabs(zm1) < fabs(zm2)) ? zm1 : zm2;
        double x_new = x3 + zm;

        if (fabs(f(x_new)) < EPSILON) return x_new; // Проверка на достижение точности

        // Обновляем точки: выбираем три ближайшие к корню
        if (x_new < x2) {
            x3 = x2;
            x2 = x_new;
        }
        else {
            x1 = x2;
            x2 = x_new;
        }

        y1 = f(x1);
        y2 = f(x2);
        y3 = f(x3);
    }

    return x2; // Возвращаем последнее найденное значение
}

int main() {
    setlocale(LC_ALL, "Russian");
    double a = 3, b = 9; // Новый диапазон поиска корня
    double root1 = parabolicMethod(a, b);
    double root2 = parabolicMethod(root1 + EPSILON, b);
    double root3 = parabolicMethod(root2 + EPSILON, b);

    cout << "Приближенное значение корня: " << root1 << endl;
    cout << "Приближенное значение корня: " << root2 << endl;
    cout << "Приближенное значение корня: " << root3 << endl;
    return 0;
}
