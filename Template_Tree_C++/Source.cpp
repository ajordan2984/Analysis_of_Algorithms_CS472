#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "SampleTree.cpp"
using namespace std;

template <typename A>
void readinvalues(SampleTree<A>*);
//globals
ifstream in;


int main()
{
	in.open("dat.txt");
	SampleTree<string> *FirstTreePtr = new SampleTree<string>();
	readinvalues(FirstTreePtr);
	FirstTreePtr->InOrder();
	SampleTree<string> *NewTreePtr = new SampleTree<string>(FirstTreePtr);
	NewTreePtr->InOrder();
	in.close();
	cout << "Finished." << endl;
	return 0;
}

template <typename A>
void readinvalues(SampleTree<A> *tree)
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
			tree->InsertTree(temp);
		temp = "";
	}
	return;
}