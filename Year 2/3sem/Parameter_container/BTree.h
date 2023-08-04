#pragma once

#include <cstdio>
#include <iostream>

template <class T, class C>
class BTree
{
private:
    struct BTreeNode
    {
        T *keys = nullptr;
        C *meanings = nullptr;
        size_t size = 0;
        BTreeNode **child = nullptr;
        BTreeNode *parent;
        size_t bt_node_size;

        BTreeNode(); 
        BTreeNode(size_t n);
        BTreeNode(const BTreeNode &x) = delete;
        ~BTreeNode();

        BTreeNode &operator=(const BTreeNode &x) = delete;

        int BinSearch(const T &x);
        int GoodBinSearch(const T &x);
        void PrintSubtree();                                        
        void InsertAtNode(const T &x, const C &y, BTreeNode *right_child, int ind);
    };

    int bt_node_size = 1;  //порядок дерева (иначе говоря, половина максимальной длины массива в узле)
    BTreeNode *bt_root_node = nullptr;

public:
    BTree();
    BTree(size_t node_size);
    BTree(const BTree &x) = delete;
    BTree &operator=(const BTree &x) = delete;
    ~BTree();

    //порядок дерева
    size_t get_node_size();

    //добавление
    int Add(const T &x, const C &y);

    //поиск значения по ключу
    C *search(const T &x);

    //оператор печати
    void print();

    //теоретико-множественное прибавление
    BTree &operator+=(const BTree &p);

private:

    //служебные функции
    int AddtoSubtree(T &x, C &y, BTreeNode *curr, BTreeNode **right_child);
    void AddSubtree(BTreeNode *curr); 
    void DelSubtree(BTreeNode *curr);
};