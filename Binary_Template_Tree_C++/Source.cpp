#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Tree.cpp"
using namespace std;

template <typename A>
void readinvalues(Tree<A>*);
//globals
ifstream in;


int main()
{
	in.open("dat.txt");


	Tree<string> *FirstTreePtr = new Tree<string>();
	readinvalues(FirstTreePtr);
	FirstTreePtr->LevelOrder();
	FirstTreePtr->DeleteNode("a");
	
	//// Create new tree and copy old tree into it
	
	Tree<string> *NewTreePtr = new Tree<string>(FirstTreePtr);
	//NewTreePtr->InOrder();

	Tree<string>* foundnode = NewTreePtr->DFS("noted");
	if (foundnode != nullptr)
		cout << "Node: noted was found with DFS." << endl;

	foundnode = NewTreePtr->BFS("york");
	if (foundnode != nullptr)
		cout << "Node: noted was found with BFS." << endl;


	//// Delete Trees
	FirstTreePtr->DeleteTree();
	NewTreePtr->DeleteTree();
	in.close();
	cout << "Finished." << endl;
	return 0;
}

template <typename A>
void readinvalues(Tree<A> *tree)
{
	int count = 0, sz = 0;
	string s1;
	string temp = "";
	while (in >> s1)
	{
		sz = s1.length();
		for (int j = 0; j < sz; j++)
		{
			if (isalpha(s1[j]))
				temp += tolower(s1[j]);
		}

		if (temp.length() > 0 && temp != "")
			tree->Insert(temp);
		temp = "";
	}
	return;
}