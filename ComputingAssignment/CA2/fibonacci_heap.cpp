#include <stdio.h>
#include <iostream>
#include <math.h>
#include "data.h"
#include "timeoffset.h"
#include "fibonacci_heap.h"
using std::cout;
// using std::cin;

// initialize Node and Heap
fibonacci::Node::Node()
{
    relation = nullptr;
    parent = nullptr;
    child = nullptr;
    left = nullptr;
    right = nullptr;
    node_num = 1;
    mark = false;
    Written = false;
    cout << "Create one node!\n";
};

fibonacci::Node::~Node()
{
    relation->f_node = nullptr;
    cout << "Delete one node!\n";
}

fibonacci::Heap::Heap()
{
    highest = nullptr;
    n = 0;
    type = 0;
    cout << "Create one empty heap!\n";
}

fibonacci::Heap::~Heap()
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
bool fibonacci::Heap::higher_priority(Node& node1, Node& node2)
{
    if (1 == type)
    {
        // profession category : int 越小越高
        // ranking of age group: 越小越高
        // time: 越小越高
        relation* data1 = node1.relation;
        relation* data2 = node2.relation;
        // add risk status judgement
        // one month extension: 30天后提高优先级(30天后risk status 2的患者跟risk 0/1的患者在risk status上同级)
        bool risk_data1 = false;
        if (0 == data1->status->risk || 1 == data1->status->risk)
            risk_data1 = true;
        else
        {
            if (3 == data1->status->risk && 0 == n)
                risk_data1 = true;
            if (2 == data1->status->risk && 30 * 24 <= (timeoffset - data1->registration->timestamp))
                risk_data1 = true;
        }
        bool risk_data2 = false;
        if (0 == data2->status->risk || 1 == data2->status->risk)
            risk_data2 = true;
        else
        {
            if (3 == data2->status->risk && 0 == n)
                risk_data2 = true;
            if (2 == data2->status->risk && 30 * 24 <= (timeoffset - data2->registration->timestamp))
                risk_data2 = true;
        }

        if (data1->person->profession < data2->person->profession)
            return risk_data1;
        else if (data1->person->profession > data2->person->profession)
            return !risk_data2;
        else
        {
            if (data1->person->age_group < data2->person->age_group)
                return risk_data1;
            else if (data1->person->age_group > data2->person->age_group)
                return !risk_data2;
            else
            {
                // penalty for withdraw(7days)
                long d1, d2;
                d1 = (true == data1->appoint->withdrawn && (0 == data1->status->risk || 1 == data1->status->risk) ? 24 * 7 * 2 : 0);
                d2 = (true == data2->appoint->withdrawn && (0 == data2->status->risk || 1 == data2->status->risk) ? 24 * 7 * 2 : 0);
                if ((data1->registration->timestamp + d1) < (data2->registration->timestamp + d2))
                    return risk_data1;
                else
                    return !risk_data2;
            }
        }
    }
    else if (2 == type)
    {
        // profession category : int 越小越高
        // ranking of age group: 越大越高
        // time: 越小越高
        relation* data1 = node1.relation;
        relation* data2 = node2.relation;
        // add risk status judgement
        // one month extension: 30天后提高优先级(30天后risk status 2的患者跟risk 0/1的患者在risk status上同级)
        bool risk_data1 = false;
        if (0 == data1->status->risk || 1 == data1->status->risk)
            risk_data1 = true;
        else
        {
            if (3 == data1->status->risk && 0 == n)
                risk_data1 = true;
            if (2 == data1->status->risk && 30 * 24 <= (timeoffset - data1->registration->timestamp))
                risk_data1 = true;
        }
        bool risk_data2 = false;
        if (0 == data2->status->risk || 1 == data2->status->risk)
            risk_data2 = true;
        else
        {
            if (3 == data2->status->risk && 0 == n)
                risk_data2 = true;
            if (2 == data2->status->risk && 30 * 24 <= (timeoffset - data2->registration->timestamp))
                risk_data2 = true;
        }

        if (data1->person->profession < data2->person->profession)
            return risk_data1;
        else if (data1->person->profession > data2->person->profession)
            return !risk_data2;
        else
        {
            if (data1->person->age_group > data2->person->age_group)
                return risk_data1;
            else if (data1->person->age_group < data2->person->age_group)
                return !risk_data2;
            else
            {
                // penalty for withdraw(7days)
                long d1, d2;
                d1 = (true == data1->appoint->withdrawn && (0 == data1->status->risk || 1 == data1->status->risk) ? 24 * 7 * 2 : 0);
                d2 = (true == data2->appoint->withdrawn && (0 == data2->status->risk || 1 == data2->status->risk) ? 24 * 7 * 2 : 0);
                if ((data1->registration->timestamp + d1) < (data2->registration->timestamp + d2))
                    return risk_data1;
                else
                    return !risk_data2;
            }
        }
    }
    else
    {
        // profession category : 优先2 其余越小越高
        // ranking of age group: 越大越高
        // time: 越小越高
        relation* data1 = node1.relation;
        relation* data2 = node2.relation;
        // add risk status judgement
        // one month extension: 30天后提高优先级(30天后risk status 2的患者跟risk 0/1的患者在risk status上同级)
        bool risk_data1 = false;
        if (0 == data1->status->risk || 1 == data1->status->risk)
            risk_data1 = true;
        else
        {
            if (3 == data1->status->risk && 0 == n)
                risk_data1 = true;
            if (2 == data1->status->risk && 30 * 24 <= (timeoffset - data1->registration->timestamp))
                risk_data1 = true;
        }
        bool risk_data2 = false;
        if (0 == data2->status->risk || 1 == data2->status->risk)
            risk_data2 = true;
        else
        {
            if (3 == data2->status->risk && 0 == n)
                risk_data2 = true;
            if (2 == data2->status->risk && 30 * 24 <= (timeoffset - data2->registration->timestamp))
                risk_data2 = true;
        }

        if ((2 == data1->person->profession) || (data1->person->profession < data2->person->profession))
            return risk_data1;
        else if ((2 == data2->person->profession) || (data1->person->profession > data2->person->profession))
            return !risk_data2;
        else
        {
            if (data1->person->age_group > data2->person->age_group)
                return risk_data1;
            else if (data1->person->age_group < data2->person->age_group)
                return !risk_data2;
            else
            {
                // penalty for withdraw(7days)
                long d1, d2;
                d1 = (true == data1->appoint->withdrawn && (0 == data1->status->risk || 1 == data1->status->risk) ? 24 * 7 * 2 : 0);
                d2 = (true == data2->appoint->withdrawn && (0 == data2->status->risk || 1 == data2->status->risk) ? 24 * 7 * 2 : 0);
                if ((data1->registration->timestamp + d1) < (data2->registration->timestamp + d2))
                    return risk_data1;
                else
                    return !risk_data2;
            }
        }
    }
}

