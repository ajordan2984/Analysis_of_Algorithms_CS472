#pragma once
#include <string>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <fstream>
using namespace std;
extern ofstream outfile;
template <typename A>
class Graph
{
public:
	virtual vector<A> neighbors(A) = 0;
	virtual bool adjacent(A, A) = 0;
	virtual void addEdge(A, A) = 0;
	virtual void deleteEdge(A, A) = 0;
	virtual Graph<A>& bfs(Graph<A>&, A&) = 0;
	virtual Graph<A>& dfs(Graph<A>&, A&) = 0;
};