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
    // profession category : int 越小越高
    // ranking of age group: 越小越高
    // time:
    Data *data1 = node1.data;
    Data *data2 = node2.data;
    if (data1->profession < data2->profession)
        return true;
    else if (data1->profession > data2->profession)
        return false;
    else
    {
        if (data1->age_group < data2->age_group)
            return true;
        else if (data1->age_group > data2->age_group)
            return false;
        else
        {
            if (data1->timestamp < data2->timestamp)
                return true;
            else
                return false;
        }
    }
}

/*
    link one node to root list
    input:
        node: the node need to link
    output: none
*/
inline void Heap::link_root(Node &node)
{
    if (NULL == highest)
        highest = &node;
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
    data->node = node;
    // TODO: Data中指向Node的指针需要更新
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

/*
    get data pointer of the highest node
    input: none
    output: data pointer
*/
Data *Heap::get_highest()
{
    Data *data = NULL;
    if (NULL != highest)
        data = highest->data;
    Heap::delete_highest();
    return data;
}

/*
    delete the highest node
    input: none
    ouput: none
*/
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
    // TODO: 只有root list的情况
    if (NULL == node)
    {
        Node *left_node = highest->left;
        highest->left->right = highest->right;
        highest->right->left = highest->left;
        delete highest;
        highest = left_node;
        node = left_node->left;
        while (node != left_node)
        {
            node->parent = NULL;    // make sure all nodes in root list have parent == NULL
            if (higher_priority(*node, *highest))
                highest = node;
            node = node->left;
        }
    }
    else
    {
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
    // degree定义为child数量，此处计算degree时需要全部加1
    // compute max degree and prepare hash map
    int maxdegree = int(log2(n));
    cout << maxdegree << "\n";
    Node *m[maxdegree + 1];
    for (int i = 0; i <= maxdegree; i++)
        m[i] = NULL;
    // iterate through root list
    while (NULL != highest)
    {
        // find the root node with the smallest degree
        int mindegree = highest->degree + 1;
        Node *min_p = highest;
        Node *p = highest->right;
        while (p != highest)
        {
            if ((p->degree + 1) <= mindegree)
            {
                mindegree = p->degree + 1;
                min_p = p;
            }
            p = p->right;
        }
        // delete from root list
        if (p == p->right)
        {
            highest = NULL;
        }
        else
        {
            // update H.highest if needed
            if (p == highest)
                highest = p->right;
            p->right->left = p->left;
            p->left->right = p->right;
            p->right = p;
            p->left = p;
        }

        mindegree = int(log2(mindegree));
        if (NULL == m[mindegree])
        {
            m[mindegree] = p;
        }
        else
        {
            do
            {
                p->parent = m[mindegree];
                if (NULL != m[mindegree]->child)
                {
                    // connect with other child node
                    p->right = m[mindegree]->child->right;
                    p->left = m[mindegree]->child;
                    m[mindegree]->child->right = p;
                    p->right->left = p;
                }
                m[mindegree]->child = p;
                m[mindegree]->degree += p->degree;
                p = m[mindegree];   // update pointer to the root node
                m[mindegree] = NULL;
                mindegree++;
            } while (NULL != m[mindegree]);
            m[mindegree] = p;    // merging two tree with same degree -> new tree with degree + 1
        }
    }

    // connect heaps together
    for (int i = 0; i <= maxdegree; i++)
        if (NULL != m[i]) link_root(*m[i]);
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
