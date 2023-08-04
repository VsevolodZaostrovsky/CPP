#pragma once
#include <iostream>
#include "BTree.h"

template <class T, class C>
BTree<T, C>::BTreeNode::BTreeNode() {
	keys = new T[2];
	meanings = new C[2];
	child = new BTreeNode * [3];
	for(int i = 0; i < 3; i++){ child[i] = nullptr; }
	size = 0;
}

template <class T, class C>
BTree<T, C>::BTreeNode::BTreeNode(size_t n) {
	keys = new T[2 * n];
	meanings = new C[2 * n];
	child = new BTreeNode * [2 * n + 1];
	for(int i = 0; i < 2 * n + 1; i++){ child[i] = nullptr; }
	size = 0;
}

template <class T, class C>
BTree<T, C>::BTreeNode::~BTreeNode() {
    delete [] keys;
    delete [] meanings;
 
	for(int i = 0; i < size + 1; i++) { child[i] = nullptr; }
	delete [] child;
	size = 0;
}

template <class T, class C>
void BTree<T, C>::BTreeNode::PrintSubtree()
    {
//	std::cout << "Node: " << std::endl;
//	std::cout << "Size: " << size  << std::endl;
    for(int k = 0; k < size; ++k) {
        std::cout << keys[k] << "=" << meanings[k] << std::endl;
    }
    if(child[0]){
        for(int k = 0; k < size + 1; ++k) {
            child[k]->PrintSubtree();
        }
    }
    }

template <class T, class C>
void BTree<T, C>::BTreeNode::InsertAtNode(const T &x, const C &y, BTreeNode* right_child, int ind)
    {
		if(size == 0)
		{
			size ++;
			keys[0] = x;
			meanings[0] = y;
			child[1] = right_child;
			return;
		}
		int i = 0;
		for(i = size; i > ind; i--)
		{
			keys[i] =keys[i-1];
			meanings[i] =meanings[i-1];
			child[i+1] = child[i];
		}
		keys[ind] = x;
		meanings[ind] = y;
		child[ind + 1] = right_child;
		size++;
	}

template <class T, class C>
BTree<T, C>::BTree() 
: bt_root_node(nullptr), bt_node_size(1) {}

template <class T, class C>
BTree<T, C>::BTree(size_t node_size) 
: bt_root_node(nullptr), bt_node_size(node_size) {}

template <class T, class C>
void BTree<T, C>::DelSubtree(BTree<T, C>::BTreeNode *curr)
{
	if (!curr)
		return;
	for (int i = 0; i <= curr->size; i++)
	{
		DelSubtree(curr->child[i]);
	}
	delete curr;
}

template <class T, class C>
BTree<T, C>::~BTree() { DelSubtree(bt_root_node); }

template <class T, class C>
size_t BTree<T, C>::get_node_size() { return bt_node_size; }

template <class T, class C>
int BTree<T, C>::BTreeNode::BinSearch(const T &x) {
    int r = size - 1;
	int l = 0;
	int m = 0;
    if(keys[0] > x) return 0;
		
    if(x > keys[size - 1]) return size;

    while(r > l) {
		m = (r + l) / 2;
		if(x > keys[m]) { l = m + 1; }
        else { r = m; }
		}
    if (x == keys[m]) {
        return -1;
    }
	return r;
} 

template <class T, class C>
void BTree<T, C>::print() { bt_root_node->PrintSubtree(); }

