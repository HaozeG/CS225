#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include "data.h"
#include "timeoffset.h"
#include "btree.h"
using std::cin;
using std::cout;
long timeoffset = 0;

int main()
{
    Btree* btree = new Btree(3);
    // BPlusTree* pTree = new BPlusTree;
    Local* abc = new Local;
    Local* abc1 = new Local;
    const char* a = "testfile.txt";
    const char* b = "testfile1.txt";
    abc->readfile(a);
    abc1->readfile(b);
    //     abc->update();
    cout << "test\n";
    for (int i = 4; i < 7; i++)
    {
        if (abc->local->head->block[i] != nullptr)
        {
            cout << "ID = "<<abc->local->head->block[i]->person->id<<"\n";
            // cout << "priority = " << abc->local->head->block[i]->status->priority << "\n";
            btree->insert(abc->local->head->block[i]);
            // cout << "root children number = " << btree->root->children.size() << "\n";
            btree->traverse();
            cout << "\n";
        }
    }
    // insert 8
    cout << "ID = "<<abc->local->head->block[3]->person->id<<"\n";
    // cout << "priority = " << abc->local->head->block[i]->status->priority << "\n";
    btree->insert(abc->local->head->block[3]);
    // cout << "root children number = " << btree->root->children.size() << "\n";
    btree->traverse();
    cout << "\n";

    // insert 15
    cout << "ID = "<<abc->local->head->block[7]->person->id<<"\n";
    // cout << "priority = " << abc->local->head->block[i]->status->priority << "\n";
    btree->insert(abc->local->head->block[7]);
    // cout << "root children number = " << btree->root->children.size() << "\n";
    btree->traverse();
    cout << "\n";

    // insert 20
    cout << "ID = "<<abc->local->head->block[8]->person->id<<"\n";
    // cout << "priority = " << abc->local->head->block[i]->status->priority << "\n";
    btree->insert(abc->local->head->block[8]);
    // cout << "root children number = " << btree->root->children.size() << "\n";
    btree->traverse();
    cout << "\n";

    // cout << "root children number = " << btree->root->children.size() << "\n";
    // cout << "remove key = " << abc->local->head->block[8]->status->priority << "\n";
    // btree->remove(abc->local->head->block[8]);
    // btree->traverse();
    // cout << "\n";
    cout << "remove key = " << abc->local->head->block[6]->status->priority << "\n";
    btree->remove(abc->local->head->block[6]);
    btree->traverse();
    cout << "\n";
    // cout << "root children number = " << btree->root->children.size() << "\n";
    // cout << "remove key = " << abc->local->head->block[4]->status->priority << "\n";
    // btree->remove(abc->local->head->block[4]);
    // btree->traverse();
    // cout << "\n";
    // cout << "root children number = " << btree->root->children.size() << "\n";

    return 1;
}


