#pragma once
#include "Tree.cpp"

template <typename A>
class Tree_Indexer
{
public:
	Tree_Indexer();
	void insert(A);
	void InOrder();
	void PreOrder();
	void PostOrder();
	void LevelOrder();
	~Tree_Indexer();

private:
	Tree<A>* TreeINDEX[26];
};

