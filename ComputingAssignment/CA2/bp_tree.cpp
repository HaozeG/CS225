#include "bp_tree.h"
#include "data.h"
// #include "base.cpp"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <array>
// #include <queue>
using std::cin;
using std::cout;
// const int max_degree = 3;

bp_tree::Tree::Tree()
{
    root_node = new bp_tree::Node;
    cout << "Create bp_tree\n";
}

bp_tree::Tree::~Tree()
{
    delete root_node;
}

// Go through the block list
void bp_tree::Tree::display(bp_tree::Node* root)
{
    // find the minimum
    bp_tree::Node* node = search_node(root_node, (char*)"0");
    cout << "Keys in root nodes:\n";
    while (nullptr != node)
    {
        for (int i = 0; i < node->key->size(); i++)
        {
            if (nullptr != node->key->at(i))
                cout << node->key->at(i) << " - ";
        }
        node = node->right;
        cout << "\n->\n";
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
    while (i < max_degree && nullptr != node->key->at(i) && keycmp(key, node->key->at(i)) > 0)
    {
        i++;
    }
    //     if (node->is_leaf)
    //         return node->children->at(i);
    //     else if (!node->is_leaf)
    //         return nullptr;
    //     else
    return search_node(node->children->at(i), key);
}

// Block<relation>;

void bp_tree::Tree::insert(char* key, Block<relation>* block)
{
    bp_tree::Node* node = root_node;
    // go to appropriate leaf node
    node = search_node(node, key);
    // find place to insert block
    int i = 0;
    // iterate through to find an approriate branch
    while (i < node->key->size() && nullptr != node->key->at(i) && keycmp(key, node->key->at(i)) > 0)
    {
        // cout << node->key->at(i) << " ";
        i++;
    }
    // insert block pointer and key
    if (nullptr != node->blocks->at(1) || i != 1)
    {
        for (int j = int(node->key->size()) - 1; j > i; j--)
        {
            node->key->at(j) = node->key->at(j - 1);
        }
        node->key->at(i) = key;
    }
    for (int j = int(node->blocks->size()) - 1; j > i; j--)
    {
        node->blocks->at(j) = node->blocks->at(j - 1);
    }
    node->blocks->at(i) = block;
    // node->key->insert(node->key->begin() + i, key);
    //     node->blocks->insert(node->blocks->begin() + i, block);
    cout << "Insert Block successful\n";
    // check for split
    bp_tree::Node* new_root = nullptr;
    //     cout << node->blocks->size() << "\n";
    //     cout << node->blocks->capacity() << "  " << node->blocks->size() << "\n";
    if (nullptr != node->blocks->at(max_degree - 1))
        new_root = node->split_node();
    //     cout << (new_root == nullptr);
    this->root_node = (nullptr == new_root ? this->root_node : new_root);
    //     if (nullptr != new_root)
    //     {
    //         cout << "tete\n";
    //         this->root_node = new_root;
    //     }
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
    while (nullptr != node->key->at(max_degree - 1))
    {
        int mid = max_degree / 2;
        bp_tree::Node* new_node = new bp_tree::Node();
        new_node->is_leaf = node->is_leaf;
        new_node->parent = node->parent;
        char* new_key = node->key->at(mid);
        if (node->is_leaf)
        {
            // connect nodes
            new_node->right = node->right;
            // check for the right end of the root list
            // root nodes do not connect head and tail
            if (nullptr != node->right)
                new_node->right->left = new_node;
            node->right = new_node;
            new_node->left = node;
            // split keys and blocks
            int i = 0;
            while (i < max_degree - mid)
            {
                new_node->key->at(i) = node->key->at(mid + i);
                node->key->at(mid + i) = nullptr;
                new_node->blocks->at(i) = node->blocks->at(mid + i);
                node->blocks->at(mid + i) = nullptr;
                i++;
            }
            new_node->blocks->at(i) = node->blocks->at(mid + i);
            node->blocks->at(mid + i) = nullptr;
        }
        else
        {
            // split keys and children
            int i = 0;
            while (i < max_degree - mid)
            {
                new_node->key->at(i) = node->key->at(mid + i);
                node->key->at(mid + i) = nullptr;
                new_node->children->at(i) = node->children->at(mid + i);
                node->children->at(mid + i) = nullptr;
                i++;
            }
            new_node->children->at(i) = node->children->at(mid + i);
            node->children->at(mid + i) = nullptr;
        }
        cout << "Split one node\n";

        if (nullptr == node->parent)
        {
            // create new root node
            bp_tree::Node* new_root = new bp_tree::Node();
            new_root->is_leaf = false;
            new_root->children->at(0) = node;
            new_root->children->at(1) = new_node;
            new_root->key->at(0) = new_key;
            node->parent = new_root;
            new_node->parent = new_root;
            cout << "Create new root node\n";
            // 更新bp tree的root_node指针
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
    int i = max_degree - 1;
    // iterate through to find an approriate place
    while (i > 0 && ((nullptr != this->key->at(i) && bp_tree::keycmp(key, this->key->at(i)) <= 0) || nullptr == this->key->at(i)))
    {
        this->key->at(i) = this->key->at(i - 1);
        this->children->at(i + 1) = this->children->at(i);
        i--;
    }
    this->key->at(i) = key;
    this->children->at(i + 1) = new_node;
    //     cout << "Insert a key\n";
}

bp_tree::Node::Node()
{
    key = new std::array<char*, max_degree>{};
    //     cout << "key size is " << key->size();
    children = new std::array<Node*, max_degree + 1>{};
    //     cout << "children size is " << children->size();
    blocks = new std::array<Block<relation>*, max_degree + 1>{};
    //     cout << "blocks size is " << blocks->size();
    parent = nullptr;
    is_leaf = true;
    //     block = nullptr;
    cout << "Create bp_node\n";
}

bp_tree::Node::~Node()
{
    cout << "Delete bp_node\n";
}
