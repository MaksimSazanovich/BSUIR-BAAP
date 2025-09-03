/*Создать двусвязанный список, состоящий из n целых чисел. Переместить
//во второй список элементы, находящиеся между минимальным
и максимальным элементами первого списка.*/

#include <iostream>
using namespace std;

struct element
{
    int inf;
    element *right;
    element *left;
};

struct list
{
    element *front = nullptr;
    element *back = nullptr;

    bool is_empty()
    {
        if (front == nullptr)
            return true;
        return false;
    }

    void add_element(int inf)
    {
        element *new_el = new element;
        new_el->inf = inf;

        if (is_empty())
        {
            new_el->left = nullptr;
            front = back = new_el;
            return;
        }
        back->right = new_el;
        new_el->left = back;
        back = new_el;
    }

    void print()
    {
        element *el = front;
        while (el != nullptr)
        {
            cout << el->inf << " ";
            el = el->right;
        }
        cout << endl;
    }

    element *get_min()
    {
        if (is_empty())
        {
            cerr << "List is empty" << endl;
            return nullptr;
        }

        element *el = front;
        element *el_min = el;

        while (el != nullptr)
        {
            if (el->inf < el_min->inf)
            {
                el_min->inf = el->inf;
                el_min->left = el->left;
                el_min->right = el->right;
            }

            el = el->right;
        }

        return el_min;
    }
};

int main()
{
    int n = 10;
    list *l = new list[n];
    l.add_element(5);
    l.add_element(4);
    l.add_element(1);
    l.add_element(4);
    l.add_element(5);
    l.add_element(6);
    l.add_element(56);
    l.add_element(4);
    l.add_element(87);
    l.add_element(4);

    l.print();
    cout << l.get_min()->inf;

    return 0;
}