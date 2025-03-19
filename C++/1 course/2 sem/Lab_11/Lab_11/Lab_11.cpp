#include <iostream>
#include <stdio.h>
#include<io.h>
#include<string.h>
#include<cctype>

using namespace std;

enum options
{
	Create = 1,
	Enter = 2,
	OpenAndRead = 3,
	ShowResultOnScreen = 4,
	ShowResultInFile = 5,
	DeleteFile = 6,
	FinishProgram = 7,
	OpenMenu = 0
};

enum file_type
{
	Binary,
	Text
};

enum sort_type
{
	BubbleSort = 1,
	QuickSort = 2,
	SelectionSort = 3,
	InsertionSort = 4,
	CocktailSort = 5,
	ShellSort = 6
};

FILE* file = NULL, * result_file = NULL;
char file_name[100];
char result_file_name[100] = " ";
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
book* (*get_book_sort(sort_type sort_type))();

book* get_sort_book_list_in_alphabet();
book* get_sort_book_list_quick_sort();
book* get_sort_book_list_selection_sort();
book* get_sort_book_list_insertion_sort();


void quick_sort(book* array, int min_index, int max_index);
int get_pivot_index(book* array, int min_index, int max_index);
void swap(book& a, book& b);

char* get_input_name(file_type type, options option);
int get_chars_in_str(char* chars, char* str);

int try_create_file_with_same_name(file_type type);
void handle_missing_file();

int create_file();
int enter_in_file();
int open_and_read_file();
void choose_sort_type(options result);
int show_result_on_screen(sort_type);
int show_result_in_file(sort_type);
void delete_files();
int open_menu();

book* get_book_list()
{
	errno_t err = fopen_s(&file, file_name, "rb");
	if (err)
	{
		cout << "Error with file reading, because binary file wasn't created" << endl;
		return NULL;
	}
	else
	{
		n = _filelength(_fileno(file)) / sizeof(book);

		if (n == 0)
		{
			return NULL;
		}
		book* book_list = new book[n];

		fread(book_list, sizeof(book), n, file);

		return book_list;
	}

}

int try_create_file_with_same_name(file_type type)
{
	char k[100] = " ";

	while (!strcmp(k, " ") || (strcmp(k, "y") && strcmp(k, "n")))
	{
		cout << "You are sure that you want to create a file with the same name, the previous file will be deleted!\n(y/n)" << endl;
		cin >> k;
		_strlwr_s(k);
		if (strcmp(k, "y") && strcmp(k, "n"))
			cout << "Wrong input" << endl;
	}

	if (!strcmp(k, "y"))
	{
		switch (type)
		{
		case Binary:
		{
			fopen_s(&file, file_name, "wb+");
		}
		break;
		case Text:
		{
			fopen_s(&result_file, result_file_name, "w+");
		}

		break;
		}
		cout << "File " << file_name << ".dat " << "created successfully" << endl;

	}
	else if (!strcmp(k, "n"))
	{
		return 0;
	}
}

void handle_missing_file()
{
	char k[100] = " ";

	while ((strcmp(k, "y") && strcmp(k, "n")) || !strcmp(k, " "))
	{
		cout << "File doen't exist. Do you want to create a new file?\n(y/n)" << endl;
		cin >> k;
		_strlwr_s(k);

		if (strcmp(k, "y") && strcmp(k, "n"))
			cout << "Wrong input" << endl;
	}

	if (!strcmp(k, "y"))
	{
		fclose(file);
		remove(file_name);
		strcpy_s(file_name, " ");
		create_file();
	}
	else if (!strcmp(k, "n"))
	{
		cout << "Error with binary file reading. You must create a new binary file" << endl;
		open_menu();
	}
}

int create_file()
{
	strcpy_s(file_name, get_input_name(Binary, Create));

	if (fopen_s(&file, file_name, "wbx+") != NULL)
	{
		try_create_file_with_same_name(Binary);
	}
	else
	{
		cout << "File " << file_name << ".dat " << "created successfully" << endl;
	}
	fclose(file);

	return OpenMenu;
}

