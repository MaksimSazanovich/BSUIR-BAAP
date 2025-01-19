#include <iostream>
#include<string.h>

using namespace std;


//Имеется список книг. Каждый элемент списка содержит следующую информацию: название, фамилия автора, год издания, количество страниц.
//Вывести в алфавитном порядке названия книг, изданных до 1990 года
int main()
{
    struct book
    {
        char title[40];
        char author_surname[40];
        int year;
        int count_pages;
    };

    int n;
    cout << "Input count of books: ";
    cin >> n;
    if (n == NULL || n <= 0)
    {
        cout << "Wrong input!";
        return 1;
    }
    book* book_list = new book[n];

    for (int i = 0; i < n; i++)
    {
        cout << endl;
       
        cout << "Input title " << i + 1 << " book: ";
        cin >> book_list[i].title;
        
        cout << "Input author surname of " << i + 1 << " book: ";
        cin >> book_list[i].author_surname;

        cout << "Input year of publication " << i + 1 << " book: ";
        cin >> book_list[i].year;

        if (book_list[i].year == NULL || book_list[i].year <= 0)
        {
            cout << "Wrong input!";
            return 1;
        }

        cout << "Input count of pages " << i + 1 << " book: ";
        cin >> book_list[i].count_pages;

        if (book_list[i].count_pages == NULL || book_list[i].count_pages <= 0)
        {
            cout << "Wrong input!";
            return 1;
        }
    }

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

    cout << endl;

    for (int i = 0; i < n; i++)
    {
        if (book_list[i].year < 1990) 
        {
            cout << book_list[i].title << endl;
        }
    }

    delete[] book_list;
    book_list = NULL;
}

