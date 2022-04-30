#include "bp_tree.h"
#include "data.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <vector>
using std::cin;
using std::cout;

bp_tree::Tree::Tree()
{
    root_node = new bp_tree::Node;
    max_degree = 3;
    cout << "Create bp_tree\n";
}

bp_tree::Node* bp_tree::Tree::find_node(char* key)
{
    bp_tree::Node* node = root_node;
    while (!node->is_leaf)
        node = node->children.at(0);
}

bp_tree::Node::Node()
{
    key = std::vector<char*>();
    children = std::vector<Node*>();
    parent = nullptr;
    is_leaf = true;
    block = nullptr;
    cout << "Create node\n";
}
