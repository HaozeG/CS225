#ifndef fibonacii_heap_h
#define fibonacii_heap_h

#include "data.h"

class Node
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

class Heap : public Node
{
public:
    Heap();
    Node *min;  // pointer to the smallest node
    int n;  // record the number of nodes in this heap

    bool is_smaller(Node &node1, Node &node2);
    void insert(Node &node);
    void decrease(Node &node, Data &new_data);   // used to update information
    void delete_node(Node &node);
    void delete_min();
    void merge();   // rebalance
};

#endif
