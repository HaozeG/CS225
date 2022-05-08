#include "btree.h"
#include "math.h"
#include <vector>
#include <bits/stdc++.h>
#include <iostream>
#include "data.h"
using namespace std;

Btree::Btree(int order, int mode)
{
    compare_mode = mode;
    n = order;
    maxkey = n - 1;
    minkey = ceil(n / 2) - 1;
    root = nullptr;
}

void Btree::insert(relation* relation)
{
    if (root == nullptr)
        root = new Node(); // TODO: 关于new的使用
    root->key.push_back(relation);
    return;
    Node* pos_node = search(root, relation);
    part_insert(relation, pos_node);
}

Node* Btree::search(Node* start_node, relation* relation)
{
    Node* current_node = start_node;
    // 到达叶子节点，返回当前node
    if (current_node->children.empty())
        return current_node;
    // 找到相同relation，返回当前node
    for (int i = 0; i < current_node->key.size(); i++)
    {
        if (r_compare(relation, current_node->key[i]) == 0)
            return current_node;
    }
    // 与key比较进入下一层search，如此递归
    for (int j = 0; j < current_node->key.size(); j++)
    {
        if (r_compare(relation, current_node->key[j]) == -1)
            search(current_node->children[j], relation);
    }
    if (r_compare(relation, current_node->key.back()) == 1)
        search(current_node->children.back(), relation);
    return current_node;
}

Node* Btree::split(Node* node, int m)
{
    // complete left node
    Node* l_node = new Node();
    l_node->parent = node->parent; // parent
    for (int i = 0; i <= m; i++)
    {
        l_node->children.push_back(node->children[i]); // children
    }
    for (int i = 0; i < m; i++)
    {
        l_node->key.push_back(node->key[i]); //key
    }
    // complete right node
    vector<relation*>::iterator it1;
    vector<Node*>::iterator it2;
    it1 = node->key.begin();
    it2 = node->children.begin();
    for (int j = 0; j <= m; j++)
    {
        node->key.erase(it1);
        node->children.erase(it2);
        it1++;
        it2++;
    }
    return l_node;
}

void Btree::part_insert(relation* r, Node* node)
{
    // if key is not full, directly add to it
    if (node->key.size() < maxkey)
    {
        for (int i = 0; i < node->key.size(); i++)
        {
            if (r_compare(r, node->key[i]) == -1)
            {
                node->key.insert(node->key.begin() + i, r);
                return;
            }
        }
        node->key.insert(node->key.end(), r);
    }

    // else, split and put the middle element upward
    Node* p_node;
    if (node->parent.empty())
        p_node = new Node();
    else
        p_node = node->parent[0];

    int m = (node->key.size() - 1) / 2;
    relation* r_m = node->key[m];
    Node* l_node = split(node, m);
    int n = p_node->children.size();
    if (r_compare(l_node->key[0], p_node->children[n - 1]->key[0]) == 1)
    {
        p_node->children.insert(p_node->children.end(), l_node);
        p_node->children.insert(p_node->children.end(), node);
    }
    else
    {
        for (int i = 0; i < p_node->children.size(); i++)
        {
            if (r_compare(l_node->key[0], p_node->children[i]->key[0]) == -1)
            {
                p_node->children.insert(p_node->children.begin() + i, l_node);
                p_node->children.insert(p_node->children.begin() + i, node);
                break;
            }
        }
    }
    part_insert(r_m, p_node);
    return;
}

int Btree::r_compare(relation* r1, relation* r2)
{
    switch (compare_mode)
    {
    case 1: // priority
        if (r1->status->priority > r2->status->priority)
            return 1;
        else if (r1->status->priority < r2->status->priority)
            return -1;
        else
            return 0;
        break;

    default:
        break;
    }
    return 0;
}
