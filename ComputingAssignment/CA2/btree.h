#ifndef btree_h
#define btree_h

#include "data.h"
#include <vector>

class Node
{
public:
    vector<relation*> key; // array of relations(key=value)
    vector<Node*> children; // array of pointers to children nodes
    vector<Node*> parent; // array of pointers to father nodes

    Node();
};

class Btree
{
public:
    int n; // order n
    Node* root;
    int compare_mode; // take what properties to compare two relations

    // valid range of key numbers
    int maxkey; // n-1
    int minkey; // [n/2]-1

    Btree(int order, int mode);
    
    void insert(relation* relation);
    void remove(relation* relation);

    void part_insert(relation* r, Node* node);
    Node* search(Node* start_node, relation* relation);
    Node* split(Node* node,int m); // 返回左半部分node，原node变为右半部分，m为分割位置，注意使用前要先保存m位置的relation
    int r_compare(relation* r1, relation* r2); // > 1, = 0, < -1
};

#endif
