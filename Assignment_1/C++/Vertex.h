#pragma once
#include <string>
#include <vector>
using namespace std;
template <typename A>
class Vertex
{
public:
	Vertex();
	void set_name(A);
	A get_name();
	~Vertex();
	vector<Vertex<A>*> neighbors;
	void set_visit(bool);
	bool get_visit();
private:
	A name;
	bool visited;
};