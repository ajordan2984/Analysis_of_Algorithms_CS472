#include "SampleTree.h"

template <typename A>
SampleTree<A>::SampleTree()
{
	leftchild = nullptr;
	rightchild = nullptr;
	root = nullptr;
}

// Overloaded Copy Constructor
template <typename A>
SampleTree<A>::SampleTree(SampleTree<A> *TreeBeingCopied)
{
	using namespace std::placeholders;
	std::function<void(A)> InsertTreePointer = std::bind(&SampleTree<A>::InsertTree, this, _1);
	PreOrderHelper(TreeBeingCopied->root, InsertTreePointer);
}

template <typename A>
SampleTree<A>::~SampleTree()
{}

template <typename A>
void SampleTree<A>::InsertTree(A key)
{
	SampleTree<A>  *current, *trail;
	trail = NULL;
	current = root;
	// Create leaf to insert
	SampleTree<A> *leaf = MyNewNode(key);

	if (root == NULL)
	{
		root = leaf;
		return;
	}
	else
	{
		// Loop until current falls out of the SampleTree
		// then place leaf in the SampleTree using the trail pointer
		while (current != NULL)
		{
			trail = current;
			if (leaf->val == current->val)
			{
				return;
			}
			if (leaf->val < current->val)
				current = current->leftchild;
			else
				current = current->rightchild;
		}// end while to find where to insert leaf

		// Place leaf into the SampleTree
		if (leaf->val < trail->val)
			trail->leftchild = leaf;
		if (leaf->val > trail->val)
			trail->rightchild = leaf;
	}//end else	
}// end insert()

template <typename A>
SampleTree<A>* SampleTree<A>::MyNewNode(A val)
{
	SampleTree<A> *tp = new SampleTree<A>;
	tp->active = true;
	tp->val = val;
	tp->rightchild = nullptr;
	tp->leftchild = nullptr;
	return tp;
}

template <typename A>
void SampleTree<A>::DeleteNode(A key)
{
	DeleteNodeHelper(root, root, 2, key);
}

template<typename A>
void SampleTree<A>::InOrder()
{
	using namespace std::placeholders;
	std::function<void(A)> PrintNodePointer = std::bind(&SampleTree<A>::PrintNode, this, _1);
	//std::function<void(SampleTree<A>*)> PrintNodePointer = &SampleTree<A>::PrintNode;
	InOrderHelper(root, PrintNodePointer);
}

template<typename A>
void SampleTree<A>::PreOrder()
{
	std::function<void(SampleTree<A>*)> PrintNodePointer = &SampleTree<A>::PrintNode;
	PreOrderHelper(root, PrintNodePointer);
}

// Private Helper Functions Defined

template<typename A>
void SampleTree<A>::DeleteNodeHelper(SampleTree<A> *current, SampleTree<A> *trail, int branch, A key)
{
	if (current->val == key || current->active = false)
	{
		// 2 children
		if (current->leftchild != NULL && current->rightchild != NULL)
			case2children(current->rightchild, current);

		else
		{
			// No children 
			if (current->leftchild == NULL && current->rightchild == NULL)
			{
				if (branch == 1)
					trail->leftchild = NULL;
				if (branch == 0)
					trail->rightchild = NULL;
			}

			// Child on left or right
			else
			{
				if (current->leftchild == NULL)
					place_node(current, trail, branch, 0);
				if (current->rightchild == NULL)
					place_node(current, trail, branch, 1);
				// Restart
				DeleteNodeHelper(root, root, 2, key);
				return;
			}
		}
	}// end if count < 5
	trail = current;
	DeleteNodeHelper(current->leftchild, trail, 1, key);
	DeleteNodeHelper(current->rightchild, trail, 0, key);

}//end DeleteNodeHelper

template<typename A>
void SampleTree<A>::place_node(SampleTree<A> *current, SampleTree<A> *trail, int branch, int side)
{
	// Right - 0
	// Left - 1
	if (branch == 0 && side == 0)
		trail->rightchild = current->rightchild;

	if (branch == 0 && side == 1)
		trail->rightchild = current->leftchild;

	if (branch == 1 && side == 0)
		trail->leftchild = current->rightchild;

	if (branch == 1 && side == 1)
		trail->leftchild = current->leftchild;

}//end place_node()

template<typename A>
void SampleTree<A>::case2children(SampleTree<A>  *branch, SampleTree<A> *replace)
{
	SampleTree<A> *trail = NULL;
	SampleTree<A> *trail2;
	while (branch != nullptr)
	{
		trail = branch;
		branch = branch->leftchild;
	}
	replace->val = trail->val;
	trail->active = false;
}

template<typename A>
void SampleTree<A>::InOrderHelper(SampleTree<A> *node, std::function<void(A)> fptr)
{
	if (node == NULL)
		return;
	else
	{
		InOrderHelper(node->leftchild,fptr);
		fptr(node->val);
		InOrderHelper(node->rightchild,fptr);
		return;
	}
}

template<typename A>
void SampleTree<A>::PreOrderHelper(SampleTree<A> *node, std::function<void(A)> fptr)
{
	if (node == NULL)
		return;
	else
	{
		fptr(node->val);
		PreOrderHelper(node->leftchild, fptr);
		PreOrderHelper(node->rightchild, fptr);
		return;
	}
}

template<typename A>
void SampleTree<A>::PrintNode(A val)
{
	cout << val << endl;
}