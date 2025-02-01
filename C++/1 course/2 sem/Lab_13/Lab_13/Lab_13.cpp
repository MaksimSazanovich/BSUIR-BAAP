#include <iostream>

using namespace std;

struct element
{
	int inf;
	element* next_adress;
};

struct stack
{
	element* top = nullptr;
	int size = 0;

	bool is_empty()
	{
		if (top)
			return false;
		else
			return true;
	}

	void push(int inf)
	{
		element* el = new element;
		el->inf = inf;
		el->next_adress = top;
		top = el;
		size++;
	}

	void pop()
	{
		element* el = top;
		top = top->next_adress;
		delete el;
		size--;
	}

	void print()
	{
		element* el = top;
		while (el != nullptr)
		{
			cout << el->inf << " ";
			el = el->next_adress;
		}
		cout << endl;
	}

	element* search(int x)
	{
		if (!top)
			return nullptr;
		element* el = top;
		while (el->inf != x && el->next_adress != nullptr)
			el = el->next_adress;
		if (el->inf == x)
			return el;
		else
			return nullptr;
	}

	element* search_before(int x)
	{
		if (!top || !top->next_adress)
			return nullptr;
		element* el = top;
		while (el->next_adress->inf != x && el->next_adress->next_adress != nullptr)
			el = el->next_adress;
		if (el->next_adress->inf == x)
			return el;
		else
			return nullptr;
	}

	void del(int x)
	{
		if (!top)
			return;
		if (top->inf == x)
			pop();
		element* el, * pr_el;
		pr_el = search_before(x);
		el = pr_el->next_adress;
		pr_el->next_adress = pr_el->next_adress->next_adress;
		delete el;
	}

	// Обмен двух следующих за указанным элементов
	void exchange(element* el)
	{
		element* el_2;
		el_2 = el->next_adress->next_adress;
		el->next_adress->next_adress = el_2->next_adress;
		el_2->next_adress = el->next_adress;
		el->next_adress = el_2;
	}

	void print_element(element* el)
	{
		cout << el->inf << endl;
	}

	void delete_stack()
	{
		while (!is_empty())
			pop();
	}
};

int main()
{
	stack s;
	int n;
	int e;
	cout << "Enter count of element ";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter element ";
		cin >> e;
		s.push(e);
	}
	//s.push(10);
	//s.push(9);
	//s.push(8);
	//s.push(7);
	//s.push(6);
	//s.push(5);
	//s.push(4);
	//s.push(3);
	//s.push(2);
	//s.push(1);
	s.print();
	element* cur = s.top;
	int x;
	while (cur != nullptr && cur->next_adress != nullptr && cur->next_adress->next_adress != nullptr)
	{
		x = cur->next_adress->next_adress->inf;
		s.del(x);
		cur = cur->next_adress->next_adress;
	}
	s.print();
	s.delete_stack();

	return 0;
}