/*
    link one node to root list
    input:
        node: the node need to link
    output: none
*/
void fibonacci::Heap::link_root(Node& node)
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
void fibonacci::Heap::insert(relation* relation)
{
    // assign treatment type to the heap
    if (0 == type)
        type = relation->status->type;
    Node* node = new Node;
    node->relation = relation;
    relation->f_node = node;
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
void fibonacci::Heap::update(Node& node)
{
    Node* parent_node = node.parent;

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

    Node* child_node = node.child;
    Node* left_root_node = highest;
    Node* right_root_node = highest->right;
    if (nullptr != node.child)
    {
        // connect child nodes to root list
        Node* right_child_node = child_node->right;
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
    cout << "Sucessfully update " << node.relation->person->name << "\n";
}

/*
    get data pointer of the highest node
    input: none
    output: data pointer
*/
relation* fibonacci::Heap::get_highest()
{
    relation* relation = nullptr;
    if (nullptr != highest)
        relation = highest->relation;
    Heap::delete_highest();
    return relation;
}

/*
    delete the highest node
    input: none
    ouput: none
*/
void fibonacci::Heap::delete_highest()
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
    Node* node = highest->child;
    if (nullptr == node)
    {
        Node* left_node = highest->left;
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
        Node* right_node = node->right;
        Node* left_root_node = highest->left;
        Node* right_root_node = highest->right;
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
void fibonacci::Heap::delete_node(Node& node)
{
    // // check if node is in the heap
    // if (nullptr == node.left)
    // {
    //     cout << "Node is not in the heap\n";
    //     return;
    // }
    // set the value of new_data to negative
    relation* new_relation = new relation;
    // TODO: create a new node based on different priority rules
    // make sure it has the highest priority
    new_relation->person->name = node.relation->person->name;
    if (1 == type)
    {
        new_relation->person->profession = -1;
        new_relation->status->risk = 0;
    }
    else if (2 == type)
    {
        new_relation->person->profession = -1;
        new_relation->status->risk = 0;
    }
    else
    {
        new_relation->person->profession = 2;
        new_relation->status->risk = 0;
    }
    relation* origin_relation = node.relation; // preserve original data
    node.relation->f_node = nullptr;
    node.relation = new_relation;

    // call decrease and delete_min
    update(node);
    relation* p = highest->relation;
    delete_highest();
    // keep the data unchanged
    delete new_relation;

    cout << "Delete " << p->person->name << "\n";
};

/*
    rebalance the heap
*/
void fibonacci::Heap::consolidate()
{
    // compute max node_num and prepare hash map
    int maxdegree = int(log2(n));
    // cout << maxdegree << "\n";
    Node* m[maxdegree + 1];
    for (int i = 0; i <= maxdegree; i++)
        m[i] = nullptr;
    // iterate through root list
    while (nullptr != highest)
    {
        // find the root node with the smallest node_num
        int mindegree = highest->node_num;
        Node* min_p = highest;
        Node* p = highest->left;
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
                // swap root nodes of two heaps based on priority
                if (higher_priority(*p, *m[mindegree]))
                {
                    Node* temp;
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
                p = m[mindegree]; // update pointer to the root node
                m[mindegree] = nullptr;
                mindegree++; // check next position
            } while (nullptr != m[mindegree]);
            m[mindegree] = p;
        }
    }

    // connect heaps together
    for (int i = 0; i <= maxdegree; i++)
        if (nullptr != m[i])
            link_root(*m[i]);
    cout << "Finish consolidate\n";
};

/*
    update node_num
    input:
        *node: first node that needs to update node_num
        d: change to the node_num (can be +/-)
    output: none
*/
void fibonacci::Heap::update_degree(Node* node, int d)
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
void fibonacci::Heap::cascaded_cut(Node* node)
{
    // return if it's root node
    if (nullptr == node)
        return;
    Node* parent = node->parent;
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
