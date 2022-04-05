#ifndef fibonacii_heap_h
#define fibonacii_heap_h

#include "data.h"

class Node
{
public:
    Node();
    ~Node();
    Data* data;
    // define four pointers for each node
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    int node_num;                     // number of nodes in subtree
    bool mark;
    bool Written;
};

class Heap
{
public:
    Heap();
    ~Heap();
    Node *highest;                  // pointer to the highest priority node
    int n;                          // record the number of nodes in this heap

    void insert(Data *data);        // insert new node with given data
    void update(Node &node);        // after the node's data changed
    void delete_node(Node &node);   // delete certain node
    Data *get_highest();            // get the pointer to the data of the highest priority node
    bool higher_priority(Node &node1, Node &node2);

private:
    void delete_highest();
    void link_root(Node &node);
    void consolidate();
    void update_degree(Node *node, int d);
    void cascaded_cut(Node *node);
};

bool higher_priority(Node &node1, Node &node2);

#endif
