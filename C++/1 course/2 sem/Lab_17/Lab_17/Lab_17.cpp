#include <iostream>
using namespace std;

struct ride
{
	char destination[100];
	char flight_number[100];
	char departure_time[100];
};

int hash_function(char* key, int m)
{
	int len = strlen(key);
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += (int)key[i];
	}
	return sum % m;
}

int hash_function_2(char* key, int m)
{
	int len = strlen(key);
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += (int)key[i];
	}
	return 1 + (sum % (m - 2));
}

void add(ride inf, int m, ride* hash_set)
{
	int i = hash_function(inf.flight_number, m);
	cout << "i " << i << endl;
	int c;
	while (hash_set[i].flight_number[0] != '\0')
	{
		c = hash_function_2(inf.flight_number, m);
		i = i - c;
		if (i < 0)
			i = i + m;

	}
	hash_set[i] = inf;
}

int search(char* inf, int m, ride hash_set[])
{
	int i = hash_function(inf, m);
	int c;
	while (hash_set[i].flight_number[0] != '\0')
	{
		if (!strcmp(hash_set[i].flight_number, inf))
			return i;
		c = hash_function_2(inf, m);
		i = i - c;
		if (i < 0)
			i = i + m;
	}
	return -1;
}

int main()
{
	int n = 8;
	int m = 10;
	ride* rides = new ride[n];

	const char* destinations[] = { "New York", "London", "Tokyo", "Paris", "Berlin", "Sydney", "Dubai", "Moscow" };
	const char* flight_numbers[] = { "SU250", "AF100", "BA001", "LH400", "AA123", "QR777", "EK500", "DL456" };
	const char* departure_times[] = { "08:00", "09:30", "12:15", "14:00", "16:45", "19:20", "22:10", "23:55" };

	for (int i = 0; i < n; i++)
	{
		strcpy_s(rides[i].destination, destinations[i]);
		strcpy_s(rides[i].flight_number, flight_numbers[i]);
		strcpy_s(rides[i].departure_time, departure_times[i]);
	}

	for (int i = 0; i < n; i++)
	{
		cout << "Ride " << i + 1 << ": "
			<< "Destination: " << rides[i].destination
			<< ", Flight Number: " << rides[i].flight_number
			<< ", Departure Time: " << rides[i].departure_time
			<< endl;
	}
	cout << endl;

	ride* hash_set = new ride[m];

	for (int i = 0; i < m; i++)
	{
		hash_set[i].flight_number[0] = '\0';
	}

	for (int i = 0; i < n; i++)
	{
		add(rides[i], m, hash_set);
	}

	for (int i = 0; i < m; i++)
	{
		cout << "Ride " << i + 1 << ": "
			<< "Destination: " << hash_set[i].destination
			<< ", Flight Number: " << hash_set[i].flight_number
			<< ", Departure Time: " << hash_set[i].departure_time
			<< endl;
	}

	char str[100];
	int str_ind;
	cout << "Key is flight number" << endl;

	char choice[100] = "y";
	while (!strcmp(choice, "y"))
	{
		puts("Enter flight number: ");
		gets_s(str);
		str_ind = search(str, m, hash_set);
		if (str_ind == -1)
			cout << "No element" << endl;
		else
		{
			puts(hash_set[str_ind].destination);
			puts(hash_set[str_ind].flight_number);
			puts(hash_set[str_ind].departure_time);
		}

		strcpy_s(choice, " ");

		while ((strcmp(choice, "y") && strcmp(choice, "n")) || !strcmp(choice, " "))
		{
			cout << "Continue? (y/n)" << endl;
			cin >> choice;
			cin.ignore();
			_strlwr_s(choice);

			if (strcmp(choice, "y") && strcmp(choice, "n"))
				cout << "Wrong input" << endl;
		}
	}

	delete[] rides;
	delete[] hash_set;
	return 0;
}

