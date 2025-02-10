#include<iostream>
#include <string>

#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>

using namespace std;
//Удалить все узлы дерева, имеющие значение ключа больше 5.
struct tnode
{
	int inf;
	tnode* left;
	tnode* right;
};

#define LN { std::cout << __LINE__ << std::endl; }
#define DEB(x) { std::cout << #x << "=(" << (x) << ") "; }

// https://en.wikipedia.org/wiki/Box_Drawing_(Unicode_block)
static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";
//static std::string ch_hor = "\u2500" /*─*/, ch_ver = "\u2502" /*│*/, ch_ddia = "\u250C" /*┌*/, ch_rddia = "\u2510" /*┐*/, ch_udia = "\u2514" /*└*/, ch_ver_hor = "\u251C\u2500" /*├─*/, ch_udia_hor = "\u2514\u2500" /*└─*/, ch_ddia_hor = "\u250C\u2500" /*┌─*/, ch_ver_spa = "\u2502 " /*│ */;
void dump4(tnode const* node, bool high = true, std::vector<std::string> const& lpref = std::vector<std::string>(), std::vector<std::string> const& cpref = std::vector<std::string>(), std::vector<std::string> const& rpref = std::vector<std::string>(), bool root = true, bool left = true, std::shared_ptr<std::vector<std::vector<std::string>>> lines = nullptr) {
	if (!node) return;
	typedef std::vector<std::string> VS;
	auto VSCat = [](VS const& a, VS const& b) { auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
	if (root) lines = std::make_shared<std::vector<VS>>();
	if (node->left)
		dump4(node->left, high, VSCat(lpref, high ? VS({ " ", " " }) : VS({ " " })), VSCat(lpref, high ? VS({ ch_ddia, ch_ver }) : VS({ ch_ddia })), VSCat(lpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), false, true, lines);
	auto sval = std::to_string(node->inf);
	size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
	for (size_t i = 0; i < sval.size(); ++i)
		lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, { std::string(1, sval[i]) }));
	if (node->right)
		dump4(node->right, high, VSCat(rpref, high ? VS({ ch_hor, " " }) : VS({ ch_hor })), VSCat(rpref, high ? VS({ ch_rddia, ch_ver }) : VS({ ch_rddia })), VSCat(rpref, high ? VS({ " ", " " }) : VS({ " " })), false, false, lines);
	if (root) {
		VS out;
		for (size_t l = 0;; ++l) {
			bool last = true;
			std::string line;
			for (size_t i = 0; i < lines->size(); ++i)
				if (l < (*lines).at(i).size()) {
					line += lines->at(i)[l];
					last = false;
				}
				else line += " ";
			if (last) break;
			out.push_back(line);
		}
		for (size_t i = 0; i < out.size(); ++i)
			std::cout << out[i] << std::endl;
	}
}

struct tree
{
	tnode* root = nullptr;

	bool is_empty()
	{
		if (root)
			return false;
		else
			return true;
	}

	void push(int inf)
	{
		tnode* new_node = new tnode;
		new_node->inf = inf;
		new_node->left = nullptr;
		new_node->right = nullptr;

		if (!root)
		{
			root = new_node;
			return;
		}

		bool is_left_new_node;
		tnode* parent = root;
		tnode* node = root;

		while (node)
		{
			parent = node;
			is_left_new_node = inf < node->inf;
			if (is_left_new_node)
				node = node->left;
			else
				node = node->right;
		}

		if (is_left_new_node)
			parent->left = new_node;
		else
			parent->right = new_node;
	}

	tnode* add_balanced_tree(int left, int right, int* array)
	{
		tnode* node;
		int m;

		if (left > right)
			return nullptr;

		m = (left + right) / 2;

		node = new tnode;
		node->inf = array[m];

		node->left = add_balanced_tree(left, m - 1, array);
		node->right = add_balanced_tree(m + 1, right, array);

		return node;
	}

	void pop(int x)
	{
		tnode* node = root;
		tnode* parent = root;
		tnode* new_node;
		tnode* new_parent;

		while (node && node->inf != x)
		{
			parent = node;
			if (x < node->inf)
				node = node->left;
			else
				node = node->right;
		}

		if (!node)
			return;

		new_parent = node;
		if (!node->left)
			new_node = node->right;
		else
		{
			new_node = node->left;
			while (new_node->right != nullptr)
			{
				new_parent = new_node;
				new_node = new_node->right;
			}
		}

		if (new_node)
		{
			if (new_parent->left == new_node)
				new_parent->left = new_node->left;
			else
				new_parent->right = new_node->left;
			new_node->right = node->right;
			new_node->left = node->left;
		}

		if (node == root)
			root = new_node;
		else if (parent->left == node)
			parent->left = new_node;
		else
			parent->right = new_node;
		delete node;
	}

	void print_reverse(tnode* node)
	{
		if (!node)
			return;
		print_reverse(node->left);
		cout << node->inf << " ";
		print_reverse(node->right);
	}

	void print_straight(tnode* node)
	{
		if (!node)
			return;
		cout << node->inf << " ";
		print_straight(node->left);
		print_straight(node->right);
	}

	void print_trail(tnode* node)
	{
		if (!node)
			return;
		print_trail(node->left);
		print_trail(node->right);
		cout << node->inf << " ";
	}

	void print_node(int key)
	{
		tnode* node = search(key);
		cout << node->inf << endl;
	}

	void print_node(tnode* node)
	{
		cout << node->inf << endl;
	}

	int search_max()
	{
		tnode* node = root;
		while (node->right != nullptr)
			node = node->right;
		return node->inf;
	}

	int search_min()
	{
		tnode* node = root;
		while (node->left != nullptr)
			node = node->left;
		return node->inf;
	}

	tnode* search(int key)
	{
		tnode* node = root;
		while (node)
		{
			if (node->inf == key)
				return node;
			if (key < node->inf)
				node = node->left;
			else
				node = node->right;
		}
	}

	tnode* delete_tree(tnode* node)
	{
		if (!node)
			return nullptr;
		
		delete_tree(node->left);
		delete_tree(node->right);
		pop(node->inf);
		//dump4(root, false);
	}
};


int main()
{
	tree tree;
	//int n;
	//int e;
	//cout << "Enter count of element ";
	//cin >> n;
	//for (int i = 0; i < n; i++)
	//{
	//	cout << "Enter element ";
	//	cin >> e;
	//	tree.push(e);
	//}
	
	
	// 3 1 21 10 42
	//n = rand() % 30;
	//cout << "n " << n << endl;
	//for (int i = 0; i < n; i++)
	//{
	//	tree.push(rand() % 46);
	//}

	int array[] = { 1, 3, 5, 6, 8 };
	int n = sizeof(array) / sizeof(array[0]);
	tree.root = tree.add_balanced_tree(0, n-1, array);

	tree.print_reverse(tree.root);
	cout << endl;
	tree.print_straight(tree.root);
	cout << endl;
	tree.print_trail(tree.root);
	cout << endl;
	dump4(tree.root, false);
	cout << endl;
	tnode* node = tree.root;
	while (node)
	{
		if (node->inf > 5)
		{
			tree.pop(node->inf);
			//dump4(tree.root, false);
			node = tree.root;
		}
		else
			node = node->right;
	}
	cout << "Result" << endl;
	if (!tree.root)
		cout << "All tree was deleted" << endl;
		else
			dump4(tree.root, false);

	tree.delete_tree(tree.root);
	return 0;
}