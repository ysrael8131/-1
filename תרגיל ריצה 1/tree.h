#pragma once

#include <iostream>
#include <list>
#include <string>
#include<algorithm>
using namespace std;

class Node;

//Answer: for each answer, the string, and the pointer to the node where to continue
class Answer
{
public:
	string ans;
	Node* son;
	Answer(string s, Node *p) { ans = s; son = p; }
};

//Node: each node in the decision tree
class Node
{
	void removeSonValue(string v);
public:
	list<Answer *> answersList;
	string value;
	bool isLeaf;
	Node(string v) { isLeaf = true;  value = v; }

	friend class Tree;
};


//Tree: the Decision Tree
class Tree
{
	Node *root;
	Node* search(Node *p, string val, Node *&parent);
	//returns node t where the string equals val. If t has a prent, the pointer parent will contain its address. 

	bool searchAndPrint(Node *p, string val);
	void print(Node *p, int level = 0);

	void process(Node *p);
public:
	Tree() { root = NULL; }
	~Tree() {
		deleteAllSubTree(root);
		root = 0;
	}
	void deleteAllSubTree(Node *t);
	void addRoot(string newval);
	bool addSon(string fatherquestion, string newanswer, string newval);
	void searchAndPrint(string val)
	{
		if (!searchAndPrint(root, val))
			cout << "Value not found" << endl;
	}
	void searchAndPrintArea(string val)
	{
		Node *parent;
		Node *area = search(root, val, parent);
		if (area) print(root);
	}
	void printAllTree() { print(root); }
	string printToString(Node *p);
	string printToString() { return printToString(root); }
	void deleteSubTree(string val);
	void process() { process(root); }
};

void Tree::print(Node *p, int level = 0)
{
	for (int i = 0; i < level; i++)
	{
		cout << "		";
	}
	cout << p->value << endl;
	list< Answer*>::iterator it = p->answersList.begin();
	for (; it != p->answersList.end(); it++)
	{
		for (int i = 0; i < (level * 2) + 1; i++)
		{
			cout << "	";
		}
		cout << (*it)->ans << endl;
		print((*it)->son, level + 1);
	}
}

Node* Tree::search(Node *p, string val, Node *&parent)
{
	if (p == nullptr || !p->isLeaf)
		return nullptr;
	if (p->value == val)
	{
		return p;
	}
	list< Answer*>::iterator it = p->answersList.begin();
	for (; it != p->answersList.end(); it++)
	{
		Node* a = search((*it)->son, val, p);
		if (a)
		{
			return a;
			parent = p;
		}

	}
	return nullptr;
}

void Tree::deleteAllSubTree(Node *t)
{
	if (!t->answersList.empty())
	{
		list< Answer*>::iterator it = t->answersList.begin();
		for (; it != t->answersList.end(); it++)
		{
			if ((*it)->son->answersList.empty())
			{
				delete (*it)->son;
				delete *it;
			}
			else
			{
				deleteAllSubTree((*it)->son);
				delete (*it)->son;
			}
		}
		delete t;
	}
}

void Tree::addRoot(string newval)
{
	root = new Node(newval);
}

bool Tree::addSon(string fatherquestion, string newanswer, string newval)
{
	Node* qustion = search(root, fatherquestion, root);
	Node* newSon = new Node(newval);
	if (qustion == nullptr)
	{
		return false;
	}
	qustion->answersList.push_back(new Answer(newanswer, newSon));
	qustion->isLeaf = false;
	return true;
}

bool Tree::searchAndPrint(Node *p, string val)
{

	Node*a = search(p, val, p);
	if (!a)
	{
		return false;
	}
	if (a == root)
	{
		cout << a->value<<endl;
		return true;
	}
	searchAndPrint(p, p->value);

	list< Answer*>::iterator it = p->answersList.begin();
	for (; it != p->answersList.end(); it++)
	{
		if ((*it)->son == a)
		{
			cout << (*it)->ans << endl;
			break;
		}
	}
	cout << a->value;
	return true;

}