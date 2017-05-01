/*
Matrix_Graph Class accepts both
Matrix_Graph and AdjacencyList_Graph Classes
in the function bfs and dfs and then returns
a reference to a new Matrix_Graph class 
that contains the nodes in either bfs or 
dfs order.
*/
#pragma once
#include "Graph.h"
using namespace std;
template <typename A>
class Matrix_Graph : public Graph<A>
{
public:

	Matrix_Graph(){
		gsize = 10;
		graph = NULL;
		graph = new bool*[gsize];
		for (int i = 0; i < gsize; i++)
			graph[i] = new bool[gsize];
		for (int i = 0; i < gsize; i++)
			for (int j = 0; j < gsize; j++)
				graph[i][j] = false;
	}

	/* Do breathfirst traversal of the graph g, starting
	from node startNode,and returning a reference to a
	new Graph<type> that contains the BFS traversal of g.
	This class overides the bfs function in the Graph class */
	virtual Graph<A>& bfs(Graph<A> &g, A &startNode)
	{
		outfile << "Entering Adjacency Matrix Graph BFS" << endl;
		// New graph pointer
		Graph<A> *mg = new Matrix_Graph<A>();
		// Used to track which nodes have been visited
		map <A, bool> visited;
		// Q for storing levels of nodes
		queue<A> vertexQ;
		vector<A> edges = g.neighbors(startNode);

		if (edges.size()>0)
		{
			//Start node exist
			//Push onto the Q
			vertexQ.push(startNode);

			//While loop cycles through level of nodes
			while (vertexQ.size() != 0)
			{
				//Grab top node
				A current_node = vertexQ.front();
				//Mark node as visited
				visited[current_node] = true;
				//Display node
				outfile << "Visiting:" << current_node << endl;
				//Get list of neighbors
				vector<A> edges = g.neighbors(current_node);
				// Check if list exist
				if (edges.size() != 0)
					for (int i = 0; i < edges.size(); i++)
					{	//Check if node has been visited already
					//if not, add to Q
					if (visited.count(edges[i]) < 1)
						vertexQ.push(edges[i]);
					else
						outfile << edges[i] << " has already been visited." << endl;
					}
				//No more edges present at this point
				//Mark node as visited and cycle through rest of Q
				outfile << current_node << " has no more edges." << endl;
				vertexQ.pop();
			}
		}
		else
			outfile << "No vertex in graph." << endl;
		outfile << "Finished." << endl;
		outfile << endl;
		return *mg;
	}//end bfs
	/* Do depthfirst traversal of the graph g, starting
	from node startNode,and returning a reference to a
	new Graph<type> that contains the DFS traversal of g.
	This class overides the dfs function in the Graph class*/
	virtual Graph<A>& dfs(Graph<A> &g, A &startnode)
	{
		outfile << "Entering Adjacency Matrix Graph DFS" << endl;
		Graph<A> *mg = new Matrix_Graph<A>();
		map<A, bool> visited;
		stack<A> vertexS;

		vector<A>edges = g.neighbors(startnode);
		if (edges.size() != 0)
		{
			vertexS.push(startnode);
			while (vertexS.size() != 0)
			{
				A current_node = vertexS.top();
				outfile << "Visiting:" << current_node << endl;
				vector<A>edges = g.neighbors(current_node);
				visited[current_node] = true;
				vertexS.pop();

				for (int i = 0; i < edges.size(); i++)
				{
					mg->addEdge(current_node, edges[i]);
					if (visited.count(edges[i]) < 1)
						vertexS.push(edges[i]);
					else
						outfile << "Already visited:" << edges[i] << endl;
				}
			}//end while
		}
		else
			outfile << "No Vertex in graph." << endl;
		outfile << "Finished." << endl;
		outfile << endl;
		return *mg;
	}//end dfs
	virtual vector<A> neighbors(A vertex)
	{
		vector<A> n;
		if (VertexExist(vertex))
			for (int i = 0; i < labels.size(); i++)
				if (graph[index(vertex)][i])
					n.push_back(labels[i]);
		return n;
	}
	virtual bool adjacent(A vertex, A edge)
	{
		if (VertexExist(vertex))
			if (VertexExist(edge))
				return graph[index(vertex)][index(edge)];
			else
				return false;
	}
	virtual void addEdge(A vertex, A edge)
	{
		if (!VertexExist(edge))
			labels.push_back(edge);

		if (!VertexExist(vertex))
		{
			labels.push_back(vertex);
			graph[index(vertex)][index(vertex)] = true;
			graph[index(vertex)][index(edge)] = true;
		}
		if (VertexExist(vertex))
			graph[index(vertex)][index(edge)] = true;
	}
	virtual void deleteEdge(A vertex, A edge)
	{
		if (VertexExist(vertex))
			if (VertexExist(edge))
				graph[index(vertex)][index(edge)] = false;
			else
				outfile << "Edge:" << edge << " does not exist." << endl;
		else
			outfile << "Vertex:" << vertex << " does not exist." << endl;
	}
	bool VertexExist(A item)
	{
		if (labels.size()>0)
			for (int i = 0; i < labels.size(); i++)
				if (labels[i] == item)
					return true;
		return false;
	}
	int index(A custom_index)
	{
		for (int i = 0; i < labels.size(); i++)
			if (labels[i] == custom_index)
				return i;
	}

	Matrix_Graph<A>::~Matrix_Graph(){}
private:
	int gsize;
	vector <A> labels;
	bool **graph;

};