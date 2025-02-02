#include <iostream>
#include<string.h>
using namespace std;

struct element
{
	double inf;
	char char_inf;
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

	void push(double inf)
	{
		element* el = new element;
		el->inf = inf;
		el->next_adress = top;
		top = el;
		size++;
	}

	void push(char char_inf)
	{
		element* el = new element;
		el->char_inf = char_inf;
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

char str[] = "b-s*(x/(x^w+y^w))";
//b s x x w ^ y w ^ + / * -
char str_out[20];
double values[200];

int get_priority(char ch)
{
	switch (ch)
	{
	case'(':case')':return 0;
	case'+':case'-':return 1;
	case'*':case'/':return 2;
	case'^':return 3;
	default: return -1;
	}
}

void transform_string(char* str_in, char* str_out)
{
	stack stack;
	int n = 0;
	int len = strlen(str_in);
	char ch;
	double inf;
	for (int i = 0; i < len; i++)
	{
		ch = str_in[i];
		//b-s*(x/(x^w+y^w))
		if (ch > 'A' && ch != '^')
		{
			str_out[n++] = ch;
			continue;
		}
		if (stack.is_empty() || ch == '(')
		{
			stack.push(ch);
			continue;
		}
		if (ch == ')')
		{
			element* el = stack.top;
			while (el->char_inf != '(')
			{	
				str_out[n++] = (char)el->char_inf;
				stack.pop();
				el = stack.top;
			}
			stack.pop();
			continue;
		}
		//b-s*(x/(x^w+y^w))
		int pr = get_priority(ch);
		element* el = stack.top;
		while (!stack.is_empty() && get_priority(stack.top->char_inf) >= pr)
		{	
			str_out[n++] = (char)el->char_inf;
			stack.pop();
			el = stack.top;
		}
		stack.push(ch);
	}
	element* el = stack.top;
	while (!stack.is_empty())
	{	
		str_out[n++] = (char)el->char_inf;
		stack.pop();
		el = stack.top;
	}
	str_out[n++] = '\0';
	stack.delete_stack();
}

double get_value(char ch)
{
	switch (ch)
	{
	case 'b': return values[int('b')];
	case 's': return values[int('s')];
	case 'x': return values[int('x')];
	case 'y': return values[int('y')];
	case 'w': return values[int('w')];
	}
}

double calculate(char* str)
{
	stack stack;
	char ch;
	double inf, inf_1, inf_2;
	int len = strlen(str);

	for (int i = 0; i < len; i++)
	{
		ch = str[i];
		//b s x x w ^ y w ^ + / * -
		if (ch >= 'A' && ch != '^')
		{
			stack.push(get_value(ch));
			continue;
		}
		inf_2 = stack.top->inf;
		stack.pop();
		inf_1 = stack.top->inf;
		stack.pop();

		switch (ch)
		{
		case'+': stack.push(inf_1 + inf_2); break;
		case'-': stack.push(inf_1 - inf_2); break;
		case'*': stack.push(inf_1 * inf_2); break;
		case'/': stack.push(inf_1 / inf_2); break;
		case'^': stack.push(pow(inf_1, inf_2)); break;
		}
	}
	inf = stack.top->inf;
	stack.delete_stack();
	return inf;
}

int main()
{
	cout << "Enter b ";
	cin >> values[int('b')];
	cout << "Enter s ";
	cin >> values[int('s')];
	cout << "Enter x ";
	cin >> values[int('x')];
	cout << "Enter y ";
	cin >> values[int('y')];
	cout << "Enter w ";
	cin >> values[int('w')];

	transform_string(str, str_out);
	puts(str_out);

	double s = calculate(str_out);
	cout << "Res = " << s << endl;
	return 0;
}
