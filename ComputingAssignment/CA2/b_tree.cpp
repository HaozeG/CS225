#include "b_tree.h"
#include <iostream>
#include <stdio.h>
#include <vector>
using std::cin;
using std::cout;

template<class T>
b_tree::Tree<T>::Tree()
{
    root_node = new b_tree::Node<T>;
    cout << "Create b_tree\n";
}

template<class T>
int b_tree::Tree<T>::find_node(T key)
{
    b_tree::Node<T>* node = root_node;
    while (nullptr != node)
    {
    }
    return 1;
}

template<class T>
b_tree::Node<T>::Node()
{
    key = std::vector<Data*>();
    children = std::vector<Node<T>*>();
    parent = nullptr;
    is_leaf = true;
    cout << "Create node\n";
}
