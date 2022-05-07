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
    root_node->is_leaf = true;
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

// TODO: 实现方式上，是插入block还是插入relation
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
    if (nullptr != node->blocks->at(node->key->size()) || i != node->key->size())
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
    if (nullptr != node->blocks->at(max_degree))
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
    if (nullptr != this->key->at(i) && bp_tree::keycmp(key, this->key->at(i)) > 0)
    {
        i++;
    }
    this->key->at(i) = key;
    this->children->at(i + 1) = new_node;
    //     cout << "Insert a key\n";
}

void bp_tree::Tree::remove(char* key, Block<relation>* block)
{
    if (nullptr == this->root_node)
    {
        cout << "B+ tree already empty\n";
        return;
    }
    bp_tree::Node* node = search_node(this->root_node, key);
    bp_tree::Node* p = node;
    // find exact place
    int i = 0;
    while (i < max_degree + 1 && nullptr != node->blocks->at(i))
    {
        if (block == node->blocks->at(i))
            break;
        i++;
    }
    // remove key and block in root node
    // remove/update key in internal node
    if (max_degree == i || nullptr == node->blocks->at(i + 1))
    {
        char* old_key;
        char* new_key;
        if (max_degree != i && nullptr != node->key->at(i))
        {
            // block number == key number
            old_key = node->key->at(i);
            new_key = node->key->at(i - 1);
            node->key->at(i) = nullptr;
        }
        else
        {
            old_key = node->key->at(i - 1);
            new_key = node->key->at(i - 2);
            node->key->at(i - 1) = nullptr;
        }
        node->blocks->at(i) = nullptr;
        // update key
        if (nullptr != node->parent)
            update_key(old_key, node->key->at(max_degree - 2), node->parent);
    }
    else
    {
        if (0 == i)
        {
            // the removal of key[0] will cause key change for internal nodes
            // update key
            update_key(node->key->at(0), node->key->at(1), node->parent);
        }
        // shift left
        while (i < max_degree - 1)
        {
            node->blocks->at(i) = node->blocks->at(i + 1);
            node->key->at(i) = node->key->at(i + 1);
            i++;
        }
        // TODO: check all shifting left
        // fill with nullptr after shifting left
        node->key->at(i) = nullptr;
        node->blocks->at(i) = node->blocks->at(i + 1);
        node->blocks->at(i + 1) = nullptr;
    }

    // check this leaf node for merge
    int min = max_degree / 2;
    if (nullptr == node->key->at(min))
    {
        // implement the merge of leaf node
        if (nullptr == node->parent && nullptr == node->left && nullptr == node->right)
        {
            // the only node in B+ tree
            return;
        }
        // check for left/right siblings
        bool LEFT = (nullptr != node->left && node->left->parent == node->parent);
        bool RIGHT = (nullptr != node->right && node->right->parent == node->parent);
        char* old_key;
        char* new_key;
        if (LEFT)
        {
            if (node->left->count_key() + node->count_key() > max_degree)
            {
                // TODO: check old_key
                // steal from left sibling
                int n = node->count_key();
                old_key = node->left->key->at(n);
                // node->parent->remove_key(node->key->at(0));
                // shift right
                node->blocks->at(n + 1) = node->blocks->at(n);
                while (n > 0)
                {
                    node->blocks->at(n) = node->blocks->at(n - 1);
                    node->key->at(n) = node->key->at(n - 1);
                    n--;
                }
                n = node->left->count_key();
                new_key = node->left->key->at(n - 1);
                node->left->key->at(n - 1) = nullptr;
                node->key->at(0) = new_key;
                n = node->left->count_blocks();
                node->blocks->at(0) = node->left->blocks->at(n - 1);
                node->left->blocks->at(n - 1) = nullptr;
                update_key(old_key, new_key, node->parent);
            }
            else
            {
                // merge
                int n = node->left->count_key();
                if (node->left->count_key() != node->left->count_blocks())
                {
                    // insert one key to prevent destroying branching rules
                    node->left->key->at(n) = node->blocks->at(0)->block[3]->key();
                    n++;
                }
                int i = 0;
                // copy to left node
                while (nullptr != node->key->at(i))
                {
                    node->left->key->at(n + i) = node->key->at(i);
                    i++;
                }
                n = node->count_blocks();
                i = 0;
                while (nullptr != node->blocks->at(i))
                {
                    node->left->blocks->at(n + i) = node->blocks->at(i);
                    i++;
                }
                if (nullptr != node->parent)
                {
                    int i = 0;
                    while (i < max_degree + 1)
                    {
                        if (node == node->parent->children->at(i))
                            break;
                        i++;
                    }
                    while (i < max_degree + 1)
                    {
                        node->parent->children->at(i) = node->parent->children->at(i + 1);
                        node->parent->key->at(i - 1) = node->parent->key->at(i);
                        i++;
                    }
                }
                // reconnect leaf nodes
                node->left->right = node->right;
                if (nullptr != node->right)
                    node->right->left = node->left;
            }
        }
        else if (RIGHT)
        {
            if (node->right->count_key() + node->count_key() > max_degree)
            {
                // steal from right sibling
                old_key = node->right->key->at(0);
                new_key = node->right->key->at(1);
                Block<relation>* new_block = node->right->blocks->at(0);
                int n = node->right->count_key();
                // shift left
                int i = 0;
                while (i < n)
                {
                    node->right->blocks->at(i) = node->right->blocks->at(i + 1);
                    node->right->key->at(i) = node->right->key->at(i + 1);
                    i++;
                }
                node->right->key->at(i) = nullptr;
                node->blocks->at(i) = node->blocks->at(i + 1);
                node->blocks->at(i + 1) = nullptr;

                n = node->count_key();
                node->key->at(n) = new_key;
                n = node->count_blocks();
                node->blocks->at(n) = new_block;
                update_key(old_key, new_key, node->parent);
            }
            else
            {
                // merge
                int n = node->count_blocks();
                int i = node->right->count_key();
                // int j = node->right->count_blocks();
                // shift right n places
                node->right->blocks->at(i + n) = node->right->blocks->at(i);
                while (i > 0)
                {
                    node->right->blocks->at(i + n - 1) = node->right->blocks->at(i - 1);
                    node->right->key->at(i + n - 1) = node->right->key->at(i - 1);
                    i--;
                }
                if (n != node->count_key())
                {
                    // insert one key to prevent destroying branching rules
                    node->right->key->at(n - 1) = node->blocks->at(n - 1)->block[3]->key();
                }
                // copy to right node
                while (n > 0)
                {
                    node->right->key->at(n - 1) = node->key->at(n - 1);
                    node->right->blocks->at(n - 1) = node->blocks->at(n - 1);
                    n--;
                }
                // remove empty node pointer
                if (nullptr != node->parent)
                {
                    int i = 0;
                    while (i < max_degree + 1)
                    {
                        if (node == node->parent->children->at(i))
                            break;
                        i++;
                    }
                    while (i < max_degree + 1)
                    {
                        node->parent->children->at(i) = node->parent->children->at(i + 1);
                        node->parent->key->at(i - 1) = node->parent->key->at(i);
                        i++;
                    }
                }
                // reconnect leaf nodes
                node->left->right = node->right;
                if (nullptr != node->right)
                    node->right->left = node->left;
            }
        }
        else
        {
            // TODO: check with this meaning
            cout << "not sure\n";
            //     return;
        }
        // recursively merge
        // node->parent->merge_node();
        //
    }
    else
    {
        // no need to merge
        return;
    }
}
// // steal
// // update key in internal nodes if the number of nodes does not change
// update_key(old_key, new_key, node->parent);
// // merge
// // check for all parent nodes if the merge of leaf nodes occurs
// node = node->parent;
// while (nullptr != node && nullptr != node->merge_node())
//     node = node->parent;
// return;

