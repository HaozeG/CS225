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
    Btree* btree = new Btree(3,1);
    // BPlusTree* pTree = new BPlusTree;
    Local* abc = new Local;
    Local* abc1 = new Local;
    const char* a = "testfile.txt";
    const char* b = "testfile1.txt";
    abc->readfile(a);
    abc1->readfile(b);
    //     abc->update();
    cout << "test\n";
    for (int i = 0; i < 9; i++)
    {
        if (abc->local->head->block[i] != nullptr)
        {
            cout << "ID = "<<abc->local->head->block[i]->person->id<<"\n";
            // cout << "priority = " << abc->local->head->block[i]->status->priority << "\n";
            btree->insert(abc->local->head->block[i]);
            btree->traverse();
            cout << "\n";
        }
    }
    btree->remove(abc->local->head->block[8]);
    btree->traverse();
    cout << "\n";
    // cout << "ID = "<<abc->local->head->next->block[3]->person->id<<"\n";
    // btree->insert(abc->local->head->next->block[3]);

    return 1;
}

        // (void)pTree->Insert(abc->local->head->block[3]->key(), abc->local->head);
        // (void)pTree->Insert(abc->local->head->next->block[3]->key(), abc->local->head->next);
        // (void)pTree->Insert(abc1->local->head->block[3]->key(), abc1->local->head);
        // (void)pTree->Insert(abc1->local->head->next->block[3]->key(), abc1->local->head->next);
    // }
    //     pTree->Delete(abc->local->head->block[3]->key());
    //     pTree->Delete(abc->local->head->next->block[3]->key());
    // return 0;
    // int i = 1;
    // const char* x = "3200000002";
    // //abc->local->head->bdelete(x);
    // //abc->local->merge(abc->local->head, abc->local->head->next);
    // //Block<relation>* tem = abc->local->head;
    // for (Block<relation>* tem = abc->local->head; tem != NULL; tem = tem->next)
    // { //cout<<(tem->next == NULL)<<"\n";
    //     cout << "Block" << i << "\n";
    //     i++;
    //     for (int j = 0; j < tem->length; j++)
    //     {
    //         if (tem->block[j] == NULL)
    //             continue;
    //         cout << j << "\n";
    //         cout << "relation" << j << "\n";
    //         cout << "person"
    //              << " " << tem->block[j]->person->id << " " << tem->block[j]->person->name
    //              << " " << tem->block[j]->person->birth << " " << tem->block[j]->person->age_group
    //              << " " << tem->block[j]->person->phone << " " << tem->block[j]->person->WeChat
    //              << " " << tem->block[j]->person->email << "\n";
    //         cout << "status"
    //              << " " << tem->block[j]->status->risk << " " << tem->block[j]->status->priority
    //              << " " << tem->block[j]->status->type << "\n";
    //         cout << "registration"
    //              << " " << tem->block[j]->registration->timestamp << "\n";
    //         cout << "treatment"
    //              << " " << tem->block[j]->treatment->time << " " << tem->block[j]->treatment->hospital_id << "\n";
    //         cout << "\n";
    //     }
    //     //if (tem->retrieval(x) != NULL)
    //     //cout<<"\n"<<tem->retrieval(x)->person->id<<"\n";
    // }

    //char* c = new char [10];int i = 3201; sprintf(c,"%d",i);
    //sprintf(c, "%d.bmp", i);
    //for (int i = 0; i < ; i++)
    //cout<<c<<"\n";
    //const char* b = "3202";
    //if (strcmp(c,b) < 0)
    //cout<<strcmp(c,b)<<"\n";
    //const char* a = new char [10];
    //strcpy(a,b);
    //cout<<a<<"\n";
    // return 0;
// }