template <class T, class C>
int BTree<T, C>::AddtoSubtree(T &x, C &y, BTree<T, C>::BTreeNode *curr, BTree<T, C>::BTreeNode **right_child) 
{
		int ind = curr->BinSearch(x);
		if (ind == -1) { return 0; }
		BTreeNode* place = curr->child[ind];
		if(place != nullptr)
		{
			int result = AddtoSubtree(x, y, place, right_child);
			if(result != 2) return result;
		}else
		{
			*right_child = nullptr;
		}

		if(curr->size < 2 * bt_node_size)
		{
			curr->InsertAtNode(x, y, *right_child, ind);
			return 1;
		}

		BTreeNode *p = new BTreeNode(bt_node_size);
		if(ind == bt_node_size)
		{
			curr->size = bt_node_size;
			p->size = bt_node_size;
			for(int k = 0; k < bt_node_size; ++k)
			{
				p->keys[k] = curr->keys[bt_node_size + k];
				p->meanings[k] = curr->meanings[bt_node_size + k];
				p->child[k + 1] = curr->child[bt_node_size + k + 1];
				curr->child[bt_node_size + k + 1] = nullptr;
			}
			p->child[0] = *right_child;
			*right_child = p;
			return 2;
		}


		if(ind < bt_node_size)
		{
			T tmp; C tmp2;
			BTreeNode* vsp = *right_child;

			tmp = curr->keys[bt_node_size - 1];
			tmp2 = curr->meanings[bt_node_size - 1];
			*right_child = p;
			for(int k = 0; k < bt_node_size; ++k)
			{
				p->keys[k] = curr->keys[bt_node_size + k];
				p->meanings[k] = curr->meanings[bt_node_size + k];
				p->child[k + 1] = curr->child[bt_node_size + k + 1];
				curr->child[bt_node_size + k + 1] = nullptr;
			}
			p->child[0] = curr->child[bt_node_size];
			curr->child[bt_node_size] = nullptr;
			curr->size = bt_node_size - 1;
			p->size = bt_node_size;
			curr->InsertAtNode(x, y, vsp, ind);
			x = tmp; y = tmp2;
			return 2;
		}
		T tmp; C tmp2;
		BTreeNode* vsp = *right_child;
		*right_child = p;
		tmp = curr->keys[bt_node_size];
		tmp2 = curr->meanings[bt_node_size];

		curr->size = bt_node_size;
		p->size = bt_node_size - 1;

		for(int k = 0; k < bt_node_size - 1; k++)
		{
			p->keys[k] = curr->keys[bt_node_size + k + 1];
			p->meanings[k] = curr->meanings[bt_node_size + k + 1];
			p->child[k + 1] = curr->child[bt_node_size + k + 2];
			curr->child[bt_node_size + k + 2] = nullptr;
		}
		p->child[0] = curr->child[bt_node_size + 1];
		curr->child[bt_node_size + 1] = nullptr;

		p->InsertAtNode(x, y, vsp, ind - bt_node_size - 1);
		x = tmp; y = tmp2;
		return 2;
	}

template <class T, class C>
int BTree<T, C>::Add(const T &X, const C &Y)
{
		if(bt_root_node == nullptr)
		{
			bt_root_node = new BTreeNode(bt_node_size);
			bt_root_node->size = 1;
			bt_root_node->keys[0] = X;
			bt_root_node->meanings[0] = Y;
			return 1;
		}

		BTreeNode* curr = bt_root_node, *right_child = nullptr;
		int result;
		T x = X; C y = Y;
		result = AddtoSubtree(x, y, curr, &right_child);
		if(result != 2) return result;
		BTreeNode *p = new BTreeNode(bt_node_size);

		p->keys[0] =x;
		p->meanings[0] =y;
		p->size = 1;
		curr->size = bt_node_size;
		p->child[0] = curr;
		p->child[1] = right_child;
		bt_root_node = p;
		return 1;
}

template <class T, class C>
void BTree<T, C>::AddSubtree(BTree<T, C>::BTreeNode *curr)
    {
    for(int k = 0; k < curr->size; ++k) {
        Add(curr->keys[k], curr->meanings[k]);
    }
    if(curr->child[0]){
        for(int k = 0; k < curr->size + 1; ++k) {
            AddSubtree(curr->child[k]);
        }
    }
    }

template <class T, class C>
BTree<T, C> &BTree<T, C>::operator+=(const BTree<T, C> &p) {
	AddSubtree(p.bt_root_node);
	return *this;
}

template <class T, class C>
int BTree<T, C>::BTreeNode::GoodBinSearch(const T &x) {
    int r = size - 1; int l = 0; int m = 0;
    if(keys[0] > x) return 0;
		
    if(x > keys[size - 1]) return size;

    while(r > l) {
		m = (r + l) / 2;
		if(x > keys[m]) { l = m + 1; }
        else { r = m; }
    	if (x == keys[m]) {
        	return m;
    	}
	}
	return r;
}

template <class T, class C>
C *BTree<T, C>::search(const T &x) {
    int index;
    BTreeNode *curr = bt_root_node;
    while (true) 
    {
        index = curr->GoodBinSearch(x);
        if((index < curr->size) && (x == curr->keys[index])) { 
			return &(curr->meanings[index]);
		}
        if(!curr->child[index]) return nullptr; 
        curr = curr->child[index];
    }
    return nullptr; 
}
