#ifndef b_tree_h
#define b_tree_h

// TODO: 用vector
#include <vector>
#include "data.h"

// TODO: 调整Fibonacci Tree的namespace
namespace bp_tree
{
    template<class T>
    class Node
    {
    public:
        Node();
        ~Node();

        std::vector<char*> key;
        std::vector<bp_tree::Node<T>*> children;
        // Block*
        bp_tree::Node<T>* parent;
        bool is_leaf;
    };

    template<class T>
    class Tree
    {
    public:
        Tree();
        ~Tree();

        int insert_node(T key);
        int delete_node(T key);
        int find_node(T key);

    private:
        // int degree;
        bp_tree::Node<T>* root_node;
    };
}

#endif
