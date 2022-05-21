#ifndef btree_h
#define btree_h

#include "data.h"
#include <vector>
using namespace std;

class Btreebase
{
public:
    int n = 3; // order
    int maxkey = 2; // n-1
    int minkey = 1; // [n/2]-1
    int compare_mode = 1;
    int r_compare(relation* r1, relation* r2); // > 1, = 0, < -1
};

class Node : public Btreebase
{
public:
    vector<relation*> key; // array of relations(key=value)
    vector<Node*> children; // array of pointers to children nodes
    vector<Node*> parent; // array of pointers to father nodes

    // Node();
    int findKey(relation* r);
    void deletion(relation* r);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    relation* getPredecessor(int idx);
    relation* getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    void traverse();
    friend class Btree;
};

class Btree : public Btreebase
{
public:
    // int n; // order n
    Node* root;
    // int compare_mode; // take what properties to compare two relations

    // valid range of key numbers
    // int maxkey; // n-1
    // int minkey; // [n/2]-1

    Btree(int order);

    void insert(relation* relation);
    void remove(relation* relation);
    void update(relation* r1, relation* r2);
    void traverse();

    void part_insert(relation* r, Node* node);
    Node* search(Node* start_node, relation* relation);
    Node* split(Node* node, int m); // 返回左半部分node，原node变为右半部分，m为分割位置，注意使用前要先保存m位置的relation
    // int r_compare(relation* r1, relation* r2); // > 1, = 0, < -1
};

// Node::Node(){};

#endif
