#include <iostream>

using namespace std;

int main()
{
	int n, cur = 0, prCur = 0, k = 0, count = 0, prCount = 0;
	cout << "Vvedite razmer: ";
	cin >> n;
	int* arr = new int[n];

	for (int i = 0; i < n; i++)
	{
		cout << "Vvedite element " << i << " : ";
		cin >> arr[i];
	}

	cur = arr[0];

	for (int i = 0; i < n; i++)
	{
		if (cur == arr[i])
		{
			count++;
			if (prCount < count)
			{
				prCount = count;
				prCur = cur;
			}
				
		}
		if (i == n - 1)
		{
			k++;
			i = k-1;
			cout << "k = " << k << endl;
			cur = arr[i];
			count = 0;
		}
	}
	cout << "Chislo " << prCur << " vstrechaetsa " << prCount << " raz" << endl;

	// 1 1 2 4
}

