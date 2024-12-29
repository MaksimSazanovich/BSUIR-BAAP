#include <iostream>
#include <stdio.h>
#include<io.h>
#include<string.h>
using namespace std;

enum options
{
	Create = 1,
	Enter = 2,
	OpenAndRead = 3,
	ShowResultOnScreen = 4,
	ShowResultInFile = 5,
	DeleteFile = 6,
	OpenMenu = 0
};

enum file_type
{
	Binary,
	Text
};

FILE* file = NULL, * result_file = NULL;
char file_name[100];
char prev_file_name[100];
char result_file_name[100];
char prev_result_file_name[100];

int menu;

struct book
{
	char title[40];
	char author_surname[40];
	int year;
	int count_pages;
};

int n;

bool is_sorted = false;

book* get_book_list();
int try_create_file_with_same_name(file_type type);
int create_file();
int enter_in_file();
int open_and_read_file();
book* get_sort_book_list();
int show_result_on_screen();
int show_result_in_file();
int open_menu();

book* get_book_list()
{
	errno_t err = fopen_s(&file, file_name, "rb");
	if (err)
	{
		cout << "Error with file reading" << endl;
		return NULL;
	}
	else
	{
		n = _filelength(_fileno(file)) / sizeof(book);

		book* book_list = new book[n];

		fread(book_list, sizeof(book), n, file);

		return book_list;
	}

}

int try_create_file_with_same_name(file_type type)
{
	char k[100] = " ";
	
	while ((k_int != 1 && k_int != 2) || !strcmp(k, " "))
	{
		cout << "You are sure that you want to create a file with the same name, the previous file will be deleted!\n(y/n)" << endl;
		cin >> k;

		if (strcmp(k, "y") && !strcmp(k, "n"))
			cout << "Wrong input" << endl;
	}

	switch (k_int)
	{
	case 1:
	{
		remove(prev_file_name);
		switch (type)
		{
		case Binary:
		{
			fopen_s(&file, prev_file_name, "wb+");
		}
		break;
		case Text:
		{
			fopen_s(&file, result_file_name, "w+");
		}

		break;
		}
		cout << "File " << file_name << ".dat " << "created successfully" << endl;
	}
	break;
	case 2:
	{
		return 0;
	}
	default:
	{
		cout << "Wrong input!" << endl;
		try_create_file_with_same_name(type);
	}
	break;
	}


}

int create_file()
{
	cout << "Enter file name: " << endl;
	gets_s(file_name);
	if (!strcmp(prev_file_name, file_name))
	{
		try_create_file_with_same_name(Binary);
	}
	else
	{
		errno_t err = fopen_s(&file, file_name, "wb+");
		if (err)
		{
			cout << "Error with file creating" << endl;
		}
		else
		{
			cout << "File " << file_name << ".dat " << "created successfully" << endl;
		}
		fclose(file);
		strcpy_s(prev_file_name, file_name);
	}
	return OpenMenu;
}

int enter_in_file()
{
	struct book
	{
		char title[40];
		char author_surname[40];
		int year;
		int count_pages;
	};

	book cur_book;



	if (file == NULL)
	{
		char k[100] = " ";
		int k_int = 0;
		while ((k_int != 1 && k_int != 2) || !strcmp(k, " "))
		{
			cout << "File doen't exist. Do you want to create a new file?\n1: Yes\n2: No" << endl;
			gets_s(k);
			gets_s(k);
			k_int = atoi(k);
			if ((k_int != 1 && k_int != 2) || !strcmp(k, " "))
				cout << "Wrong input" << endl;
		}
		switch (k_int)
		{
		case 1:
			create_file();
			break;
		case 2:
		{
			cout << "Error with file reading" << endl;
			open_menu();
		}
		break;
		}
	}
	else
	{
		fopen_s(&file, file_name, "ab");
		cout << "Input count of books: ";

		char k[100] = " ";

		while (n <= 0 || !strcmp(k, " "))
		{
			cout << "Input count of books: ";
			gets_s(k);
			n = atoi(k);
			if (n <= 0 || !strcmp(k, " "))
				cout << "Wrong input" << endl;
		}
		for (int i = 0; i < n; i++)
		{
			cout << endl;

			cout << "Input title " << i + 1 << " book: ";
			cin >> cur_book.title;

			cout << "Input author surname of " << i + 1 << " book: ";
			cin >> cur_book.author_surname;


			char k[100];
			char a[100];
			cur_book.year = 0;
			while (cur_book.year <= 0 || !strcmp(k, " "))
			{
				cout << "Input year of publication " << i + 1 << " book: ";
				puts("Input year of publication ");
				puts(i + 1);

				gets_s(k);
				

				cur_book.year = atoi(k);

				if (cur_book.year <= 0 || !strcmp(k, " "))
					cout << "Wrong input" << endl;
			}

			while (cur_book.count_pages <= 0 || !strcmp(k, " "))
			{
				cout << "Input count of pages " << i + 1 << " book: ";

				gets_s(k);
				gets_s(a);

				cur_book.count_pages = atoi(k);

				if (cur_book.count_pages <= 0 || !strcmp(k, " "))
					cout << "Wrong input" << endl;
			}


			fwrite(&cur_book, sizeof(book), 1, file);
		}

		fclose(file);
		return OpenMenu;
	}
}