// count the number of keys
int bp_tree::Node::count_blocks()
{
    //     int i = 0;
    //     while (i < max_degree && nullptr != this->blocks->at(i))
    //         i++;
    return this->blocks->size();
}

// count the number of keys
int bp_tree::Node::count_key()
{
    //     int i = 0;
    //     while (i < max_degree && nullptr != this->key->at(i))
    // i++;
    return this->key->size();
}

// recursively update key starting at node
void bp_tree::Tree::update_key(char* old_key, char* new_key, bp_tree::Node* node)
{
    while (nullptr != node)
    {
        int i = 0;
        while (i < max_degree && nullptr != node->key->at(i))
        {
            if (0 == keycmp(old_key, node->key->at(i)))
            {
                node->key->at(i) = new_key;
                cout << "Key updated: " << old_key << " -> " << new_key << "\n";
                return update_key(old_key, new_key, node->parent);
            }
            i++;
        }
        node = node->parent;
    }
    return;
}

/*
// implement the merge of internal node
bp_tree::Node* bp_tree::Node::merge_node()
{
    bp_tree::Node* node = this;

    if (node->parent != nullptr)
    {
    }
    // check this leaf node for merge
    int min = max_degree / 2;
    if (nullptr == node->key->at(min))
    {
        // implement the merge of leaf node
        if (nullptr == node->parent && nullptr == node->left && nullptr == node->right)
        {
            // the only node in B+ tree
            return;
        }
        // check for left/right siblings
        bool LEFT = (nullptr != node->left && node->left->parent == node->parent);
        bool RIGHT = (nullptr != node->right && node->right->parent == node->parent);
        char* old_key;
        char* new_key;
        if (LEFT)
        {
            if (node->left->count_key() + node->count_key() > max_degree)
            {
                // TODO: check old_key
                // steal from left sibling
                int n = node->count_key();
                old_key = node->left->key->at(n);
                // node->parent->remove_key(node->key->at(0));
                // shift right
                node->blocks->at(n + 1) = node->blocks->at(n);
                while (n > 0)
                {
                    node->blocks->at(n) = node->blocks->at(n - 1);
                    node->key->at(n) = node->key->at(n - 1);
                    n--;
                }
                n = node->left->count_key();
                new_key = node->left->key->at(n - 1);
                node->left->key->at(n - 1) = nullptr;
                node->key->at(0) = new_key;
                n = node->left->count_blocks();
                node->blocks->at(0) = node->left->blocks->at(n - 1);
                node->left->blocks->at(n - 1) = nullptr;
                update_key(old_key, new_key, node->parent);
            }
            else
            {
                // merge
                int n = node->left->count_key();
                if (node->left->count_key() != node->left->count_blocks())
                {
                    // insert one key to prevent destroying branching rules
                    node->left->key->at(n) = node->blocks->at(0)->block[3]->key();
                    n++;
                }
                int i = 0;
                // copy to left node
                while (nullptr != node->key->at(i))
                {
                    node->left->key->at(n + i) = node->key->at(i);
                    i++;
                }
                n = node->count_blocks();
                i = 0;
                while (nullptr != node->blocks->at(i))
                {
                    node->left->blocks->at(n + i) = node->blocks->at(i);
                    i++;
                }
                if (nullptr != node->parent)
                {
                    int i = 0;
                    while (i < max_degree + 1)
                    {
                        if (node == node->parent->children->at(i))
                            break;
                        i++;
                    }
                    while (i < max_degree + 1)
                    {
                        node->parent->children->at(i) = node->parent->children->at(i + 1);
                        node->parent->key->at(i - 1) = node->parent->key->at(i);
                        i++;
                    }
                }
                // reconnect leaf nodes
                node->left->right = node->right;
                if (nullptr != node->right)
                    node->right->left = node->left;
            }
        }
        else if (RIGHT)
        {
            if (node->right->count_key() + node->count_key() > max_degree)
            {
                // steal from right sibling
                old_key = node->right->key->at(0);
                new_key = node->right->key->at(1);
                Block<relation>* new_block = node->right->blocks->at(0);
                int n = node->right->count_key();
                // shift left
                int i = 0;
                while (i < n)
                {
                    node->right->blocks->at(i) = node->right->blocks->at(i + 1);
                    node->right->key->at(i) = node->right->key->at(i + 1);
                    i++;
                }
                node->right->key->at(i) = nullptr;
                node->blocks->at(i) = node->blocks->at(i + 1);
                node->blocks->at(i + 1) = nullptr;

                n = node->count_key();
                node->key->at(n) = new_key;
                n = node->count_blocks();
                node->blocks->at(n) = new_block;
                update_key(old_key, new_key, node->parent);
            }
            else
            {
                // merge
                int n = node->count_blocks();
                int i = node->right->count_key();
                // int j = node->right->count_blocks();
                // shift right n places
                node->right->blocks->at(i + n) = node->right->blocks->at(i);
                while (i > 0)
                {
                    node->right->blocks->at(i + n - 1) = node->right->blocks->at(i - 1);
                    node->right->key->at(i + n - 1) = node->right->key->at(i - 1);
                    i--;
                }
                if (n != node->count_key())
                {
                    // insert one key to prevent destroying branching rules
                    node->right->key->at(n - 1) = node->blocks->at(n - 1)->block[3]->key();
                }
                // copy to right node
                while (n > 0)
                {
                    node->right->key->at(n - 1) = node->key->at(n - 1);
                    node->right->blocks->at(n - 1) = node->blocks->at(n - 1);
                    n--;
                }
                // remove empty node pointer
                if (nullptr != node->parent)
                {
                    int i = 0;
                    while (i < max_degree + 1)
                    {
                        if (node == node->parent->children->at(i))
                            break;
                        i++;
                    }
                    while (i < max_degree + 1)
                    {
                        node->parent->children->at(i) = node->parent->children->at(i + 1);
                        node->parent->key->at(i - 1) = node->parent->key->at(i);
                        i++;
                    }
                }
                // reconnect leaf nodes
                node->left->right = node->right;
                if (nullptr != node->right)
                    node->right->left = node->left;
            }
        }
        else
        {
            // TODO: check with this meaning
            cout << "not sure\n";
            //     return;
        }
    }
    // case for root node
    //
    //
    // steal from left

    // steal from right

    // merge to one node

    return nullptr;
}
*/

// recursively find the key to delete
void bp_tree::Node::remove_key(char* key)
{
    int i = 0;
    while (i < max_degree && nullptr != this->key->at(i) && 0 != keycmp(key, this->key->at(i)))
        i++;
    if (i == max_degree || nullptr == this->key->at(i))
    {
        // not found in this node
        if (nullptr != this->parent)
        {
            this->parent->remove_key(key);
            return;
        }
        else
        {
            cout << "Key " << key << " not found\n";
            return;
        }
    }
    else
    {
        // key found in this node
        // shift left
        // TODO: childrens??
        while (i < max_degree)
        {
            this->key->at(i - 1) = this->key->at(i);
            this->key->at(i) = nullptr;
            i++;
        }
        // check if need to merge
        if (nullptr == this->merge_node())
        {
            // number of nodes does not change
            return;
        }
        else
        {
            // number of nodes decreases
            bp_tree::Node* node = this->parent;
            // check all parent nodes
            while (nullptr != node && nullptr != node->merge_node())
                node = node->parent;
            return;
        }
    }
}

bp_tree::Node* bp_tree::Node::merge_node()
{
    return nullptr;
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
