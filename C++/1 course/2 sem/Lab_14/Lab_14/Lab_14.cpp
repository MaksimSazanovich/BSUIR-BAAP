#include <iostream>
#include "Lab_14.h"

using namespace std;
//B7. Создать двусвязанный список, состоящий из n целых чисел.
//Переместить во второй список элементы, находящиеся между минимальным и максимальным элементами первого списка.

struct element
{
	int inf;
	element* left;
	element* right;
};

struct list
{
	element* front = nullptr;
	element* back = nullptr;

	bool is_empty()
	{
		if (front)
			return false;
		else
			return true;
	}

	void push(int inf)
	{
		element* el = new element;
		el->inf = inf;
		el->right = nullptr;
		if (!front)
		{
			el->left = nullptr;
			front = back = el;
			return;
		}
		back->right = el;
		el->left = back;
		back = el;
	}

	void pop()
	{
		element* el = front;
		front = front->right;
		delete el;
		if (!front)
			back = nullptr;
		else
			front->left = nullptr;
	}

	void print()
	{
		element* el = front;
		while (el != nullptr)
		{
			cout << el->inf << " ";
			el = el->right;
		}
		cout << endl;
	}

	element* search(int x)
	{
		if (!front)
			return nullptr;
		element* el = front;
		while (el->inf != x && el->right != nullptr)
		{
			el = el->right;
		}
		if (el->inf == x)
			return el;
		else
			return nullptr;
	}

	void del(int x)
	{
		element* el = search(x);
		if (!el)
			return;
		if (front == back)
		{
			front = nullptr;
			back = nullptr;
		}
		else if (!el->left)
		{
			front = el->right;
			front->left = nullptr;
		}
		else if (!el->right)
		{
			back = el->left;
			back->right = nullptr;
		}
		else
		{
			el->right->left = el->left;
			el->left->right = el->right;
		}
		delete el;
	}

	// Добавление элемента после заданного
	void push_left(element* el, int inf)
	{
		element* el_left = new element;
		el_left->inf = inf;
		el_left->right = el->right;
		el_left->left = el;
		el->right = el_left;
		if (el_left->right)
			el_left->right->left = el_left;
	}

	element* get_min()
	{
		if (!front)
			return nullptr;

		element* el = front;
		element* el_min = new element;
		el_min->inf = el->inf;
		el_min->left = el->left;
		el_min->right = el->right;

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

	element* get_max()
	{
		if (!front)
			return nullptr;

		element* el = front;
		element* el_max = new element;
		el_max->inf = el->inf;
		el_max->left = el->left;
		el_max->right = el->right;
		while (el != nullptr)
		{
			if (el->inf > el_max->inf)
			{
				el_max->inf = el->inf;
				el_max->left = el->left;
				el_max->right = el->right;
			}
			el = el->right;
		}
		return el_max;
	}

	void print_element(int x)
	{
		element* el = search(x);
		cout << el->inf << endl;
	}

	void print_element(element* el)
	{
		cout << el->inf << endl;
	}

	bool is_right_list(element* el_min, element* el_max)
	{
		element* el = el_min;
		while (el->inf != el_max->inf && el->right != nullptr)
		{
			el = el->right;
		}
		if (el->inf == el_max->inf)
			return true;
		else
			return false;
	}

	void delete_list()
	{
		while (!is_empty())
			pop();
	}
};


int main()
{
	list s;
	int n;
	int e;
	cout << "Enter count of elements (>2) ";
	cin >> n;
	if (n < 3)
	{
		cout << "Too few elements to move ";
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		cout << "Enter element ";
		cin >> e;
		s.push(e);
	}
	//s.push(10);
	//s.push(7);
	//s.push(3);
	//s.push(5);
	s.print();
	element* el_min = s.get_min();
	element* el_max = s.get_max();

	list s_2;

	//cout << "is_right_list " << s.is_right_list(el_min, el_max) << endl;
	element* el = s.is_right_list(el_min, el_max) ? el_min : el_max;
	element* el_end = s.is_right_list(el_min, el_max) ? el_max : el_min;

	//s.print_element(el);
	//s.print_element(el_end);
	el = el->right;
	while (el->inf != el_end->inf)
	{
		s_2.push(el->inf);
		el = el->right;
		s.del(el->left->inf);
	}

	cout << "Source: ";
	s.print();
	cout << "Result: ";
	s_2.print();

	s.delete_list();
	s_2.delete_list();
	delete el_min;
	delete el_max;
}

