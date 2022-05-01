#ifndef b_tree_h
#define b_tree_h

#include <vector>
#include "data.h"

// TODO: 调整Fibonacci Tree的namespace
namespace bp_tree
{
    class Node
    {
    public:
        Node();
        ~Node();

        // leaf 1 extra space for split
        std::vector<char*> key; // mex_degree
        std::vector<bp_tree::Node*> children; // max_degree + 1
        // for leaf node, store pointers to blocks
        std::vector<Block<relation>*> blocks; // max_degree + 1
        bp_tree::Node* parent;
        bp_tree::Node* left;
        bp_tree::Node* right;
        bool is_leaf;

        void insert_key(char* key, bp_tree::Node* new_node);
        bp_tree::Node* split_node();
        // int merge_node();

    private:
        int max_degree;
    };

    class Tree
    {
    public:
        Tree();
        ~Tree();

        bp_tree::Node* root_node;

        bp_tree::Node* search_node(bp_tree::Node* node, char* key); // return certain block that can store the key
        void insert(char* key, Block<relation>* block);

        // int delete_node(char* key);
        void display(bp_tree::Node* root);
        // void linear_print();
    };
    int keycmp(char* key1, char* key2);
}

#endif
