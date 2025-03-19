#include <iostream>
using namespace std;


char* convertToSystem(int num, int system);
char str[100];
int main()
{
    int num;
    int system;
    cout << "Enter number: ";
    cin >> num;
    cout << "Enter number system: ";
    cin >> system;

    if (num < 0)
    {
        cout << "Number must be positive" << endl;
        return 1;
    }
    if (system < 1 || system > 10)
    {
        cout << "Sysytem must be < 10" << endl;
        return 1;
    }

    cout << num << " in " << system << " system: " << convertToSystem(num, system) << endl;
}

char* convertToSystem(int num, int system)
{
    if (num == 0)
        return _strrev(str);

    if (system == 1)
    {
        strcat_s(str, "1");
        return convertToSystem(num - 1, system);
    }
    else
    {
        char remainder[2];
        _itoa_s(num % system, remainder, sizeof(remainder), 10);
        strcat_s(str, remainder);
        
        return convertToSystem(num / system , system);
    }
}



