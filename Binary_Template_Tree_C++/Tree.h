#pragma once

/// Include for std::function class used with function pointers
#include <functional>
/// Include for queue used with printing tree levels
#include <queue>

// Namespace to put in place holders for variables
// when initializing a std::function object
using namespace std::placeholders;

template <typename A>
class Tree
{
public:
	Tree();
	Tree(Tree<A> *TreeBeingCopied);
	void Insert(A key);
	void DeleteNode(A key);
	void InOrder();
	void PreOrder();
	void PostOrder();
	void LevelOrder();
	void DeleteTree();

private:
	/// Private Helper Functions
	void AddNode(A key, std::function<void(Tree<A>*&)> UserFunction);
	Tree<A>* BuildNewNode(A val,int nodelevel);
	void DeleteNodeHelper(Tree<A> *&node);
	void FindReplacementNode(Tree<A> *&Old, Tree<A> *&Branch, char side);
	void InOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction);
	void PreOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction);
	void PostOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction);
	void LevelOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction);
	void PrintNode(Tree<A> *node);											// Takes a pointer and prints val
	void DeleteTreeHelper(Tree<A> *node);									// Deletes Tree in Post-Order 
	void RaiseCount(Tree<A> *&node);										// Raised the count if val already in Tree
	void InsertExtractValue(Tree<A> *node);									// Gets value from old tree -> new tree
	~Tree();
	/// Private Members
	A val;
	int count;
	int level;
	std::function<void(Tree<A> *)> PrintNodePointer;
	std::function<void(Tree<A> *)> DeleteTreeHelperPointer;
	std::function<void(Tree<A> *)> InsertExtractValuePointer;
	std::function<void(Tree<A> *&)> DeleteNodeHelperPointer;
	std::function<void(Tree<A> *&)> RaiseCountPointer;
	Tree<A>* leftchild;
	Tree<A>* rightchild;
	Tree<A>* root;
};
