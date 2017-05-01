// Author: Andrew Jordan
// Institution: Athens State University
// Class: CS472 Programming Assignment 1
// Instructor:Dr.Adam Lewis
// Templated Graphs Depth First Search and Breadth First Search
// Due: 1/24/2017

#include <iostream>
#include <fstream>
#include "Matrix_Graph.cpp"
#include "AdjacencyList_Graph.cpp"
#include <sstream>
#include <algorithm>
#include <stdio.h>
using namespace std;
template <typename A>
void addEdges(Graph<A>*);
ofstream outfile;

int main()
{
	outfile.open("Results.txt");
	Graph<int> *matrixgraph = new Matrix_Graph<int>();
	Graph<int> *listgraph = new AdjacencyList_Graph<int>();
	addEdges(matrixgraph);
	addEdges(listgraph);

	int startnode = 0;
	Graph<int> &mdfs = matrixgraph->dfs(*matrixgraph, startnode);
	Graph<int> &mbfs = matrixgraph->bfs(*matrixgraph, startnode);
	Graph<int> &ldfs = listgraph->dfs(*listgraph, startnode);
	Graph<int> &lbfs = listgraph->bfs(*listgraph, startnode);
	cout << "Main is exiting.." << endl;
	return 0;
}

template<typename A>
void addEdges(Graph<A> *graph)
{
	ifstream filein;
	filein.open("nodes.txt");
	if (!filein)
		cout << "Error:Not in file." << endl;
	else
	{
		int i = 0;
		int edge;
		string numbers;
		while (!filein.eof())
		{
			getline(filein, numbers);
			istringstream snumbers(numbers);
			while (!snumbers.eof())
			{
				snumbers >> edge;
				graph->addEdge(i, edge);
			}
			i++;
		}//end !filein.eof()
	}
}