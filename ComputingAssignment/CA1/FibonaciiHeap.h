#include "data.h"

template<class T> class Node
{
public:
    Node();
    // define four pointers for each node
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int degree;
    bool mark;
};

template<class T> class Heap : public Node
{
public:
    Heap();
    Node *min;  // pointer to the smallest node
    int n;  // record the number of nodes in this heap

    void insert(Node<T> &node);
    void decrease(Node<T> &node, Data<T> &new_data);   // used to update information
    void delete_node(Node<T> &node);
    void delete_min();
    void merge();   // rebalance
};

// initialize Node and Heap
template<class T> Node<T>::Node()
{
    parent = NULL;
    child = NULL;
    left = NULL;
    right = NULL;
    degree = 0;
    mark = false;
};

template<class T> Heap<T>::Heap()
{
    min = NULL;
    n = 0;
}
