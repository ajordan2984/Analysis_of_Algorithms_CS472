#include "Tree.h"

template <typename A>
Tree<A>::Tree()
{
	count = 0;
	level = 0;
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
	level = 0;
	/// Set pointers to null default
	leftchild = nullptr;
	rightchild = nullptr;
	root = nullptr;

	/// Set function pointers to correct functions
	/// Type: std::function<void(A)> -> std::function<RETURN TYPE (FUNCTION ARGUMENTS TYPE)> variable_name 
	/// Bind: variable_name = std::bind(CLASS REFERENCE::CLASS FUNCTION, this, PLACE HOLDER FOR FUNCTION ARGUMENTS SEPARATED BY COMMAS);
	/// Example if PrintNode needed 3 arguments: PrintNodePointer = std::bind(&Tree<A>::PrintNode, this, _1,_2,_3);
	PrintNodePointer = std::bind(&Tree<A>::PrintNode, this, _1);
	InsertExtractValuePointer = std::bind(&Tree<A>::InsertExtractValue, this, _1);
	DeleteTreeHelperPointer = std::bind(&Tree<A>::DeleteTreeHelper, this, _1);
	DeleteNodeHelperPointer = std::bind(&Tree<A>::DeleteNodeHelper, this, _1);
	RaiseCountPointer = std::bind(&Tree<A>::RaiseCount, this, _1);
	
	// Copy old tree into new one
	PreOrderHelper(TreeBeingCopied->root, InsertExtractValuePointer);
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
void Tree<A>::LevelOrder()
{
	LevelOrderHelper(root, PrintNodePointer);
}

template <typename A>
Tree<A>* Tree<A>::DFS(A SearchTerm)
{
	if (root == NULL){
		cout << "Error:Root is null." << endl;
		return nullptr;
	}
	else{
		stack<Tree<A> *> TreeStack;
		TreeStack.push(root);

		while (TreeStack.size() != 0)
		{
			Tree<A> *FrontNode = TreeStack.top();
			/// Pop off old node
			TreeStack.pop();

			/// Return Node if found
			if (FrontNode->val == SearchTerm)
				return FrontNode;

			/// Add any leftchildren
			if (FrontNode->leftchild != nullptr)
				TreeStack.push(FrontNode->leftchild);
			if (FrontNode->rightchild != nullptr)
				TreeStack.push(FrontNode->rightchild);
		}// end while
	}// end else
	
	/// Node not found
	return nullptr;
}

template <typename A>
Tree<A>* Tree<A>::BFS(A SearchTerm)
{
	if (root == NULL){
		cout << "Error:Root is null." << endl;
		return nullptr;
	}
	else{
		queue<Tree<A> *> TreeQ;
		TreeQ.push(root);

		while (TreeQ.size() != 0)
		{
			Tree<A> *FrontNode = TreeQ.front();
			
			/// Return Node if found
			if (FrontNode->val == SearchTerm)
				return FrontNode;

			/// Add any leftchildren
			if (FrontNode->leftchild != nullptr)
				TreeQ.push(FrontNode->leftchild);
			if (FrontNode->rightchild != nullptr)
				TreeQ.push(FrontNode->rightchild);
			/// Dequeue node
			TreeQ.pop();
		}// end while
	}// end else

	/// Node not found
	return nullptr;
}

template<typename A>
void Tree<A>::DeleteTree()
{
	PostOrderHelper(root, DeleteTreeHelperPointer);
}

/// Private Helper Functions Defined

template <typename A>
void Tree<A>::AddNode(A key, std::function<void(Tree<A>*&)> UserFunction)
{
	Tree<A>  *current, *trail;
	trail = NULL;
	current = root;
	
	if (root == NULL)
	{
		root = BuildNewNode(key,0);
		return;
	}
	else
	{
		int nodelevel = 0;
		/// Loop until current falls out of the Tree
		/// then place leaf in the Tree using the trail pointer
		while (current != NULL)
		{
			trail = current;
			if (key == current->val)
			{
				UserFunction(current);
				return;
			}
			if (key < current->val)
				current = current->leftchild;
			else
				current = current->rightchild;

			/// Bump node level to record what level the leaf is at
			nodelevel++;
		}/// end while to find where to insert leaf

		/// Create leaf to insert
		Tree<A> *leaf = BuildNewNode(key,nodelevel);
		/// Place leaf into the Tree
		if (key < trail->val)
			trail->leftchild = leaf;
		if (key > trail->val)
			trail->rightchild = leaf;
	}//end else	
}// end AddNode()

template <typename A>
Tree<A>* Tree<A>::BuildNewNode(A val,int nodelevel)
{
	Tree<A> *tp = new Tree<A>;
	tp->val = val;
	tp->count = 1;
	tp->level = nodelevel;
	tp->rightchild = nullptr;
	tp->leftchild = nullptr;
	return tp;
}

template<typename A>
void Tree<A>::DeleteNodeHelper(Tree<A> *&node)
{
		/// Two Children Scenario
	if (node->leftchild != NULL && node->rightchild != NULL)
	{
		FindReplacementNode(node, node->leftchild, 'L');
		return;
	}
		/// No Children Scenario
	if (node->leftchild == NULL && node->rightchild == NULL)
	{
		delete(node);
		node = nullptr;
		return;
	}
		/// Child On Left Or Right Scenario:

		/// Child On Left
	if (node->leftchild != NULL && node->rightchild == NULL)
	{
		FindReplacementNode(node, node->leftchild, 'L');
		return;
	}
		/// Child On Right
	if (node->leftchild == NULL && node->rightchild != NULL)
	{
		FindReplacementNode(node, node->rightchild, 'R');
		return;
	}

}//end DeleteNodeHelper

template<typename A>
void Tree<A>::FindReplacementNode(Tree<A> *&Old, Tree<A> *&Branch, char direction)
{
	Tree<A> *current = Branch;
	Tree<A> *NodeToDelete = nullptr;
	
	switch (direction)
	{
	case 'L':
		while (current->rightchild->rightchild != NULL)
			current = current->rightchild;

		Old->val = current->rightchild->val;
		Old->count = current->rightchild->count;
		
		if (current->rightchild->leftchild != nullptr)
		{
			NodeToDelete = current->rightchild;
			current->rightchild = current->rightchild->leftchild;
			delete (NodeToDelete);
			NodeToDelete = nullptr;
		}
		else
		{
			delete(current->rightchild);
			current->rightchild = nullptr;
		}
		break;
	
	case 'R':
		while (current->leftchild->leftchild != NULL)
			current = current->leftchild;

		Old->val = current->leftchild->val;
		Old->count = current->leftchild->count;
		
		if (current->leftchild->rightchild != nullptr)
		{
			NodeToDelete = current->leftchild;
			current->leftchild = current->leftchild->rightchild;
			delete (NodeToDelete);
			NodeToDelete = nullptr;
		}
		else
		{
			delete(current->leftchild);
			current->leftchild = nullptr;
		}
		break;
	default:
		cout << "An unknown error occured." << endl;
		exit(1);
		break;
	}// end switch
}// end FindReplacementNode()

template<typename A>
void Tree<A>::InOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction)
{
	if (node == NULL)
		return;
	else
	{
		InOrderHelper(node->leftchild, UserFunction);
		UserFunction(node);
		InOrderHelper(node->rightchild, UserFunction);
		return;
	}
}