int enter_in_file()
{
	book cur_book;

	strcpy_s(file_name, get_input_name(Binary, Enter));

	if (fopen_s(&file, file_name, "wbx") != NULL)
	{
		fopen_s(&file, file_name, "ab");

		char k[100] = " ";
		char cont[100] = "y";

		while (!strcmp(cont, "y"))
		{
			cout << endl;

			strcpy_s(cur_book.title, " ");

			while (isupper(cur_book.title[0]) == false || !strcmp(k, " "))
			{
				cout << "Input title of book: ";

				cin >> k;
				strcpy_s(cur_book.title, k);

				if (isupper(cur_book.title[0]) == false || !strcmp(k, " "))
				{
					cout << "The title of the book must begin with an upper letter" << endl;
				}

			}

			strcpy_s(cur_book.author_surname, " ");
			char dlm[] = "-'";
			bool isRight = false;

			while (((isupper(cur_book.author_surname[0]) == false || !strcmp(k, " "))) || isRight == false)
			{
				cout << "Input author's surname of book: ";

				cin >> k;
				strcpy_s(cur_book.author_surname, k);
				//cout << get_chars_in_str(dlm, cur_book.author_surname);
				if ((isupper(cur_book.author_surname[0]) == false || !strcmp(k, " ")))
				{
					cout << "The author's surname of the book must begin with an upper letter" << endl;
					isRight = true;
				}
				if (get_chars_in_str(dlm, cur_book.author_surname))
				{
					int k_int;
					if (strchr(cur_book.author_surname, '-'))
					{
						k_int = (int)(strchr(cur_book.author_surname, '-') - cur_book.author_surname);
						if (isupper(cur_book.author_surname[k_int + 1]) == false)
						{
							cout << "The author's double surname of the book must iclude upper letter after - " << endl;
							isRight = false;
						}
						else
							isRight = true;
					}
					else if (strchr(cur_book.author_surname, '\''))
					{
						k_int = (int)(strchr(cur_book.author_surname, '\'') - cur_book.author_surname);
						if (isupper(cur_book.author_surname[k_int + 1]) == false)
						{
							cout << "The author's double surname of the book must iclude upper letter after ' " << endl;
							isRight = false;
						}
						else
							isRight = true;
					}
				}
				else
					isRight = true;
			}

			cur_book.year = 0;
			while (cur_book.year <= 0 || !strcmp(k, " "))
			{
				cout << "Input year of publication of book: ";

				cin >> k;

				cur_book.year = atoi(k);

				if (cur_book.year <= 0 || !strcmp(k, " "))
					cout << "Wrong input" << endl;
			}

			char pages[100] = " ";
			while (cur_book.count_pages <= 0 || !strcmp(pages, " "))
			{
				cout << "Input count of pages of book: ";

				cin >> pages;

				cur_book.count_pages = atoi(pages);

				if (cur_book.count_pages <= 0 || !strcmp(pages, " "))
					cout << "Wrong input" << endl;
			}

			fwrite(&cur_book, sizeof(book), 1, file);

			strcpy_s(cont, " ");

			while ((strcmp(cont, "y") && strcmp(cont, "n")) || !strcmp(cont, " "))
			{
				cout << "Continue? (y/n)" << endl;
				cin >> cont;
				_strlwr_s(cont);

				if (strcmp(cont, "y") && strcmp(cont, "n"))
					cout << "Wrong input" << endl;
			}


		}
		fclose(file);
	}
	else
	{
		handle_missing_file();
	}

	return OpenMenu;
}

