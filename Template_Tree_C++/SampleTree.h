#pragma once
#include <functional>
template <typename A>
class SampleTree
{
public:
	SampleTree();
	SampleTree(SampleTree<A> *TreeBeingCopied);
	void InsertTree(A key);
	void DeleteNode(A key);
	void InOrder();
	void PreOrder();
	void PostOrder();

private:
	SampleTree<A>* MyNewNode(A val);
	void DeleteNodeHelper(SampleTree<A>*, SampleTree<A>*, int, A);
	void place_node(SampleTree<A> *current, SampleTree<A> *trail, int branch, int side);
	void case2children(SampleTree<A> *branch, SampleTree<A> *replace);
	void InOrderHelper(SampleTree<A> *node, std::function<void(A)> fptr);
	void PreOrderHelper(SampleTree<A> *node, std::function<void(A)> fptr);
	void PrintNode(A val);
	~SampleTree();
	/// Private Members
	A val;
	bool active;
	SampleTree<A>* leftchild;
	SampleTree<A>* rightchild;
	SampleTree<A>* root;
};