template<typename A>
void Tree<A>::PreOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction)
{
	if (node == NULL)
		return;
	else
	{
		UserFunction(node);
		PreOrderHelper(node->leftchild, UserFunction);
		PreOrderHelper(node->rightchild, UserFunction);
		return;
	}
}

template<typename A>
void Tree<A>::PostOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction)
{
	if (node == NULL)
		return;
	else
	{
		PostOrderHelper(node->leftchild, UserFunction);
		PostOrderHelper(node->rightchild, UserFunction);
		UserFunction(node);
		return;
	}
}

template<typename A>
void Tree<A>::LevelOrderHelper(Tree<A> *node, std::function<void(Tree<A>*)> UserFunction)
{
	if (node == NULL){
		cout << "Error:Root is null." << endl;
		return;
	}
	else{
		queue<Tree<A> *> TreeQ;
		TreeQ.push(node);

		while (TreeQ.size() != 0)
		{
			Tree<A> *FrontNode = TreeQ.front();
			UserFunction(FrontNode);
			/// Add any leftchildren
			if (FrontNode->leftchild != nullptr)
				TreeQ.push(FrontNode->leftchild);
			if (FrontNode->rightchild != nullptr)
				TreeQ.push(FrontNode->rightchild);
			/// Dequeue node
			TreeQ.pop();
		}// end while
	}// end else	
}// end LevelOrderHelper()

template<typename A>
void Tree<A>::PrintNode(Tree<A> *node)
{
		cout <<"["<< node->val <<"]  [Level:"<<node->level<<"]"<<endl;
}

template<typename A>
void Tree<A>::DeleteTreeHelper(Tree<A> *node)
{
	delete (node);
	node = nullptr;
}

template<typename A>
void Tree<A>::RaiseCount(Tree<A> *&node)
{
	node->count++;
}

template<typename A>
void Tree<A>::InsertExtractValue(Tree<A> *node)
{
	Insert(node->val);
}