int open_and_read_file()
{
	strcpy_s(file_name, get_input_name(Binary, Enter));

	if (fopen_s(&file, file_name, "wbx") != NULL)
	{
		book* book_list = get_book_list();

		if (book_list == NULL)
		{
			cout << file_name << ".dat is empty" << endl;
			fclose(file);
			return OpenMenu;
		}
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
	else
	{
		handle_missing_file();
	}

}

book* get_sort_book_list_in_alphabet()
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

book* get_sort_book_list_quick_sort()
{
	book* book_list = get_book_list();
	if (book_list == NULL)
		return NULL;

	quick_sort(book_list, 0, n - 1);

	return book_list;
}

void quick_sort(book* array, int min_index, int max_index)
{
	if (min_index < max_index)
	{
		int pivot_index = get_pivot_index(array, min_index, max_index);

		quick_sort(array, min_index, pivot_index - 1);
		quick_sort(array, pivot_index + 1, max_index);
	}
}

int get_pivot_index(book* array, int min_index, int max_index)
{
	int pivot = min_index - 1;
	for (int i = min_index; i < max_index; i++)
	{
		if (array[i].count_pages < array[max_index].count_pages)
		{
			pivot++;
			swap(array[pivot], array[i]);
		}
	}
	pivot++;
	swap(array[pivot], array[max_index]);
	return pivot;
}

void swap(book& a, book& b)
{
	book temp = a;
	a = b;
	b = temp;
}


struct St 
{
	int l;
	int r;
} stack[20];
void push(int l, int r, int& s)
{
	stack[s].l = l;
	stack[s].r = r;
	s++;
}
void pop(int& l, int& r, int& s) 
{
	s--;
	l = stack[s].l;
	r = stack[s].r;
}
book* get_sort_book_list_non_rec_quick_sort() 
{
	book* book_list = get_book_list();
	if (book_list == NULL)
		return NULL;

	int i, j, left, right, s = 0;
	book x;
	push(0, n - 1, s);
	while (s != -1) 
	{
		pop(left, right, s);
		while (left < right) 
		{
			i = left;
			j = right; 
			x = book_list[(left + right) / 2];
			while (i <= j) 
			{
				while (book_list[i].count_pages < x.count_pages)
					i++;
				while (book_list[j].count_pages > x.count_pages)
					j--;
				if (i <= j) 
				{ 
					swap(book_list[i], book_list[j]);
					i++; 
					j--; 
				}
			}
			if ((j - left) < (right - i)) 
			{ 
				if (i < right) 
					push(i, right, s);
				right = j;
			}
			else 
			{
				if (left < j) 
					push(left, j, s);
				left = i;
			}
		}
	}

	return book_list;
}

book* get_sort_book_list_selection_sort()
{
	book* book_list = get_book_list();
	if (book_list == NULL)
		return NULL;

	int min;

	for (int i = 0; i < n; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (book_list[j].count_pages < book_list[min].count_pages)
			{
				min = j;
			}
		}
		swap(book_list[i], book_list[min]);
	}
	return book_list;
}

book* get_sort_book_list_insertion_sort()
{
	book* book_list = get_book_list();
	if (book_list == NULL)
		return NULL;

	int index;
	book cur_book;

	for (int i = 0; i < n; i++)
	{
		index = i;
		cur_book = book_list[i];

		while (index > 0 && cur_book.count_pages < book_list[index - 1].count_pages)
		{
			book_list[index] = book_list[index - 1];
			index--;
		}
		book_list[index] = cur_book;
	}

	return book_list;
}

void choose_sort_type(options result)
{
	char k[100] = " ";
	int cur_sort_type = 0;
	while ((cur_sort_type < (int)BubbleSort || cur_sort_type >(int)InsertionSort) || !strcmp(k, " "))
	{
		cout << "Choose sort type: " << endl;
		cout << "1) Bubble sort (in alphabetical order)\n"
			 << "2) QuickSort (in non - decreasing order of number of pages)\n"
			 << "3) Selection sort (in non - decreasing order of number of pages)\n"
			 /* << "4) Insertion sort (in non - decreasing order of number of pages)" */<< endl;
		cin >> k;
		cur_sort_type = atoi(k);
		if ((cur_sort_type < (int)BubbleSort || cur_sort_type >(int)InsertionSort) || !strcmp(k, " "))
			cout << "Wrong input" << endl;
	}
	switch (result)
	{
	case ShowResultOnScreen:
		show_result_on_screen(static_cast<sort_type>(cur_sort_type));
		break;
	case ShowResultInFile:
		show_result_in_file(static_cast<sort_type>(cur_sort_type));
		break;
	}
}

book* (*get_book_sort(sort_type sort_type))()
{
	switch (sort_type)
	{
	case BubbleSort:
		return &get_sort_book_list_in_alphabet;
	case QuickSort:
		return &get_sort_book_list_non_rec_quick_sort;
	case SelectionSort:
		return &get_sort_book_list_selection_sort;
	case InsertionSort:
		return &get_sort_book_list_insertion_sort;
	}
}

