#include <iostream>
#include "SRList.h"
#include "MyExceptionSDRL.h"

template <class T>
SRList<T>::~SRList()
{
    while (_size)
    {
        SRListNode *p = _first->_next;
        delete _first;
        _first = p;
        _size -= 1;
    }
}

template <class T>
void SRList<T>::pushAfterFirst(const T &x)
{
    try
    {
        SRListNode *p = new SRListNode;
        p->_value = x;

        if (_first == 0)
        {
            _first = p;
            _CurrentNode = p;
            _first->_next = p;
            ++_size;
            return;
        }

        p->_next = _first->_next;
        _first->_next = p;
        ++_size;
        return;
    }
    catch (std::bad_alloc)
    {
        throw new MyExceptionSDRL("SRList<T>::PushAfterFirst: memory allocation error\n", EC_MEMORY);
    }
}

template <class T>
void SRList<T>::insAfter(const T &x)
{
    try
    {
        SRListNode *p = new SRListNode;
        p->_value = x;

        if (_CurrentNode == 0)
        {
            _first = p;
            _CurrentNode = p;
            _first->_next = p;
            ++_size;
            return;
        }

        p->_next = _CurrentNode->_next;
        _CurrentNode->_next = p;
        ++_size;
        return;
    }
    catch (std::bad_alloc)
    {
        throw new MyExceptionSDRL("DList<T>::InsAfter: memory allocation error\n", EC_MEMORY);
    }
}

template <class T>
void SRList<T>::toNext() { _CurrentNode = _CurrentNode->_next; }

template <class T>
void SRList<T>::toFirst() { _CurrentNode = _first; }

template <class T>
void SRList<T>::delAfter() 
{

    SRListNode *next = _CurrentNode->_next;
    SRListNode *nextnext = next->_next;
    if (next == _first) {
        _first = _CurrentNode;
    }
    delete next;
    _CurrentNode->_next = nextnext;
    _size -= 1;
}

template <class T>
int SRList<T>::size() { return _size; }

template <class T>
T &SRList<T>::node() { return _CurrentNode->_value; }

template <class T>
const T &SRList<T>::node() const { return _CurrentNode->_value; }

template <class T>
void SRList<T>::print()
{
    try
    {
        SRListNode *p;
        p = _first;
        int temp = _size;
        if (_first == 0) {
            std::cout << "empty" << std::endl;
        }
        while (temp)
        {
            std::cout << p->_value << " ";
            p = p->_next;
            --temp;
        }
        std::cout << std::endl;
    }
    catch (std::bad_alloc)
    {
        throw new MyExceptionSDRL("SRList<T>::PushAfterFirst: memory allocation error\n", EC_MEMORY);
    }
}

template <class T>
SRList<T> &SRList<T>::operator=(const SRList<T> &p)
{
    if (this == &p)
    {
        return *this;
    }

    while (_size)
    {
        SRListNode *p = _first->_next;
        delete _first;
        _first = p;
        _size -= 1;
    }

    Iterator P(p._first);
    for (int k = 0; k < p._size; ++k) {
        this->insAfter(*P);
        this->toNext(); ++P;
    }
    return *this;
}

template<class T>
SRList<T>::SRList(const SRList &p) {
    Iterator P(p._first);
    for (int k = 0; k < p._size; ++k) 
    {
        this->insAfter(*P);
        this->toNext(); ++P;
    }
}

template<class T>
typename SRList<T>::SRListNode *SRList<T>::find_max_N_steps(SRList<T>::SRListNode *StartNode, int N) {
    T max = StartNode->_value;
    SRListNode *MaxNode = StartNode;
    for (int k = 0; k < N; ++k) {
        if (StartNode->_value > max) {
            max = StartNode->_value;
            MaxNode = StartNode;
        }
        StartNode = StartNode->_next;
    }
    return MaxNode;
}

template<class T>
void SRList<T>::sort() {
    SRListNode *nowNode = _first;
    SRListNode *nowMaxNode = _first;
    T per;
    for (int k = 0; k < _size; ++k) {
        nowMaxNode = this->find_max_N_steps(nowNode, _size - k);
        per = nowNode->_value;
        nowNode->_value = nowMaxNode->_value;
        nowMaxNode->_value = per;
        nowNode = nowNode->_next;
    }
}

template <class T>
SRList<T> &SRList<T>::operator+=(const SRList<T> &p) {
    Iterator P(p._first);
    for (int k = 0; k < p._size; ++k) {
        this->insAfter(*P);
        this->toNext(); ++P;
    }
    return *this;

}

template <class T>
std::ostream &operator<<(std::ostream &os, const SRList<T> &list)
{
    try
    {
        typename SRList<T>::SRListNode *p;
        p = list._first;
        int temp = list._size;
        std::cout << "[" << temp << "] ";

        while (temp)
        {
            std::cout << p->_value << " ";
            p = p->_next;
            --temp;
        }
        std::cout << std::endl;
        return os;
    }
    catch (std::bad_alloc)
    {
        throw new MyExceptionSDRL("SRList<T>::PushAfterFirst: memory allocation error\n", EC_MEMORY);
    }
}

