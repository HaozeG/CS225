#ifndef b_tree_h
#define b_tree_h

// TODO: 用vector
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

        std::vector<char*> key;
        std::vector<bp_tree::Node*> children;
        bp_tree::Node* parent;
        bool is_leaf;
        // for leaf node, pointing to the block
        Block* block;
    };

    class Tree
    {
    public:
        Tree();
        ~Tree();

        int insert_node(char* key);
        int delete_node(char* key);
        bp_tree::Node* find_node(char* key);
        int keycmp(bp_tree::Node* node1, bp_tree::Node* node2);

    private:
        int max_degree;
        bp_tree::Node* root_node;
    };
}

#endif
