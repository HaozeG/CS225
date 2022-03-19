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
    node.parent = NULL;

    // adjust H.highest
    if (higher_priority(node, *(Heap::highest)))
        Heap::highest = &node;
}

/*
    insert new node into root
    input:
        node: the node needs to insert
    output: none
*/
void Heap::insert(Node &node)
{
    link_root(node);
    Heap::n++;
};

/*
    changes to the heap if one node has changed
    input:
        node: the node that has been changed
    output: none
*/
void Heap::update(Node &node)
{
    Node *parent_node = node.parent;

    // cut off subtree and insert to root list
    update_degree(node.parent, -node.degree);
    link_root(node);
    // connect child nodes to root list
    Node *child_node = node.child;
    Node *right_child_node = child_node->right;
    Node *left_root_node = Heap::highest;
    Node *right_root_node = Heap::highest->right;
    child_node->right = right_root_node;
    right_root_node->left = child_node;
    right_child_node->left = left_root_node;
    left_root_node->right = right_child_node;
    node.degree = 1;
    // update H.highest
    child_node = left_root_node->left;
    while (child_node != left_root_node)
    {
        child_node->parent = NULL;    // make sure all nodes in root list have parent == NULL
        if (higher_priority(*child_node, *(Heap::highest)))
            Heap::highest = child_node;
        child_node = child_node->left;
    }

    // cascaded cut parent nodes
    cascaded_cut(*parent_node);
}

// to get the data of the highest node, just H.highest->data
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
    Node *node = Heap::highest->child;
    Node *right_node = node->right;
    Node *left_root_node = Heap::highest;
    Node *right_root_node = Heap::highest->right;
    node->right = right_root_node;
    right_root_node->left = node;
    right_node->left = left_root_node;
    left_root_node->right = right_node;

    // update H.highest
    node = left_root_node->left;
    while (node != left_root_node)
    {
        node->parent = NULL;    // make sure all nodes in root list have parent == NULL
        if (higher_priority(*node, *(Heap::highest)))
            Heap::highest = node;
        node = node->left;
    }

    // rebalance
    consolidate();
};

/*
    delete specified node
    input:
        node: the node needs to delete
    output: none
*/
void Heap::delete_node(Node &node)
{
    // set the value of new_data to negative
    Data *new_data = new Data;
    new_data->profession = 0;       // make sure it has the highest priority
    Data *origin_data = node.data;  // preserve original data
    node.data = new_data;

    // call decrease and delete_min
    update(node);
    delete_highest();
    // keep the data unchanged
    node.data = origin_data;
};

/*
    rebalance the heap
*/
void Heap::consolidate()
{
    // compute max degree
    Node *m[int(log2(n)) + 1];
    // iterate through root list

    // merge two trees if needed

    // update H.highest

};

/*
    used to compare the priority between two nodes
    input:
        node1, node2: two nodes need to compare
    output:
        true: node1 has higher priority
        false: node2 has higher priority
*/
bool higher_priority(Node &node1, Node &node2)
{
    // profession category, ranking of age group, time

}

/*
    update degree
    input:
        *node: first node that needs to update degree
        d: change to the degree (can be +/-)
    output: none
*/
void Heap::update_degree(Node *node, int d)
{
    while (NULL != (*node).parent)
    {
        (*node).degree += d;
        node = (*node).parent;
    }
}

/*
    iterate through all parent nodes to check if they are marked
    input: first parent node
    output: none
*/
void Heap::cascaded_cut(Node &node)
{
    Node *p = &node;
    // return if its root node
    if (NULL == p)
        return;
    Node *parent = p->parent;
    while (true == p->mark && NULL != parent)
    {
        update_degree(p, -p->degree);
        link_root(*p);
        // move to next parent node
        p = parent;
        parent = parent->parent;
    }
    p->mark = true;
}
