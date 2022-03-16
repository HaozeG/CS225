#include <stdio.h>
#include <iostream>
#include <math.h>
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
    highest = NULL;
    n = 0;
}

void Heap::link_root(Node &node)
{
    // link to root list
    Node *m = (*(Heap::highest)).right;
    (*(Heap::highest)).right = &node;
    node.left = Heap::highest;
    node.right = m;
    (*m).left = &node;

    // adjust H.highest
    if (higher_priority(node, *(Heap::highest)))
        Heap::highest = &node;
}

// insert new node into root
void Heap::insert(Node &node)
{
    link_root(node);
    Heap::n++;
};

// used to update information
void Heap::update(Node &node, Data &new_data)
{
    Node *temp = new Node;
    temp->data = &new_data;
    // judge if the priority increases or decreases
    bool flag = higher_priority(node, *temp);
    if (flag)
    {
        decrease(node, new_data);
    }
    else
    {
        increase(node, new_data);
    }
}

void Heap::increase(Node &node, Data &new_data)
{
    // increase the data of the node
    node.data = &new_data;

    // update degree value of parent nodes
    // mark parent node
    // iterate through all parent nodes to check if they are marked
    cascaded_cut(node);
    update_degree(node.parent, node.degree);

    // cut off subtree
    // insert to root
    node.parent = NULL;
    link_root(node);
}

void Heap::decrease(Node &node, Data &new_data)
{
    // decrease the data of the node
    node.data = &new_data;

    // update degree value of parent nodes
    // mark parent node
    // iterate through all parent nodes to check if they are marked
    cascaded_cut(node);
    update_degree(node.parent, node.degree);

    // update the link of parent node
    if (&node == (node.parent)->child)
        (node.parent)->child = node.left;
    // cut off subtree
    // insert to root
    node.parent = NULL;
    link_root(node);

};

void Heap::delete_highest()
{
    // check if the heap is empty
    if (0 == Heap::n)
    {
        cout << "Already empty!\n";
        return;
    }
    Heap::n--;
    // connect child nodes to root list

    // rebalance
    consolidate();
};

void Heap::delete_node(Node &node)
{
    // set the value of new_data to negative
    Data *new_data = new Data;
    Data *origin_data = node.data;

    // call decrease and delete_min
    decrease(node, *new_data);
    delete_highest();
    // TODO: 是否需要修改原来的数据
    // // keep the data unchanged
    // node.data = origin_data;
};

void Heap::consolidate()
{
    Node *m[int(log2(n))];
    // iterate through root list

    // merge two trees if needed

    // update H.highest

};

bool higher_priority(Node &node1, Node &node2)
{
    // profession category, ranking of age group, time

}

void Heap::update_degree(Node *node, int d)
{
    while (NULL != (*node).parent)
    {
        (*node).degree -= d;
        node = (*node).parent;
    }
}

        // //TODO:if逻辑
        // if ((false == (*node).mark) && (false == flag))
        // {
        //     (*node).mark = true;
        //     flag = false;
        // }
        // else
        // {
        //     // cut off node

        // }
