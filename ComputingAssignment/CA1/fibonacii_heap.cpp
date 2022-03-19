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
    cout << "Add one node!\n";
};

Node::~Node()
{
    cout << "Delete one node!\n";
}

Heap::Heap()
{
    highest = NULL;
    n = 0;
    cout << "Build one empty heap!\n";
}

Heap::~Heap()
{
    cout << "Delete heap\n";
}

/*
    used to compare the priority between two nodes
    input:
        node1, node2: two nodes need to compare
    output:
        true: node1 has higher priority
        false: node2 has higher priority
*/
inline bool higher_priority(Node &node1, Node &node2)
{
    // profession category, ranking of age group, time
    return false;
}

/*
    link one node to root list
    input:
        node: the node need to link
    output: none
*/
inline void Heap::link_root(Node &node)
{
    // link to root list
    node.left = highest;
    node.right = highest->right;
    highest->right = &node;
    node.right->left = &node;
    node.parent = NULL;

    // adjust H.highest
    if (higher_priority(node, *highest))
        highest = &node;
}

/*
    insert new node into root
    input:
        data: the data of the node
    output: none
*/
void Heap::insert(Data *data)
{
    Node *node = new Node;
    node->data = data;
    link_root(*node);
    Heap::n++;
    cout << "Insert one node!\n";
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
    Node *left_root_node = highest;
    Node *right_root_node = highest->right;
    child_node->right = right_root_node;
    right_root_node->left = child_node;
    right_child_node->left = left_root_node;
    left_root_node->right = right_child_node;
    node.degree = 1;
    node.child = NULL;

    // update H.highest
    child_node = left_root_node->left;
    while (child_node != left_root_node)
    {
        child_node->parent = NULL;    // make sure all nodes in root list have parent == NULL
        if (higher_priority(*child_node, *highest))
            highest = child_node;
        child_node = child_node->left;
    }

    // cascaded cut parent nodes
    cascaded_cut(parent_node);
    cout << "Sucessfully update!\n";
}

// to get the data of the highest node, just H.highest->data
void Heap::delete_highest()
{
    // check if the heap is empty
    if (0 == n)
    {
        cout << "Already empty!\n";
        return;
    }
    Heap::n--;
    if (0 == n)
    {
        delete highest;
        highest = NULL;
        return;
    }

    // connect child nodes to root list
    Node *node = highest->child;
    Node *right_node = node->right;
    Node *left_root_node = highest->left;
    Node *right_root_node = highest->right;
    if (highest->left == highest)
    {
        // only one node in root list
        left_root_node = highest->child;
    }
    else
    {
        node->right = right_root_node;
        right_root_node->left = node;
        right_node->left = left_root_node;
        left_root_node->right = right_node;
    }
    delete highest;

    // update H.highest
    highest = left_root_node;
    node = left_root_node->left;
    while (node != left_root_node)
    {
        node->parent = NULL;    // make sure all nodes in root list have parent == NULL
        if (higher_priority(*node, *highest))
            highest = node;
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
    // check if node is in the heap
    if (NULL == node.left)
    {
        cout << "Node is not in the heap\n";
        return;
    }
    // set the value of new_data to negative
    Data *new_data = new Data;
    new_data->profession = 0;       // make sure it has the highest priority
    Data *origin_data = node.data;  // preserve original data
    node.data = new_data;

    // call decrease and delete_min
    update(node);
    // keep the data unchanged
    node.data = origin_data;
    delete_highest();
    // TODO: Data的析构
    delete new_data;
};

/*
    rebalance the heap
*/
void Heap::consolidate()
{
    // compute max degree and prepare hash map
    int maxdegree = int(log2(n)) + 1;
    Node *m[maxdegree];
    for (int i = 0; i < maxdegree; i++)
        m[i] = NULL;
    // iterate through root list
    while (highest->right != highest)
    {
        // find the root node with the smallest degree
        int mindegree = highest->degree;
        Node *min_p = highest;
        Node *p = highest->right;
        while (p != highest)
        {
            if (p->degree <= mindegree && p != m[int(log2(mindegree))])
            {
                mindegree = p->degree;
                min_p = p;
            }
            p = p->right;
        }

        mindegree = int(log2(mindegree));
        if (NULL == m[mindegree])
        {
            m[mindegree] = p;
        }
        else
        {
            // delete from root list
            p->left->right = p->right;
            p->right->left = p->left;
            // merge two trees
            p->parent = m[mindegree];
            p->right = m[mindegree]->child->right;
            p->left = m[mindegree]->child;
            m[mindegree]->child->right = p;
            p->right->left = p;
            m[mindegree]->degree += p->degree;
            m[mindegree + 1] = m[mindegree];    // merging two tree with same degree -> new tree with degree + 1
            m[mindegree] = NULL;

            // update H.highest if needed
            if (p == highest)
                highest = m[mindegree + 1];
        }
    }
};

/*
    update degree
    input:
        *node: first node that needs to update degree
        d: change to the degree (can be +/-)
    output: none
*/
void Heap::update_degree(Node *node, int d)
{
    if (0 == d)
        return;
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
void Heap::cascaded_cut(Node *node)
{
    // return if its root node
    if (NULL == node)
        return;
    Node *parent = node->parent;
    while (true == node->mark && NULL != parent)
    {
        update_degree(node, -node->degree);
        link_root(*node);
        // move to next parent node
        node = parent;
        parent = parent->parent;
    }
    node->mark = true;
}
