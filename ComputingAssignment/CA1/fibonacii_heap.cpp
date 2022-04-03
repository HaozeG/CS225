#include <stdio.h>
#include <iostream>
#include <math.h>
#include "timeoffset.h"
#include "fibonacii_heap.h"
using std::cout;
using std::cin;

// initialize Node and Heap
Node::Node()
{
    data = nullptr;
    parent = nullptr;
    child = nullptr;
    left = nullptr;
    right = nullptr;
    node_num = 1;
    mark = false;
    cout << "Create one node!\n";
};

Node::~Node()
{
    data->node = nullptr;
    cout << "Delete one node!\n";
}

Heap::Heap()
{
    highest = nullptr;
    n = 0;
    cout << "Create one empty heap!\n";
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
inline bool Heap::higher_priority(Node &node1, Node &node2)
{
    // profession category, ranking of age group, time
    // profession category : int 越小越高
    // ranking of age group: 越小越高
    // time:
    Data *data1 = node1.data;
    Data *data2 = node2.data;
    // add risk status judgement
    bool risk_data1 = false;
    if (0 == data1->risk || 1 == data1->risk)
        risk_data1 = true;
    else
    {
        if (3 == data1->risk && 0 == n)
            risk_data1 = true;
        if (2 == data1->risk && 30*24 >= (timeoffset - data1->timestamp))
            risk_data1 = true;
    }
    bool risk_data2 = false;
    if (0 == data2->risk || 1 == data2->risk)
        risk_data2 = true;
    else
    {
        if (3 == data2->risk && 0 == n)
            risk_data2 = true;
        if (2 == data2->risk && 30*24 >= (timeoffset - data2->timestamp))
            risk_data2 = true;
    }

    if (data1->profession < data2->profession)
        return risk_data1;
    else if (data1->profession > data2->profession)
        return !risk_data2;
    else
    {
        if (data1->age_group < data2->age_group)
            return risk_data1;
        else if (data1->age_group > data2->age_group)
            return !risk_data2;
        else
        {
            // penalty for withdraw
            long d1, d2;
            d1 = (true == data1->withdrawn && (0 == data1->risk || 1 == data1->risk) ? 24 * 7 : 0);
            d2 = (true == data2->withdrawn && (0 == data2->risk || 1 == data2->risk) ? 24 * 7 : 0);
            if ((data1->timestamp + d1)< (data2->timestamp + d2))
                return risk_data1;
            else
                return !risk_data2;
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
    if (nullptr == highest)
        highest = &node;
    else
    {
        // link to root list
        node.left = highest;
        node.right = highest->right;
        highest->right = &node;
        node.right->left = &node;

        // adjust H.highest
        if (higher_priority(node, *highest))
            highest = &node;
    }
    node.parent = nullptr;
    node.mark = false;
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
    data->node = node;
    node->right = node;
    node->left = node;
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
    update_degree(node.parent, -node.node_num);
    if (nullptr != parent_node && parent_node->child == &node)
        parent_node->child = (&node == node.right ? nullptr : node.right);
    // remove from heap
    if (nullptr != parent_node && nullptr != parent_node->child)
    {
        node.left->right = node.right;
        node.right->left = node.left;
        node.right = &node;
        node.left = &node;
    }

    // link to root list if it's not in root list
    if (nullptr != parent_node)
        link_root(node);
    else
    {
        if (higher_priority(node, *highest))
            highest = &node;
    }

    // TODO: 处理没有child的情况
    Node *child_node = node.child;
    Node *left_root_node = highest;
    Node *right_root_node = highest->right;
    if (nullptr != node.child)
    {
        // connect child nodes to root list
        Node *right_child_node = child_node->right;
        child_node->right = right_root_node;
        right_root_node->left = child_node;
        right_child_node->left = left_root_node;
        left_root_node->right = right_child_node;

        // update H.highest
        child_node = left_root_node->right;
        while (child_node != right_root_node)
        {
            child_node->mark = false;
            child_node->parent = nullptr; // make sure all nodes in root list have parent == nullptr
            if (higher_priority(*child_node, *highest))
                highest = child_node;
            child_node = child_node->right;
        }
    }
    node.node_num = 1;
    node.child = nullptr;

    // cascaded cut parent nodes
    cascaded_cut(parent_node);
    cout << "Sucessfully update " << node.data->name << "\n";
}

/*
    get data pointer of the highest node
    input: none
    output: data pointer
*/
Data *Heap::get_highest()
{
    Data *data = nullptr;
    if (nullptr != highest)
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
        highest = nullptr;
        cout << "Finish delete highest node\n";
        return;
    }
    // connect child nodes to root list
    Node *node = highest->child;
    // TODO: 没有child的情况
    if (nullptr == node)
    {
        Node *left_node = highest->left;
        highest->left->right = highest->right;
        highest->right->left = highest->left;
        delete highest;
        highest = left_node;
        node = left_node->left;
        while (node != left_node)
        {
            node->mark = false;
            node->parent = nullptr; // make sure all nodes in root list have parent == nullptr
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
            node->mark = false;
            node->parent = nullptr; // make sure all nodes in root list have parent == nullptr
            if (higher_priority(*node, *highest))
                highest = node;
            node = node->left;
        }
    }
    cout << "Finish delete highest node\n";

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
    // // check if node is in the heap
    // if (nullptr == node.left)
    // {
    //     cout << "Node is not in the heap\n";
    //     return;
    // }
    // set the value of new_data to negative
    Data *new_data = new Data;
    new_data->name = node.data->name;
    new_data->profession = -1; // make sure it has the highest priority
    new_data->risk = 0;
    Data *origin_data = node.data; // preserve original data
    node.data = new_data;

    // call decrease and delete_min
    // TODO: update无效
    update(node);
    Data *p = highest->data;
    delete_highest();
    // keep the data unchanged
    delete new_data;
    cout << "Delete " << p->name << "\n";
};

/*
    rebalance the heap
*/
void Heap::consolidate()
{
    // degree定义为child数量，此处计算degree时需要全部加1
    // compute max node_num and prepare hash map
    int maxdegree = int(log2(n));
    // cout << maxdegree << "\n";
    Node *m[maxdegree + 1];
    for (int i = 0; i <= maxdegree; i++)
        m[i] = nullptr;
    // iterate through root list
    while (nullptr != highest)
    {
        // find the root node with the smallest node_num
        int mindegree = highest->node_num;
        Node *min_p = highest;
        Node *p = highest->left;
        while (p != highest)
        {
            // cout << highest->data->name << "\n";
            // cout << highest->left->data->name << "\n";
            // cout << p->data->name << "\n";
            if (p->node_num < mindegree)
            {
                mindegree = p->node_num;
                min_p = p;
            }
            p = p->left;
        }
        // delete from root list
        p = min_p;
        if (p == p->right)
        {
            highest = nullptr;
        }
        else
        {
            // update H.highest if needed
            highest = p->right;
            p->right->left = p->left;
            p->left->right = p->right;
        }
        p->right = p;
        p->left = p;

        mindegree = int(log2(mindegree));
        if (nullptr == m[mindegree])
        {
            m[mindegree] = p;
        }
        else
        {
            do
            {
                // swap if needed
                if (higher_priority(*p, *m[mindegree]))
                {
                    Node *temp;
                    temp = p;
                    p = m[mindegree];
                    m[mindegree] = temp;
                }
                p->parent = m[mindegree];
                if (nullptr != m[mindegree]->child)
                {
                    // connect with other child node
                    p->right = m[mindegree]->child->right;
                    p->left = m[mindegree]->child;
                    p->left->right = p;
                    p->right->left = p;
                }
                m[mindegree]->child = p;
                m[mindegree]->node_num += p->node_num;
                p = m[mindegree];   // update pointer to the root node
                m[mindegree] = nullptr;
                mindegree++;
            } while (nullptr != m[mindegree]);
            m[mindegree] = p;    // merging two tree with same node_num -> new tree with node_num + 1
        }
        // cout << mindegree << "\n";
    }

    // connect heaps together
    for (int i = 0; i <= maxdegree; i++)
        if (nullptr != m[i]) link_root(*m[i]);
    cout << "Finish consolidate\n";
};

/*
    update node_num
    input:
        *node: first node that needs to update node_num
        d: change to the node_num (can be +/-)
    output: none
*/
void Heap::update_degree(Node *node, int d)
{
    if (0 == d || nullptr == node)
        return;
    while (nullptr != (*node).parent)
    {
        (*node).node_num += d;
        node = (*node).parent;
    }
    node->node_num += d;
}

/*
    iterate through all parent nodes to check if they are marked
    input: first parent node
    output: none
*/
void Heap::cascaded_cut(Node *node)
{
    // TODO: 剪掉后是否更新child数值
    // return if its root node
    if (nullptr == node)
        return;
    Node *parent = node->parent;
    // if in root list
    if (nullptr == parent)
    {
        node->mark = false;
        cout << "Finish cascaded cut\n";
        return;
    }
    if (false == parent->mark)
    {
        node->mark = true;
        cout << "Finish cascaded cut\n";
        return;
    }
    while (true == node->mark && nullptr != parent)
    {
        if (parent->child == node)
            parent->child = (node == node->right ? nullptr : node->right);
        update_degree(node, -node->node_num);
        // remove from heap
        if (nullptr != parent->child)
        {
            node->left->right = node->right;
            node->right->left = node->left;
            node->right = node;
            node->left = node;
        }
        link_root(*node);
        // move to next parent node
        node = parent;
        parent = parent->parent;
    }
    cout << "Finish cascaded cut\n";
}
