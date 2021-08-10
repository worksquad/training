#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

class Tree
{
private:
	string data;
	vector<Tree*> children = vector<Tree*>();
public:
	Tree(string data) { this->data = data; }
	int childnum() { return children.size(); };
	string getdata() { return data; }
	Tree* child(int i) { return children[i]; };
	void print() { cout << data << endl; };
	void add(Tree* child) { children.push_back(child); };
	~Tree() { for (Tree* c : children) { delete c; } children.clear(); };
};

void printall(Tree* root)
{
	if (root != NULL)
	{
		int n = root->childnum();
		for (int i = 0; i < n; i++)	printall(root->child(i));
		root->print();
	}
}

void prall(Tree* root)
{
	stack<Tree*> toprint;
	toprint.push(root);
	while (toprint.size() != 0)
	{
		Tree* temp = toprint.top();
		temp->print();
		toprint.pop();
		for (int i = 0; i < temp->childnum(); i++) toprint.push(temp->child(i));
	}
}

Tree* createNprint()
{
	unique_ptr<Tree> root = move(make_unique<Tree>("root"));
	Tree* temp = root.get();
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			string tstr = temp->getdata() + " " + to_string(i);
			temp->add(new Tree(tstr));
		}
		temp = temp->child(j);
	}
	temp = root.get();
	printall(temp);
	prall(temp);
	return root.get()->child(1);
}

int main()
{
	Tree * check = createNprint();
}