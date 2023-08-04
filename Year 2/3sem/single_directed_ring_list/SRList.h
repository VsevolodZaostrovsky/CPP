#pragma once

template <class T>
class SRList
{
private:
    struct SRListNode //структура в которой хранится информация об узлах списка
    {
        T _value;           //объект класса Т хранящийся в узле
        SRListNode *_next;  //ссылка не следующий узел
        SRListNode() { _next = 0; }
        SRListNode(const T value) { _next = 0; _value = value; }
    };

    SRListNode *_CurrentNode; //текущая позиция
    SRListNode *_first;       //ссылка на первый узел списка
    int _size;                //размер списка

public:
    SRList() { _CurrentNode = _first = 0; _size = 0;};
    SRList(const SRList &p);
    ~SRList();

    void pushAfterFirst(const T &x); //вставить элемент в список (после первого)
    void insAfter(const T &x);       //вставить элемент после текцщей позиции

    void delAfter(); //удалить следующий узел

    void toNext(); //передвинуться на следующий узел
    void toFirst(); //передвинуться в начало списка

    int size();            //вернуть размер списка
    T &node();             //изменение значения в узле
    const T &node() const; //доступ к значению в узле

    void sort(); // сортировка (для корректной работы на сложных классах необходима перегрузка оператора <)

    SRList &operator=(const SRList &p);

    SRList &operator+=(const SRList &p); //(дизъюнктное) присоедиенение к списку списка p

    template <class P>
    friend std::ostream & operator<<(std::ostream & os, const SRList<P> & list); //оператор печати

    void print(); //альтернативный оператор печати 
    //для корректной работы каждого из операторов печати необходима перегрузка оператора <<

public:
    class Iterator
    {
    private:
        friend class SRList;
        SRListNode *_currentNode; //ссылка на узел списка который описывается итератором
        Iterator();

    public:
        Iterator(SRListNode *pos)
         : _currentNode(pos) {}

        Iterator(const Iterator &I) { _currentNode = I._currentNode; }   

        //перевод оператора на следующий узел списка
        void operator++() { _currentNode = _currentNode->_next; } 
         
        Iterator &operator=(const Iterator &I) { this->_currentNode = I->_currentNode; }

        T &operator*() const { return _currentNode->_value; }    //возвращение объекта узла

        bool operator!=(const Iterator &I) const {
            if (_currentNode == I._currentNode) { return 1; }
            return 0;
        }

        bool operator==(const Iterator &I) const {
            if (_currentNode != I._currentNode) { return 1; }
            return 0;
        }
    };

    private:
        SRListNode *find_max_N_steps(SRListNode *StartNode, int N);
};