int open_and_read_file()
{
	book* book_list = get_book_list();

	if (book_list == NULL)
		return 1;
	else
	{
		cout << endl << "Data from file: " << endl << endl;
		for (int i = 0; i < n; i++)
		{
			cout << "Title: " << book_list[i].title << endl;
			cout << "Author's surname: " << book_list[i].author_surname << endl;
			cout << "Publication year: " << book_list[i].year << endl;
			cout << "The amount of pages: " << book_list[i].count_pages << endl;
			cout << endl;
		}
		fclose(file);
		delete[] book_list;
		return OpenMenu;
	}
}

book* get_sort_book_list()
{
	book* book_list = get_book_list();
	if (book_list == NULL)
		return NULL;

	book temp;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (strcmp(book_list[i].title, book_list[j].title) == 1 && book_list[i].year < 1990 && book_list[j].year < 1990)
			{
				temp = book_list[i];
				book_list[i] = book_list[j];
				book_list[j] = temp;
			}
		}
	}

	return book_list;
}

int show_result_on_screen()
{
	book* book_list = get_sort_book_list();
	if (book_list == NULL)
		return 1;

	cout << endl;
	cout << "Result: " << endl;
	for (int i = 0; i < n; i++)
	{
		if (book_list[i].year < 1990)
		{
			cout << book_list[i].title << endl;
		}
	}
	cout << endl;
	fclose(file);
	delete[] book_list;
	return OpenMenu;
}

int show_result_in_file()
{
	cout << "Enter text file name: " << endl;
	gets_s(result_file_name);
	gets_s(result_file_name);
	//strcat_s(file_name, ".txt");

	if (!strcmp(prev_result_file_name, result_file_name))
	{
		try_create_file_with_same_name(Text);
	}
	else
	{
		errno_t err = fopen_s(&result_file, result_file_name, "w");
		if (err)
		{
			cout << "Error with file creating" << endl;
			open_menu();
		}
		else
		{
			cout << "File " << result_file_name << ".txt " << "created successfully";
			book* book_list = get_sort_book_list();
			if (book_list == NULL)
				return 1;

			cout << endl;

			for (int i = 0; i < n; i++)
			{
				if (book_list[i].year < 1990)
				{
					fprintf(result_file, "%s\n", book_list[i].title);
				}
			}

			delete[] book_list;

		}
		fclose(file);
		fclose(result_file);
		return OpenMenu;
	}
}
int open_menu()
{
	char k[100] = " ";
	int k_int = 0;
	while ((k_int < 1 && k_int > 6) || !strcmp(k, " "))
	{
		cout << "Menu: \n1: Create file\n2: Enter data in file\n3: Open file and read data\n4: Output result on screen\n5: Output result in files\n6: Delete file" << endl;
		cin >> k;
		k_int = atoi(k);
		if ((k_int < 1 && k_int > 6) || !strcmp(k, " "))
			cout << "Wrong input" << endl;
	}


	switch (k_int)
	{
	case Create:
	{
		if (create_file())
		{
			return 1;
		}
	}
	break;
	case Enter:
	{
		if (enter_in_file())
		{
			return 1;
		}
	}
	break;
	case OpenAndRead:
	{
		if (open_and_read_file())
		{
			return 1;
		}
	}
	break;
	case ShowResultOnScreen:
	{
		if (show_result_on_screen())
		{
			return 1;
		}
	}
	break;
	case ShowResultInFile:
	{
		if (show_result_in_file())
		{
			return 1;
		}
	}
	break;
	case DeleteFile:
	{
		remove(file_name);
		remove(result_file_name);
		file = NULL;
		result_file = NULL;
	}
	break;
	default:
	{
		cout << "There is no such option, please select another one" << endl;
	}
	break;
	}

	open_menu();
}


int main()
{
	open_menu();

	return 0;
}

