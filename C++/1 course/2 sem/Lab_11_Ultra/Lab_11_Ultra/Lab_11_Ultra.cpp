#include <iostream>
#include<io.h>

using namespace std;

struct book
{
	char title[40];
	char author_surname[40];
	int year;
	int count_pages;
};

FILE* fl;
char file_name[100] = "q.txt";
int n;

int books_count;
book* book_list;

int open_file();

void parse_file();

int get_books_count();

void get_symbol(char& ch, int file_read_len);

int choose_sort();
int non_rec_quick_sort();
int selection_sort();

void print_array();

bool is_double_backslash(FILE* file, int cur_i);
void delete_last_spaces(char(&str)[100]);

int main()
{
	bool file_opened = false;

	do
	{
		if (!file_opened)
		{
			if (open_file() == 1)
			{
				cout << "File doesn't exist" << endl;
			}
			else
				file_opened = true;
		}
	} while (!file_opened);


	rewind(fl);
	n = _filelength(_fileno(fl)) / sizeof(char);

	books_count = get_books_count();

	book_list = new book[books_count];

	parse_file();

	if (choose_sort() == 1)
		return 1;

	delete[] book_list;
	return 0;
}

int open_file()
{
	cout << "Enter file name: " << endl;

	gets_s(file_name);
	strcat_s(file_name, ".txt");
	if (fopen_s(&fl, file_name, "rt+"))
	{
		return 1;
	}
	cout << "File opened" << endl;

	return 0;
}

void parse_file()
{
	char ch;
	char next_ch;

	int file_read_len = 0;

	char field[100];
	int field_len = 0;

	int field_start = 0;
	bool is_first_letter_of_field = true;

	int field_number = 0;

	char field_dlm = '\\';
	char struct_dlm = ';';

	for (int i = 0; i < books_count; i++)
	{
		get_symbol(ch, file_read_len);
		get_symbol(next_ch, file_read_len + 1);

		while (ch != struct_dlm && file_read_len < n)
		{
			fseek(fl, sizeof(char) * file_read_len, SEEK_SET);
			fread(&ch, sizeof(char), 1, fl);

			fseek(fl, sizeof(char) * file_read_len + 1, SEEK_SET);
			fread(&next_ch, sizeof(char), 1, fl);

			if (ch != ' ' && ch != field_dlm && ch != struct_dlm && is_first_letter_of_field)
			{
				is_first_letter_of_field = false;
				field_start = file_read_len;
			}

			if (is_double_backslash(fl, file_read_len) || next_ch == struct_dlm || file_read_len == n - 1)
			{
				if (is_double_backslash(fl, file_read_len) || ch == struct_dlm)
				{
					field_len = file_read_len - field_start;
				}
				else if (file_read_len == n - 1)
				{
					field_len = file_read_len - field_start + 1;
				}

				int j = 0;
				for (int i = field_start; i < field_start + field_len; i++, j++)
				{
					fseek(fl, sizeof(char) * i, SEEK_SET);
					fread(&ch, sizeof(char), 1, fl);
					field[j] = ch;
				}
				field[j] = '\0';
				delete_last_spaces(field);

				is_first_letter_of_field = true;

				switch (field_number)
				{
				case 0:
					strcpy_s(book_list[i].title, field);
					break;
				case 1:
					strcpy_s(book_list[i].author_surname, field);
					break;
				case 2:
					book_list[i].year = atoi(field);
					break;
				case 3:
					book_list[i].count_pages = atoi(field);
					break;
				}
				field[0] = '\0';
				field_number++;
			}

			file_read_len++;
		}
		file_read_len++;
		is_first_letter_of_field = true;
		field_number = 0;
	}


	print_array();

}

int get_books_count()
{
	char ch;
	int books_count = 0;
	for (int i = 0; i < n; i++)
	{
		fseek(fl, sizeof(char) * i, SEEK_SET);
		fread(&ch, sizeof(char), 1, fl);

		if (ch == ';')
			books_count++;
	}
	books_count++;

	return books_count;
}

void get_symbol(char& ch, int file_read_len)
{
	fseek(fl, sizeof(char) * file_read_len, SEEK_SET);
	fread(&ch, sizeof(char), 1, fl);
}

int choose_sort()
{
	int menu;
	do
	{
		cout << "Choose sort type: " << endl;
		cout << "1. QuickSort (in non - decreasing order of number of pages)" << endl;
		cout << "2. Selection sort (in non - decreasing order of number of pages)" << endl;
		cout << "0. Exit" << endl;

		cin >> menu;
		switch (menu)
		{
		case 1:
			if (non_rec_quick_sort() == 1)
			{
				cout << "Quick sort error" << endl;
				return 1;
			}
			break;
		case 2:
			if (selection_sort() == 1)
			{
				cout << "Selection sort error" << endl;
				return 1;
			}
			break;
		case 0: return 1;
		default:
		{
			cout << "Invalid choice. Try again" << endl;
			continue;
		}
		}
		if (menu >= 1 && menu <= 2)
			print_array();

	} while (true);

	return 0;
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
int non_rec_quick_sort()
{
	//book* book_list = get_book_list();
	if (book_list == NULL)
		return 1;

	int i, j, left, right, s = 0;
	book x;
	push(0, books_count - 1, s);
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

}

int selection_sort()
{
	if (book_list == NULL)
		return 1;

	int min;

	for (int i = 0; i < books_count; i++)
	{
		min = i;
		for (int j = i + 1; j < books_count; j++)
		{
			if (book_list[j].count_pages < book_list[min].count_pages)
			{
				min = j;
			}
		}
		swap(book_list[i], book_list[min]);
	}
	return 0;
}


void print_array()
{
	for (int i = 0; i < books_count; i++)
	{
		cout << book_list[i].title << " " << book_list[i].author_surname << " " << book_list[i].year << " " << book_list[i].count_pages << endl;
	}
}

bool is_double_backslash(FILE* file, int cur_i)
{
	char ch;
	char next_ch;

	fseek(file, sizeof(char) * cur_i, SEEK_SET);
	fread(&ch, sizeof(char), 1, file);

	fseek(file, sizeof(char) * (cur_i + 1), SEEK_SET);
	fread(&next_ch, sizeof(char), 1, file);

	if (ch == '\\' && next_ch == '\\')
		return true;
	return false;
}

void delete_last_spaces(char(&str)[100])
{
	int len = strlen(str);
	for (int i = len - 1; str[i] == ' '; i--)
	{
		str[i] = '\0';
	}
}



