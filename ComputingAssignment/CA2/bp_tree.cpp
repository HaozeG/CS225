#include "bp_tree.h"
#include "data.h"
// #include "base.cpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using std::cin;
using std::cout;

bp_tree::Tree::Tree()
{
    root_node = new bp_tree::Node;
    cout << "Create bp_tree\n";
}

bp_tree::Tree::~Tree()
{
    delete root_node;
}

// BFS display
void bp_tree::Tree::display(bp_tree::Node* root)
{
    cout << "abab";
    queue<bp_tree::Node*> l;
    l.push(root);
    while (!l.empty())
    {
        bp_tree::Node* temp = l.front();
        l.pop();
        // cout << temp-;
        cout << temp->children.size() << "tetetst";
        for (int i = 0; i < temp->children.size(); i++)
        {
            //     cout << temp->children.size() << " hughrughrug";
            if (i < temp->key.size())
                cout << temp->key.at(i);
            l.push(temp->children.at(i));
        }
        cout << "\n";
    }
}

// search for the leaf node that points to the block suitable for key
bp_tree::Node* bp_tree::Tree::search_node(bp_tree::Node* node, char* key)
{
    if (node->is_leaf)
        return node;
    // stop when finding an empty space in vector key
    int i = 0;
    // iterate through to find an approriate branch
    while (i < node->key.size() && nullptr != node->key.at(i) && keycmp(key, node->key.at(i)) >= 0)
    {
        i++;
    }
    //     if (node->is_leaf)
    //         return node->children.at(i);
    //     else if (!node->is_leaf)
    //         return nullptr;
    //     else
    return search_node(node->children.at(i), key);
}

// Block<relation>;

void bp_tree::Tree::insert(char* key, Block<relation>* block)
{
    //     cout << "hhghg\n";
    bp_tree::Node* node = root_node;
    // go to appropriate leaf node
    node = search_node(node, key);
    // find place to insert block
    int i = 0;
    // iterate through to find an approriate branch
    while (i < node->key.size() && nullptr != node->key.at(i) && keycmp(key, node->key.at(i)) >= 0)
    {
        cout << i;
        i++;
    }
    // insert block pointer and key
    node->key.insert(node->key.begin() + i, key);
    node->blocks.insert(node->blocks.begin() + i, block);
    // check for split
    bp_tree::Node* new_root;
    if (0 == node->key.capacity() - node->key.size())
        new_root = node->split_node();
    if (nullptr == new_root)
        this->root_node = new_root;
    cout << "Insert key successful\n";
}

/*
key1 > key2 : return > 0
key1 = key2 : return = 0
key1 < key2 : return < 0
*/
int bp_tree::keycmp(char* key1, char* key2)
{
    return strcmp(key1, key2);
}

// int bp_tree::Tree::merge_node()
// {
//     return 0;
// }

// split one node
bp_tree::Node* bp_tree::Node::split_node()
{
    bp_tree::Node* node = this;
    while (0 == node->key.capacity() - node->key.size())
    {
        int mid = node->key.capacity() / 2;
        bp_tree::Node* new_node = new bp_tree::Node();
        new_node->is_leaf = node->is_leaf;
        new_node->parent = node->parent;
        new_node->right = node->right;
        new_node->right->left = new_node;
        node->right = new_node;
        new_node->left = node;
        char* new_key = node->key.at(mid);
        if (node->is_leaf)
        {
            new_node->key.assign(node->key.begin() + mid, node->key.end());
            node->key.erase(node->key.begin() + mid, node->key.end());
            new_node->children.assign(node->children.begin() + mid, node->children.end());
            node->children.erase(node->children.begin() + mid, node->children.end());
            new_node->blocks.assign(node->blocks.begin() + mid, node->blocks.end());
            node->blocks.erase(node->blocks.begin() + mid, node->blocks.end());
        }
        else
        {
            new_node->key.assign(node->key.begin() + mid + 1, node->key.end());
            node->key.erase(node->key.begin() + mid, node->key.end());
            new_node->children.assign(node->children.begin() + mid + 1, node->children.end());
            node->children.erase(node->children.begin() + mid + 1, node->children.end());
        }

        cout << "Split one node\n";
        if (nullptr == node->parent)
        {
            bp_tree::Node* new_root = new bp_tree::Node();
            new_root->is_leaf = false;
            new_root->children.push_back(node);
            new_root->children.push_back(new_node);
            new_root->key.push_back(new_key);
            // TODO: 更新bp tree的root_node指针
            return new_root;
        }
        else
            node->insert_key(new_key, new_node);
        // recursively split
        node = node->parent;
    }
    return nullptr;
}

void bp_tree::Node::insert_key(char* key, bp_tree::Node* new_node)
{
    int i = 0;
    // iterate through to find an approriate place
    while (i < this->key.size() && nullptr != this->key.at(i) && bp_tree::keycmp(key, this->key.at(i)) >= 0)
    {
        i++;
    }
    this->key.insert(this->key.begin() + i, key);
    this->children.insert(this->children.begin() + i, new_node);
    cout << "Insert a key\n";
}

bp_tree::Node::Node()
{
    max_degree = 3;
    key = std::vector<char*>(max_degree);
    children = std::vector<Node*>(max_degree + 1);
    blocks = std::vector<Block<relation>*>(max_degree + 1);
    parent = nullptr;
    is_leaf = true;
    //     block = nullptr;
    cout << "Create bp_node\n";
}

bp_tree::Node::~Node()
{
    cout << "Delete bp_node\n";
}
