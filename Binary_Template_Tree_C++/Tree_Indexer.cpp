#include "Tree_Indexer.h"

template <typename A>
Tree_Indexer<A>::Tree_Indexer()
{
	for (int i = 0; i < 26; i++)
		TreeINDEX[i] = new Tree<A>();
}

template <typename A>
void Tree_Indexer<A>::insert(A key)
{
	switch (key[0])
	{
	case 'a':
		TreeINDEX[0]->Insert(key); break;
	case 'b':
		TreeINDEX[1]->Insert(key); break;
	case 'c':
		TreeINDEX[2]->Insert(key); break;
	case 'd':
		TreeINDEX[3]->Insert(key); break;
	case 'e':
		TreeINDEX[4]->Insert(key); break;
	case 'f':
		TreeINDEX[5]->Insert(key); break;
	case 'g':
		TreeINDEX[6]->Insert(key); break;
	case 'h':
		TreeINDEX[7]->Insert(key); break;
	case 'i':
		TreeINDEX[8]->Insert(key); break;
	case 'j':
		TreeINDEX[9]->Insert(key); break;
	case 'k':
		TreeINDEX[10]->Insert(key); break;
	case 'l':
		TreeINDEX[11]->Insert(key); break;
	case 'm':
		TreeINDEX[12]->Insert(key); break;
	case 'n':
		TreeINDEX[13]->Insert(key); break;
	case 'o':
		TreeINDEX[14]->Insert(key); break;
	case 'p':
		TreeINDEX[15]->Insert(key); break;
	case 'q':
		TreeINDEX[16]->Insert(key); break;
	case 'r':
		TreeINDEX[17]->Insert(key); break;
	case 's':
		TreeINDEX[18]->Insert(key); break;
	case 't':
		TreeINDEX[19]->Insert(key); break;
	case 'u':
		TreeINDEX[20]->Insert(key); break;
	case 'v':
		TreeINDEX[21]->Insert(key); break;
	case 'w':
		TreeINDEX[22]->Insert(key); break;
	case 'x':
		TreeINDEX[23]->Insert(key); break;
	case 'y':
		TreeINDEX[24]->Insert(key); break;
	case 'z':
		TreeINDEX[25]->Insert(key); break;
	default:
		return;
	}
}

template <typename A>
void Tree_Indexer<A>::InOrder()
{
	for (int i = 0; i < 26; i++)
		TreeINDEX[i]->InOrder();
}

template <typename A>
void Tree_Indexer<A>::PreOrder()
{
	for (int i = 0; i < 26; i++)
		TreeINDEX[i]->PreOrder();
}

template <typename A>
void Tree_Indexer<A>::PostOrder()
{
	for (int i = 0; i < 26; i++)
		TreeINDEX[i]->PostOrder();
}

template <typename A>
void Tree_Indexer<A>::LevelOrder()
{
	for (int i = 0; i < 26; i++)
		TreeINDEX[i]->LevelOrder();
}

template <typename A>
Tree_Indexer<A>::~Tree_Indexer()
{
}
