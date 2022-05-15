// #include <stdio.h>
#include <cstring>
#include <iostream>
#include "data.h"
#include "timeoffset.h"
#include "fibonacci_heap.h"
#include "BPlusTree.h"
// #include "base.cpp"
// #include "appoint.cpp"
#include <vector>
#include "report.h"
using std::cin;
using std::cout;
long timeoffset = 0;
long timestart = 20220401;

bool is_included(vector<relation*>* list, relation* key)
{
    vector<relation*>::iterator it;
    for (it = list->begin(); it != list->end(); it++)
    {
        if (0 == strcmp(key->key(), (*it)->key()))
            return true;
    }
    return false;
}

int main()
{
    int op = -1;
    Local* local[2];
    local[0] = new Local;
    local[1] = new Local; // cout << "Create new local"
    fibonacci::Heap* h[3];
    h[0] = new fibonacci::Heap;
    h[0]->type = 0;
    h[1] = new fibonacci::Heap;
    h[1]->type = 1;
    h[2] = new fibonacci::Heap;
    h[2]->type = 2;
    BPlusTree* bpTree = new BPlusTree;
    blist<relation>* central = new blist<relation>; // central
    vector<relation*>* withdrawn_list = new vector<relation*>; // list that stores withdrawn records
    //     Alist alist;
    //     Hlist hlist;
    //     Hospital hospital1(100, 100, 1), hospital2(500, 500, 1);
    //     hlist.addh(&hospital1);
    //     hlist.addh(&hospital2);
    do
    {
        cout << "---NEW DAY---\n";
        // our system time
        cout << "TODAY IS " << timestart + int(int(timeoffset / 24) / 30) * 100 + (int(timeoffset / 24) - 30 * int(int(timeoffset / 24) / 30)) << "\n";
        cout << "-------------\n";
        do
        {
            cout << "Choose an operation:\n";
            cout << "0: QUIT\n";
            cout << "1: do registration to local\n";
            cout << "2: update registry to central\n";
            cout << "3: present priority letter\n";
            cout << "4: withdraw\n";
            cout << "5: make appointments\n";
            cout << "6: manual reporting\n";
            cout << "7: GO TO NEXT DAY\n";
            cout << "8: print information about heap\n";
            cout << "9: print information about B+ tree\n";
            cout << "10: print information about blocks\n";
            cin >> op;
        } while (op < 0 && op > 10);
        switch (op)
        {
        case 0:
        {
            // destroy before exit
            delete central;
            delete h[0];
            delete h[1];
            delete h[2];
            delete bpTree;
            return 0;
        }
        case 1:
        {
            int f = -1;
            char* c = new char[30];
            cout << "Specify the name of the input file:\n";
            cin >> c;
            const char* filename = c;
            do
            {
                cout << "Choose one local registry from 1 to 2:\n";
                cin >> f;
            } while (f < 1 && f > 2);
            local[f - 1]->readfile(filename);
            cout << "Data stored: \n";
            // print
            int i = 1;
            for (Block<relation>* tem = local[f - 1]->local->head; tem != NULL; tem = tem->next)
            { //cout<<(tem->next == NULL)<<"\n";
                cout << "Block" << i << "\n";
                i++;
                for (int j = 0; j < tem->length; j++)
                {
                    if (tem->block[j] == NULL)
                        continue;
                    cout << j << "\n";
                    cout << "relation" << j << "\n";
                    cout << "person"
                         << " " << tem->block[j]->person->id << " " << tem->block[j]->person->name
                         << " " << tem->block[j]->person->birth << " " << tem->block[j]->person->age_group
                         << " " << tem->block[j]->person->phone << " " << tem->block[j]->person->WeChat
                         << " " << tem->block[j]->person->email << "\n";
                    cout << "status"
                         << " " << tem->block[j]->status->risk << " " << tem->block[j]->status->priority
                         << " " << tem->block[j]->status->type << "\n";
                    cout << "registration"
                         << " " << tem->block[j]->registration->timestamp << "\n";
                    cout << "treatment"
                         << " " << tem->block[j]->treatment->time << " " << tem->block[j]->treatment->hospital_id << "\n";
                    cout << "\n";
                }
            }
            break;
        }
        case 2:
        {
            for (int l = 0; l < 2; l++)
            {
                Block<relation>* pt = local[l]->local->head;
                while (pt != nullptr)
                {
                    // iterate through each block
                    for (int i = 0; i < pt->length; i++)
                    {
                        relation* insert_ptr = pt->block[i];
                        if (nullptr == insert_ptr)
                            continue;
                        if (is_included(withdrawn_list, insert_ptr))
                            insert_ptr->appoint->withdrawn = true;
                        if (bpTree->SearchExistence(insert_ptr->key()))
                        {
                            //     update
                            Block<relation>* target_block = bpTree->SearchData(insert_ptr->key());
                            int j = 0;
                            for (j = 0; j < target_block->length; j++)
                            {
                                if (nullptr != target_block->block[j] && (0 == strcmp(target_block->block[j]->key(), insert_ptr->key())))
                                    break;
                            }
                            insert_ptr->f_node = target_block->block[j]->f_node;
                            target_block->block[j] = insert_ptr;
                            h[insert_ptr->status->type]->update(*(insert_ptr->f_node));
                        }
                        else
                        {
                            //     newly added
                            if (nullptr == bpTree->GetRoot())
                            {
                                // initialize central
                                central->head = new Block<relation>;
                                central->head->insert(insert_ptr);
                                bpTree->Insert(insert_ptr->key(), central->head);
                            }
                            else
                            {
                                Block<relation>* target_block = bpTree->SearchInsertPos(insert_ptr->key());
                                if (nullptr != target_block)
                                {
                                    Block<relation>* split_block = target_block->insert(insert_ptr);
                                    // if split happened
                                    if (nullptr != split_block)
                                    {
                                        bpTree->Insert(split_block->block[split_block->overblock]->key(), split_block);
                                    }
                                }
                                else
                                {
                                    // insert to the last block
                                    Block<relation>* new_block = new Block<relation>;
                                    new_block->insert(pt->block[i]);
                                    // connect to list
                                    Block<relation>* new_position = central->head;
                                    while (new_position != nullptr && new_position->next != nullptr)
                                        new_position = new_position->next;
                                    new_position->next = new_block;
                                    new_block->prev = new_position;
                                    bpTree->Insert(pt->block[i]->key(), new_block);
                                }
                            }
                            // insert to fibonacci heap based on treatment type
                            h[insert_ptr->status->type]->insert(insert_ptr);
                        }
                    }
                    pt = pt->next;
                }
                // clear local data
                local[l]->local->head = nullptr;
            }
            cout << "Collect information from all local registries\n";
            break;
        }
        case 3:
        {
            // priority letter
            char a[10];
            bool flag = false;
            char str[9];
            int ddl = 0;
            cout << "Enter an ID to present priority letter:\n";
            cin >> a;
            cout << "Enter a deadline (Format: YYYYMMDD):\n";
            cin >> str;
            str[8] = '\0';
            ddl = (atoi(str) - timestart) * 24;

            // search blist to find relation data with certain id
            Block<relation>* pBlock = bpTree->SearchData(a);
            relation* ptr = nullptr;
            if (nullptr != pBlock)
            {
                cout << a << "\n";
                ptr = pBlock->retrieval(a);
            }
            if (nullptr != ptr)
            {
                ptr->status->priority = ddl;
                cout << ptr->person->name << "=>priority letter presented\n";
            }
            else
            {
                cout << "ID not found\n";
            }
            break;
        }
        case 4:
        {
            char a[10];
            bool flag = false;
            cout << "Enter an ID to withdraw:\n";
            cin >> a;

            // search blist to find relation data with certain id
            Block<relation>* pBlock = bpTree->SearchData(a);
            relation* ptr = nullptr;
            if (nullptr != pBlock)
                ptr = pBlock->retrieval(a);
            //     withdraw that data
            if (nullptr != ptr)
            {
                ptr->appoint->withdrawn = true;
                // TODO: if判断是否在Fibonacci heap中，判断alist和heap的delete操作
                if (nullptr != ptr->f_node)
                    h[ptr->status->type]->delete_node(*(ptr->f_node));
                withdrawn_list->push_back(ptr);
                char* key_delete = pBlock->bdelete(a);
                if (nullptr != key_delete)
                    bpTree->Delete(key_delete);
                cout << ptr->key() << " withdrawn"
                     << "\n";
            }
            else
            {
                cout << "ID not found\n";
            }

            break;
        }
        case 5:
        {
            //     check for priority letter
            Block<relation>* p = central->head;
            while (nullptr != p)
            {
                for (int i = 0; i < p->length; i++)
                {
                    if (nullptr == p->block[i])
                        continue;
                    // people with priority letter will receive appointment if it is <= 48 hours before the deadline
                    if ((p->block[i]->status->priority - timeoffset) <= 48 && -1 != p->block[i]->status->priority)
                    {
                        relation* new_data = new relation;
                        new_data->person->name = p->block[i]->person->name;
                        if (0 == p->block[i]->status->type)
                        {
                            new_data->person->profession = -1;
                            new_data->status->risk = 0;
                        }
                        else if (1 == p->block[i]->status->type)
                        {
                            new_data->person->profession = -1;
                            new_data->status->risk = 0;
                        }
                        else
                        {
                            new_data->person->profession = 2;
                            new_data->status->risk = 0;
                        }
                        p->block[i]->f_node->data = new_data;

                        // call decrease and delete_min
                        h[p->block[i]->status->type]->update(*p->block[i]->f_node);
                        p->block[i]->f_node->data = p->block[i];
                        delete new_data;
                    }
                }
                p = p->next;
            }

            //     // input hospital information
            //     cout << "tot_capacity = " << hlist.tot_capacity << "\n";

            //     bool available = false;
            //     cout << "alist.numitems = " << alist.numitems << "\n";
            //     available = (alist.numitems < hlist.tot_capacity ? true : false);
            //     while (available && h->n != 0)
            //     {
            //         alist.appoint(h, hlist);
            //         available = (alist.numitems < hlist.tot_capacity ? true : false);
            //         cout << "alist.numitems = " << alist.numitems << "\n";
            break;
        }
        case 6:
        {
            char c = 'a';
            do
            {
                cout << "w for weekly report; m for monthly report\n";
                cin >> c;
            } while (c != 'w' && c != 'm');
            switch (c)
            {
            case ('w'):
            {
                Report_system report;
                report.Open_file(central, timeoffset);
                break;
            }
            case ('m'):
            {
                Report_system report;
                report.Month(central, timeoffset);
            }
            }
            break;
        }
        case 7:
        {
            //     hlist.treat_done();
            //     alist.clear();

            timeoffset += 24; // +24h
            if ((timeoffset / 24) % 7 == 0 && 0 != timeoffset)
            {
                Report_system report;
                report.Open_file(central, timeoffset);
            }
            if ((timeoffset / 24) % 30 == 0 && 0 != timeoffset)
            {
                Report_system report;
                report.Month(central, timeoffset);
            }
            //     system("clear");
            break;
        }
        case 8:
        {
            for (int i = 0; i < 3; i++)
            {
                cout << "Fibonacci heap " << i << "\n";
                // print heap
                if (nullptr == h[i]->highest)
                {
                    cout << "Heap already empty!\n";
                    continue;
                }
                cout << "Number of nodes: " << h[i]->n << "\n";
                fibonacci::Node* p = h[i]->highest->left;
                fibonacci::Node* q = h[i]->highest->left;
                // cout << p->left->data->name << "\n";
                // cout << p->data->name << "\n";
                // cout << h->highest->right->data->name << "\n";
                cout << "Name of highest:\n"
                     << h[i]->highest->data->person->name << "\n";
                cout << "Names in root list:\n";
                // int j = 0;
                while (p != h[i]->highest)
                {
                    cout << p->data->person->name << "->\n";
                    p = p->left;
                    q = q->left->left;
                    if (p == q)
                        break;
                }
                cout << p->data->person->name << "\n";
            }
            break;
        }
        case 9:
        {
            bpTree->PrintTree();
            break;
        }
        case 10:
        {
            // print
            int i = 1;
            //     const char* x = "3200000002";
            //abc->local->head->bdelete(x);
            //abc->local->merge(abc->local->head, abc->local->head->next);
            //Block<relation>* tem = abc->local->head;
            for (Block<relation>* tem = central->head; tem != NULL; tem = tem->next)
            { //cout<<(tem->next == NULL)<<"\n";
                cout << "Block" << i << "\n";
                i++;
                for (int j = 0; j < tem->length; j++)
                {
                    if (tem->block[j] == NULL)
                        continue;
                    cout << j << "\n";
                    cout << "relation" << j << "\n";
                    cout << "person"
                         << " " << tem->block[j]->person->id << " " << tem->block[j]->person->name
                         << " " << tem->block[j]->person->birth << " " << tem->block[j]->person->age_group
                         << " " << tem->block[j]->person->phone << " " << tem->block[j]->person->WeChat
                         << " " << tem->block[j]->person->email << "\n";
                    cout << "status"
                         << " " << tem->block[j]->status->risk << " " << tem->block[j]->status->priority
                         << " " << tem->block[j]->status->type << "\n";
                    cout << "registration"
                         << " " << tem->block[j]->registration->timestamp << "\n";
                    cout << "treatment"
                         << " " << tem->block[j]->treatment->time << " " << tem->block[j]->treatment->hospital_id << "\n";
                    cout << "\n";
                }
                //if (tem->retrieval(x) != NULL)
                //cout<<"\n"<<tem->retrieval(x)->person->id<<"\n";
            }
            break;
        }
        }
    } while (op != 0);
    return 0;
}

// above is the basic structure for main program

/*
    等于说是同一天做这些事->

    数据更新：
    readfile
            定时queue *Local.update （queue：单链表 有记录头尾）
            Center利用pop，连接所有local的记录（用一个指针Data *Central,指向包含所有数据的单链表）
            每一次pop，insert入堆
    update数据：手动更新 遍历
    withdraw：手动更新，更新heap，data

    Appointment：
    available进行第二天的安排，预约信息体现在Data.appointment中（打印新的appointment）
    当天结束清空预约list

    Reporting:
    手动开启（每周一个）报告，给选项，生成一个report文件
    手动开启每月报告
    */
