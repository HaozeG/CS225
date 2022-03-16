#ifndef fibonacii_heap_h
#define fibonacii_heap_h

#include "data.h"

class Node
{
public:
    Node();

    Data* data;
    // define four pointers for each node
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int degree; // number of children
    bool mark;
};

class Heap : public Node
{
public:
    Heap();
    Node *highest;  // pointer to the highest priority node
    int n;  // record the number of nodes in this heap

    void insert(Node &node);
    void link_root(Node &node);
    void update(Node &node, Data &new_data); // used to update information
    void increase(Node &node, Data &new_data);
    void decrease(Node &node, Data &new_data);
    void delete_node(Node &node);
    void delete_highest();
    void consolidate();
    void update_degree(Node *node, int d);
    void cascaded_cut(Node &node);
};

bool higher_priority(Node &node1, Node &node2);

#endif
