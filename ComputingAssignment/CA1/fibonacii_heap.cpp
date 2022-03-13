#include <stdio.h>
#include <iostream>
#include "fibonacii_heap.h"
using std::cout;
using std::cin;

// initialize Node and Heap
Node::Node()
{
    parent = NULL;
    child = NULL;
    left = NULL;
    right = NULL;
    degree = 0;
    mark = false;
};

Heap::Heap()
{
    min = NULL;
    n = 0;
}

// insert new node into root
void Heap::insert(Node &node)
{
    // insert to root
    Node *m = (*(Heap::min)).right;
    (*(Heap::min)).right = &node;
    node.left = Heap::min;
    node.right = m;
    (*m).left = &node;

    // adjust H.min
    //TODO: 优先级判断函数
    if (is_smaller(node, *(Heap::min)))
        Heap::min = &node;
};

// used to update information
void Heap::decrease(Node &node, Data &new_data)
{

};

void Heap::delete_node(Node &node)
{

};

void Heap::delete_min()
{
};

void Heap::merge()
{

};

bool Heap::is_smaller(Node &node1, Node &node2)
{
}
