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
    minkey = (n - 1) / 2;
    root = nullptr;

    cout << "Btree built.\n";
    cout << "order = " << n << "\n";
    cout << "max key number = " << maxkey << "\n";
    cout << "min key number = " << minkey << "\n";
    cout << "\n";
}

void Btree::insert(relation* relation)
{
    cout << "Insert Person ID: " << relation->person->id << "\n";
    if (root == nullptr)
    {
        root = new Node(); // TODO: 关于new的使用
        root->key.push_back(relation);
        return;
    }
    Node* pos_node = search(root, relation);
    cout << "search success\n";
    cout << "node's first person id = " << pos_node->key.front()->person->id << "\n";
    cout << "node's size = " << pos_node->key.size() << "\n";
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
    if (!node->children.empty())
    {
        for (int i = 0; i <= m; i++)
        {
            l_node->children.push_back(node->children[i]); // children
        }
    }
    for (int i = 0; i < m; i++)
    {
        l_node->key.push_back(node->key[i]); //key
    }

    // complete right node
    vector<relation*>::iterator it1;
    it1 = node->key.begin();
    for (int j = 0; j <= m; j++)
    {
        node->key.erase(it1);
    }
    if (!node->children.empty())
    {
        vector<Node*>::iterator it2;
        it2 = node->children.begin();
        for (int k = 0; k <= m; k++)
        {
            node->children.erase(it2);
        }
    }

    return l_node;
}

void Btree::part_insert(relation* r, Node* node)
{
    // if key is not full, directly add to it
    if (node->key.size() < maxkey)
    {
        cout << "not full\n";
        for (int i = 0; i < node->key.size(); i++)
        {
            if (r_compare(r, node->key[i]) == -1)
            {
                node->key.insert(node->key.begin() + i, r);
                return;
            }
        }
        node->key.insert(node->key.end(), r);
        return;
    }

    // else, split and put the middle element upward
    for (int i = 0; i < node->key.size(); i++)
    {
        if (r_compare(r, node->key[i]) == -1)
        {
            node->key.insert(node->key.begin() + i, r);
        }
    }
    if (r_compare(r, node->key.back()) != -1)
        node->key.insert(node->key.end(), r);
    cout << "node size = " << node->key.size() << "\n";

    Node* p_node;
    if (node->parent.empty())
    {
        p_node = new Node();
        cout << "1\n";
    }
    else
    {
        p_node = node->parent[0];
        cout << "2\n";
    }

    int m = (node->key.size() - 1) / 2;
    relation* r_m = node->key[m];
    cout << "r_m's id = " << r_m->person->id << "\n";
    Node* l_node = split(node, m);
    cout << "left node size = " << l_node->key.size() << " first id = " << l_node->key.front()->person->id << "\n";
    cout << "right node size = " << node->key.size() << " first id = " << node->key.front()->person->id << "\n";

    int n = p_node->children.size();
    if (n == 0)
    {
        p_node->children.insert(p_node->children.end(), l_node);
        p_node->children.insert(p_node->children.end(), node);
        cout << "lala\n";
        part_insert(r_m, p_node);
    }
    else
    {
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
    }
    return;
}

int Btreebase::r_compare(relation* r1, relation* r2)
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

// Delete Operation
void Btree::remove(relation* relation)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->deletion(relation);

    if (root->key.empty())
    {
        Node* tmp = root;
        if (root->children.empty())
            root = NULL;
        else
            root = root->children[0];

        delete tmp;
    }
    return;
}

// Find the key
int Node::findKey(relation* r)
{
    int idx = 0;
    while (idx < key.size() && (r_compare(key[idx], r) == -1))
        ++idx;
    return idx;
}

// Deletion operation
void Node::deletion(relation* r)
{
    int idx = findKey(r);

    if (idx < key.size() && (r_compare(key[idx], r) == 0))
    {
        if (children.empty())
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        if (children.empty())
        {
            cout << "The person does not exist in the tree\n";
            return;
        }

        bool flag = ((idx == key.size()) ? true : false);

        if (children[idx]->key.size() < (n/2)) // <t
            fill(idx);

        if (flag && idx > key.size())
            children[idx - 1]->deletion(r);
        else
            children[idx]->deletion(r);
    }
    return;
}

// Remove from the leaf
void Node::removeFromLeaf(int idx)
{
    // for (int i = idx + 1; i < key.size(); ++i)
    //     key[i - 1] = key[i];

    // keynum--;
    key.erase(key.begin() + idx);

    return;
}

// Delete from non leaf node
void Node::removeFromNonLeaf(int idx)
{
    relation* r = key[idx];

    if (children[idx]->key.size() >= (n/2)) // t
    {
        relation* pred = getPredecessor(idx);
        key[idx] = pred; // TODO:是否可以直接赋值
        children[idx]->deletion(pred);
    }

    else if (children[idx + 1]->key.size() >= (n/2)) // t
    {
        relation* succ = getSuccessor(idx);
        key[idx] = succ;
        children[idx + 1]->deletion(succ);
    }

    else
    {
        merge(idx);
        children[idx]->deletion(r);
    }
    return;
}

relation* Node::getPredecessor(int idx)
{
    Node* cur = children[idx];
    while (!cur->children.empty())
        cur = cur->children[cur->key.size()];

    return cur->key[cur->key.size() - 1];
}

relation* Node::getSuccessor(int idx)
{
    Node* cur = children[idx + 1];
    while (!cur->children.empty())
        cur = cur->children[0];

    return cur->key[0];
}

void Node::fill(int idx)
{
    if (idx != 0 && children[idx - 1]->key.size() >= (n/2)) // t
        borrowFromPrev(idx);

    else if (idx != key.size() && children[idx + 1]->key.size() >= (n/2)) // t
        borrowFromNext(idx);

    else
    {
        if (idx != key.size())
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

// Borrow from previous
void Node::borrowFromPrev(int idx)
{
    Node* child = children[idx];
    Node* sibling = children[idx - 1];

    child->key.insert(child->key.begin(), key[idx - 1]);

    if (!child->children.empty())
    {
        child->children.insert(child->children.begin(), sibling->children[sibling->key.size()]);
    }

    key[idx - 1] = sibling->key[sibling->key.size() - 1];

    return;
}

// Borrow from the next
void Node::borrowFromNext(int idx)
{
    Node* child = children[idx];
    Node* sibling = children[idx + 1];

    child->key.push_back(key[idx]);

    if (!(child->children.empty()))
        child->children.push_back(sibling->children[0]);

    key[idx] = sibling->key[0];

    sibling->key.pop_back();

    if (!sibling->children.empty())
    {
        sibling->children.pop_back();
    }

    return;
}

// Merge
void Node::merge(int idx)
{
    Node* child = children[idx];
    Node* sibling = children[idx + 1];

    child->key[minkey] = key[idx];

    for (int i = 0; i < sibling->key.size(); ++i)
        child->key.push_back(sibling->key[i]);

    if (!child->children.empty())
    {
        for (int i = 0; i <= sibling->key.size(); ++i)
            child->children.push_back(sibling->children[i]);
    }

    key.erase(key.begin() + idx);
    children.erase(children.begin()+idx+1);

    delete (sibling);
    return;
}

void Btree::traverse()
{
    if (root!=NULL)
        root->traverse();
}

void Node::traverse()
{
    int i;
    for (i = 0; i < key.size(); i++)
    {
        if (!children.empty())
            children[i]->traverse();
        cout << " " << key[i]->status->priority;
    }
    if (!children.empty())
        children[i]->traverse();
}