int show_result_on_screen(sort_type sort_type)
{
	book* (*get_sort_book_function)();
	strcpy_s(file_name, get_input_name(Binary, Enter));

	if (fopen_s(&file, file_name, "wbx") != NULL)
	{
		//book* book_list = get_sort_book_list_in_alphabet();
		get_sort_book_function = get_book_sort(sort_type);
		book* book_list = get_sort_book_function();
		if (book_list == NULL)
		{
			cout << file_name << ".dat is empty" << endl;
			fclose(file);
			return OpenMenu;
		}

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
	else
	{
		handle_missing_file();
	}
}

int show_result_in_file(sort_type sort_type)
{
	book* (*get_sort_book_function)();
	strcpy_s(file_name, get_input_name(Binary, Enter));

	if (fopen_s(&file, file_name, "wbx") != NULL)
	{
		//book* book_list = get_sort_book_list_in_alphabet();
		get_sort_book_function = get_book_sort(sort_type);
		book* book_list = get_sort_book_function();
		if (book_list == NULL)
		{
			cout << file_name << " is empty" << endl;
			fclose(file);
			return OpenMenu;
		}

		strcpy_s(result_file_name, get_input_name(Text, ShowResultInFile));
		//strcat_s(result_file_name, ".txt");

		if (fopen_s(&result_file, result_file_name, "wtx") != NULL)
		{
			fopen_s(&file, result_file_name, "at");
			for (int i = 0; i < n; i++)
			{
				if (book_list[i].year < 1990)
				{
					fprintf(result_file, "%s\n", book_list[i].title);
				}
			}

			delete[] book_list;

			cout << "Data from " << file_name << ".dat has been output in " << result_file_name << ".txt successfully" << endl;

			fclose(file);
			fclose(result_file);
			return OpenMenu;
		}
		else
		{

			cout << result_file_name << " doesn't exist, you must create text file" << endl;

			fclose(result_file);
			remove(result_file_name);
			strcpy_s(result_file_name, get_input_name(Text, Create));
			//strcat_s(result_file_name, ".txt");
			if (!strcmp(file_name, result_file_name))
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
					cout << "File " << result_file_name << " created successfully" << endl;

					get_sort_book_function = get_book_sort(sort_type);
					book* book_list = get_sort_book_function();
					if (book_list == NULL)
					{
						fclose(file);
						fclose(result_file);
						return 1;
					}
						

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

	}
	else
	{
		handle_missing_file();
	}
}

void delete_files()
{
	char k[100] = " ";

	while (!strcmp(k, " ") || (strcmp(k, "b") && strcmp(k, "t")))
	{
		cout << "Select the type of file you want to delete: \n(b/t)" << endl;
		cin >> k;
		_strlwr_s(k);
		if (strcmp(k, "b") && strcmp(k, "t"))
			cout << "Wrong input" << endl;
	}

	if (!strcmp(k, "b"))
	{
		strcpy_s(file_name, get_input_name(Binary, DeleteFile));
		remove(file_name);
		file = NULL;
		cout << file_name << ".dat was deleted succsessfully" << endl;
		strcpy_s(file_name, " ");
	}
	else if (!strcmp(k, "t"))
	{
		strcpy_s(result_file_name, get_input_name(Text, DeleteFile));
		remove(result_file_name);
		result_file = NULL;
		cout << result_file << " was deleted succsessfully" << endl;
		strcpy_s(result_file_name, " ");
	}
}

int open_menu()
{
	char k[100] = " ";
	int menu = 0;
	while ((menu < (int)Create || menu >(int)FinishProgram) || !strcmp(k, " "))
	{
		cout << "Choose option: " << endl;
		cout << "1: Create file\n2: Enter data in file\n3: Open file and read data\n4: Output result on screen\n5: Output result in file\n6: Delete file\n7: Finish program" << endl;
		cin >> k;
		menu = atoi(k);
		if ((menu < (int)Create || menu >(int)FinishProgram) || !strcmp(k, " "))
			cout << "Wrong input" << endl;
	}

	switch (menu)
	{
	case Create: create_file(); break;
	case Enter: enter_in_file(); break;
	case OpenAndRead: open_and_read_file(); break;
	case ShowResultOnScreen: choose_sort_type(ShowResultOnScreen); break;
	case ShowResultInFile: choose_sort_type(ShowResultInFile); break;
	case DeleteFile: delete_files(); break;
	case FinishProgram: return 0; break;
	default: cout << "There is no such option, please select another one" << endl; break;
	}
	open_menu();
}

int get_chars_in_str(char* chars, char* str)
{
	int k = strlen(chars);
	int n = strlen(str);
	int count = 0;
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (str[j] == chars[i])
				count++;
		}
	}
	return count;
}

char* get_input_name(file_type type, options option)
{
	char name[100];
	if (type == Binary && option == Create)
		cout << "Enter binary file name for creating: " << endl;
	else if (type == Binary && option == Enter)
		cout << "Enter binary file name for reading: " << endl;
	else if (type == Text && option == Create)
		cout << "Enter text file name for creating: " << endl;
	else if (type == Text && option == ShowResultInFile)
		cout << "Enter text file name for writing: " << endl;
	else if (type == Binary && option == DeleteFile)
		cout << "Enter binary file name for deleting: " << endl;
	else if (type == Text && option == DeleteFile)
		cout << "Enter text file name for deleting: " << endl;

	cin >> name;
	if (type == Text)
		strcat_s(name, ".txt");
	return name;
}

int main()
{
	open_menu();

	return 0;
}