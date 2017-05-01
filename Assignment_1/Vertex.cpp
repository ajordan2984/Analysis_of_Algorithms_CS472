#include "Vertex.h"

template <typename A>
Vertex<A>::Vertex()
{
	visited = false;
}

template <typename A>
void Vertex<A>::set_name(A input)
{
	name = input;
}
template <typename A>
A Vertex<A>::get_name()
{
	return name;
}
template <typename A>
void Vertex<A>::set_visit(bool data)
{
	visited = data;
}
template <typename A>
bool Vertex<A>::get_visit()
{
	return visited;
}

template <typename A>
Vertex<A>::~Vertex(){}
