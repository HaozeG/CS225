#ifndef b_tree_h
#define b_tree_h

#include <array>
#include "data.h"
const int max_degree = 3;

// TODO: 调整Fibonacci Tree的namespace
namespace bp_tree
{
    class Node
    {
    public:
        Node();
        ~Node();

        // leave 1 extra space for split
        std::array<char*, max_degree>* key; // max_degree
        std::array<bp_tree::Node*, max_degree + 1>* children; // max_degree + 1
        // for leaf node, store pointers to blocks
        std::array<Block<relation>*, max_degree + 1>* blocks; // max_degree + 1
        bp_tree::Node* parent;
        bp_tree::Node* left;
        bp_tree::Node* right;
        bool is_leaf;

        void insert_key(char* key, bp_tree::Node* new_node);
        bp_tree::Node* split_node();
        void remove_key(char* key);
        bp_tree::Node* merge_node();
        int count_key();
        int count_blocks();
        // int merge_node();
    };

    class Tree
    {
    public:
        Tree();
        ~Tree();

        bp_tree::Node* root_node;

        bp_tree::Node* search_node(bp_tree::Node* root_node, char* key); // return certain block that can store the key
        void insert(char* key, Block<relation>* block);
        void remove(char* key, Block<relation>* block);
        void update_key(char* old_key, char* new_key, bp_tree::Node* node);

        // int delete_node(char* key);
        void display(bp_tree::Node* root);
        // void linear_print();
    };
    int keycmp(char* key1, char* key2);
}

#endif
