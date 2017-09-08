#include "Tree.h"

template <typename A>
Tree<A>::Tree()
{
	count = 0;
	/// Set pointers to null default
	leftchild = nullptr;
	rightchild = nullptr;
	root = nullptr;
	/// Set printer function pointer
	PrintNodePointer = std::bind(&Tree<A>::PrintNode, this, _1);
	DeleteTreeHelperPointer = std::bind(&Tree<A>::DeleteTreeHelper, this, _1);
	DeleteNodeHelperPointer = std::bind(&Tree<A>::DeleteNodeHelper, this, _1);
	RaiseCountPointer = std::bind(&Tree<A>::RaiseCount, this, _1);
}

/// Overloaded Copy Constructor
template <typename A>
Tree<A>::Tree(Tree<A> *TreeBeingCopied)
{
	count = 0;
	/// Set pointers to null default
	leftchild = nullptr;
	rightchild = nullptr;
	root = nullptr;

	/// Set function pointers to correct functions
	/// Type: std::function<void(A)> -> std::function<RETURN TYPE (FUNCTION ARGUMENTS TYPE)> variable_name 
	/// Bind: variable_name = std::bind(CLASS REFERENCE::CLASS FUNCTION, this, PLACE HOLDER FOR FUNCTION ARGUMENTS SEPARATED BY COMMAS);
	/// Example if PrintNode needed 3 arguments: PrintNodePointer = std::bind(&Tree<A>::PrintNode, this, _1,_2,_3);
	PrintNodePointer = std::bind(&Tree<A>::PrintNode, this, _1);
	InsertTreePointer = std::bind(&Tree<A>::Insert, this, _1);
	DeleteTreeHelperPointer = std::bind(&Tree<A>::DeleteTreeHelper, this, _1);
	DeleteNodeHelperPointer = std::bind(&Tree<A>::DeleteNodeHelper, this, _1);
	RaiseCountPointer = std::bind(&Tree<A>::RaiseCount, this, _1);
	
	// Copy old tree into new one
	PreOrderHelper(TreeBeingCopied->root, InsertTreeHelperPointer);	
}

template <typename A>
Tree<A>::~Tree()
{}

template <typename A>
void Tree<A>::Insert(A key)
{
	AddNode(key, RaiseCountPointer);
}

template <typename A>
void Tree<A>::DeleteNode(A key)
{
	AddNode(key, DeleteNodeHelperPointer);
}

template<typename A>
void Tree<A>::InOrder()
{
	InOrderHelper(root, PrintNodePointer);
}

template<typename A>
void Tree<A>::PreOrder()
{
	PreOrderHelper(root, PrintNodePointer);
}

template<typename A>
void Tree<A>::PostOrder()
{
	PostOrderHelper(root, PrintNodePointer);
}

template<typename A>
void Tree<A>::DeleteTree()
{
	PostOrderHelper(root, DeleteTreeHelperPointer);
}

/// Private Helper Functions Defined

template <typename A>
void Tree<A>::AddNode(A key, std::function<void(Tree<A>*)> fptr)
{
	Tree<A>  *current, *trail;
	trail = NULL;
	current = root;
	// Create leaf to insert
	Tree<A> *leaf = MyNewNode(key);

	if (root == NULL)
	{
		root = leaf;
		return;
	}
	else
	{
		// Loop until current falls out of the Tree
		// then place leaf in the Tree using the trail pointer
		while (current != NULL)
		{
			trail = current;
			if (leaf->val == current->val)
			{
				fptr(current);
				delete(leaf);
				return;
			}
			if (leaf->val < current->val)
				current = current->leftchild;
			else
				current = current->rightchild;
		}// end while to find where to insert leaf

		// Place leaf into the Tree
		if (leaf->val < trail->val)
			trail->leftchild = leaf;
		if (leaf->val > trail->val)
			trail->rightchild = leaf;
	}//end else	
}// end AddNode()

template <typename A>
Tree<A>* Tree<A>::MyNewNode(A val)
{
	Tree<A> *tp = new Tree<A>;
	tp->val = val;
	tp->count = 1;
	tp->rightchild = nullptr;
	tp->leftchild = nullptr;
	return tp;
}

template<typename A>
void Tree<A>::DeleteNodeHelper(Tree<A> *node)
{
		/// Two Children Scenario
		if (node->leftchild != NULL && node->rightchild != NULL)
			FindReplacementNode(node, node->leftchild, 'L');

		/// No Children Scenario
		if (node->leftchild == NULL && node->rightchild == NULL)
			delete(node);

		/// Child On Left Or Right Scenario:

		/// Child On Left
		if (node->leftchild != NULL && node->rightchild == NULL)
			FindReplacementNode(node, node->leftchild, 'L');

		/// Child On Right
		if (node->leftchild == NULL && node->rightchild != NULL)
			FindReplacementNode(node, node->rightchild, 'R');

}//end DeleteNodeHelper

template<typename A>
void Tree<A>::FindReplacementNode(Tree<A> *Old, Tree<A> *Branch, char direction)
{
	Tree<A> *current = Branch;
	Tree<A> *trail = nullptr;
	Tree<A> *NodeToDelete = nullptr;
	
	switch (direction)
	{
	case 'L':
		while (current != NULL)
		{
			trail = current;
			current = current->rightchild;
		}
		Old->val = trail->val;
		Old->count = trail->count;
		
		if (trail->leftchild != nullptr)
		{
			NodeToDelete = trail;
			trail = trail->leftchild;
			delete (NodeToDelete);
			NodeToDelete = nullptr;
		}
		else
			DeleteTreeHelper(trail);
		break;
	case 'R':
		while (current != NULL)
		{
			trail = current;
			current = current->leftchild;
		}
		Old->val = trail->val;
		Old->count = trail->count;
		if (trail->rightchild != nullptr)
		{
			NodeToDelete = trail;
			trail = trail->rightchild;
			delete (NodeToDelete);
			NodeToDelete = nullptr;
		}
		else
			DeleteTreeHelper(trail);
		break;
	default:
		cout << "An unknown error occured." << endl;
		exit(1);

	}// end switch
}// end FindReplacementNode()

template<typename A>
void Tree<A>::InOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> fptr)
{
	if (node == NULL)
		return;
	else
	{
		InOrderHelper(node->leftchild, fptr);
		fptr(node);
		InOrderHelper(node->rightchild, fptr);
		return;
	}
}

template<typename A>
void Tree<A>::PreOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> fptr)
{
	if (node == NULL)
		return;
	else
	{
		fptr(node);
		PreOrderHelper(node->leftchild, fptr);
		PreOrderHelper(node->rightchild, fptr);
		return;
	}
}

template<typename A>
void Tree<A>::PostOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> fptr)
{
	if (node == NULL)
		return;
	else
	{
		PostOrderHelper(node->leftchild, fptr);
		PostOrderHelper(node->rightchild, fptr);
		fptr(node);
		return;
	}
}

template<typename A>
void Tree<A>::PrintNode(Tree<A> *node)
{
	if (node->count >= 10)
	cout << node->val << endl;
}

template<typename A>
void Tree<A>::DeleteTreeHelper(Tree<A> *node)
{
	delete (node);
	node = nullptr;
}

template<typename A>
void Tree<A>::RaiseCount(Tree<A> *node)
{
	node->count++;
}