/*
AdjacencyList_Graph Class accepts both
Matrix_Graph and AdjacencyList_Graph Classes
in the function bfs and dfs and then returns
a reference to a new AdjacencyList_Graph class
that contains the nodes in either bfs or
dfs order.
*/
#pragma once
#include "Vertex.cpp"
#include "Graph.h"
using namespace std;

template <typename A>
class AdjacencyList_Graph :public Graph<A>
{
public:
	AdjacencyList_Graph(){};

	/* Do breathfirst traversal of the graph g, starting
	from node startNode,and returning a reference to a
	new Graph<type> that contains the BFS traversal of g.
	This class overides the bfs function in the Graph class */
	virtual Graph<A>& bfs(Graph<A> &g, A &startNode)
	{
		outfile << "Entering Adjacency List Graph BFS" << endl;
		// New graph pointer
		Graph<A> *mg = new AdjacencyList_Graph<A>();
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
		Graph<A> *mg = new AdjacencyList_Graph<A>();
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
	}// end dfs

	// Checks if Vertex is in the Graph and 
	// returns a pointer to node or NULL pointer
	// if no node exits
	Vertex<A>* VertexExist(A vertex)
	{
		Vertex<A> *vp;
		typename vector<Vertex<A>*>::iterator Vit;
		for (Vit = graph.begin(); Vit != graph.end(); Vit++)
		{
			vp = *Vit;
			if (vp->get_name() == vertex)
				return vp;
		}
		return vp = NULL;
	}// end VertexExist

	// Creates a new Vertex node and returns a pointer to it
	Vertex<A>* CreateVertex(A vertex)
	{
		Vertex<A> *vp = new Vertex<A>();
		vp->set_name(vertex);
		return vp;
	}// end CreateVertex

	// Delete the edge from x to y if one exists
	virtual void deleteEdge(A vertex, A edge)
	{
		Vertex<A> *vp = VertexExist(vertex);
		if (vp != NULL)
		{
			// Vertex Exist
			// Find edge and delete out of vector of edges
			Vertex<A> *lookup_edge;
			// iterator over neighbors
			typename vector<Vertex<A>*>::iterator nlist;
			// Set iterator at begining of neighbor list
			nlist = vp->neighbors.begin();

			while (nlist != vp->neighbors.end())
			{
				lookup_edge = *nlist;
				if (lookup_edge->get_name() == edge)
					vp->neighbors.erase(nlist);
				nlist++;
			}
		}//end if Vertex Exist

		// Vertex does not exist
		else
			outfile << "No Vertex present in graph." << endl;
	}// end deleteEdge

	// Return a Vector containing the nodes have a edge from x to elements in the vector
	virtual vector<A> neighbors(A vertex)
	{
		Vertex<A> *vp = VertexExist(vertex);
		if (vp != NULL)
		{
			// Vertex Exist
			// Return vector of edge names
			vector<A> edges;
			Vertex<A> *ep;
			typename vector<Vertex<A>*>::iterator nit = vp->neighbors.begin();
			while (nit != vp->neighbors.end())
			{
				ep = *nit;
				edges.push_back(ep->get_name());
				nit++;
			}
			return edges;
		}
		else
		{
			A data;
			outfile << "No vertex:" << vertex << " present." << endl;
			outfile << "Enter new vertex:" << endl;
			cin >> data;
			return neighbors(data);
		}
	}// end neighbors

	// Is there a node from x to y
	virtual bool adjacent(A vertex, A edge)
	{
		Vertex<A> *vp = VertexExist(vertex);
		if (vp != NULL)
		{
			// Vertex Exist
			// Find edge and return true

			Vertex<A> *lookup_edge;
			// iterator over neighbor of edges
			typename vector<Vertex<A>*>::iterator nlist;

			// Set iterator at begining of neighbor list
			nlist = vp->neighbors.begin();

			while (nlist != vp->neighbors.end())
			{
				lookup_edge = *nlist;
				if (lookup_edge->get_name() == edge)
					return true;
				nlist++;
			}
		}// end if
		else
			outfile << "Vertex does not exist." << endl;
		return false;
	}// end adjacent

	// Add an edge from x to y if none exists
	// Add vertex into the graph if none exists
	virtual void addEdge(A vertex, A edge)
	{
		Vertex<A> *vp; //vertex pointer
		Vertex<A> *ep; // edges pointer
		vp = VertexExist(vertex);
		ep = VertexExist(edge);
		Vertex<A> *edgep;

		if (vp != NULL)
		{
			edgep = CreateVertex(edge);
			vp->neighbors.push_back(edgep);
		}
		else
		{
			vp = CreateVertex(vertex);
			// create new vector to store edges
			typename vector<Vertex<A>*> newneighbors;
			// Store new vertex in the graph
			graph.push_back(vp);
			newneighbors.push_back(CreateVertex(edge));
			vp->neighbors = newneighbors;
			if (ep == NULL)
				graph.push_back(CreateVertex(edge));
		}
	}
	~AdjacencyList_Graph();
private:
	vector<Vertex<A>*> graph;
};