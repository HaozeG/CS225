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
    int degree;                     // number of children
    bool mark;
};

class Heap
{
public:
    Heap();
    ~Heap();
    Node *highest;                  // pointer to the highest priority node

    void insert(Data *data);        // insert new node with given data
    void update(Node &node);        // after the node's data changed
    void delete_node(Node &node);   // delete certain node
    Data *get_highest();            // get the pointer to the data of the highest priority node
    // TODO: 返回的数据类型
    // TODO: print函数+test程序

private:
    int n;                          // record the number of nodes in this heap
    void delete_highest();
    void link_root(Node &node);
    void consolidate();
    void update_degree(Node *node, int d);
    void cascaded_cut(Node *node);
};

bool higher_priority(Node &node1, Node &node2);

#endif
