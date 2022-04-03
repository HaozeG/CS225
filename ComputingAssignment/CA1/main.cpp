#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include "timeoffset.h"
#include "fibonacii_heap.h"
#include "data.h"
#include "appoint.h"
using std::cin;
using std::cout;
long timeoffset = 0;
long timestart = 20220401;

int main()
{
    int op, f;
    Local *local[2];
    local[0] = new Local; // cout << "Create new local"
    local[1] = new Local; // cout << "Create new local"
    Heap *h = new Heap;
    queue *q = new queue;   // central
    // TODO: queue的析构要改（单链表）
    Alist alist;

    do
    {
        cout << "---NEW DAY---\n";
        // 输出今天是几月几日
        cout << "Today is " << int(timeoffset/24) << "\n";
        cout << "-------------\n";
        do
        {
            cout << "Choose an operation:\n";
            cout << "0: quit\n";
            cout << "1: do registration to local\n";
            cout << "2: update registry to central\n";
            cout << "3: present priority letter\n";
            cout << "4: withdraw while waiting\n";
            cout << "5: make appointments\n";
            cout << "6: manual reporting\n";
            cout << "7: GO TO NEXT DAY\n";
            cout << "8: print information about heap\n";
            cin >> op;
        }
        while (op < 0 && op > 8);
        switch (op)
        {
            case 0:
            {
                // destroy before exit
                delete local[0];
                delete local[1];
                delete q;
                delete h;
                return 0;
            }
            case 1:
            {
                char* c = new char[30];
                cout << "Specify the name of the input file:\n";
                cin >> c;
                const char* filename = c;
                // cout << filename << "hello\n";
                do
                {
                    cout << "Choose one local registry from 1 to 2:\n";
                    cin >> f;
                }
                while (f < 1 && f > 2);
                local[f - 1]->readfile(filename);
                cout << "This queue has " << local[f - 1]->Queue->num << " items now\n";
                // Data *p = local[0]->Queue->head;
                // while (nullptr != p)
                // {
                //     cout << p->name << "\n";
                //     p = p->next;
                // }
                break;
            }
            case 2:
            {
                int i = 0;
                Data *temp = nullptr;
                while (i < 2)
                {
                    while (local[i]->Queue->num != 0)
                    {
                        temp = local[i]->Queue->pop();

                        if (0 == q->num)
                        {
                            q->push(temp);
                            h->insert(temp);
                        }
                        else
                        {
                            // check if it has registered
                            Data *d_prev = q->head;
                            Data *d = d_prev->next;
                            // cout << d_prev->name << "\n";
                            // cout << temp->name << "\n";
                            // check the first data
                            if (!strcmp(d_prev->id, temp->id) && (false == d_prev->appo))
                            {
                                temp->next = d;
                                q->head = temp;
                                // cout << "update first one\n";
                                d_prev->node->data = temp;
                                temp->node = d_prev->node;
                                delete d_prev;
                                // cout << "test\n";
                                h->update(*temp->node);
                                continue;
                            }
                            while (nullptr != d)
                            {
                                if (!strcmp(d->id, temp->id) && (false == d->appo))
                                {
                                    d_prev->next = temp;
                                    temp->next = d->next;
                                    // cout << d->node->data << "\n";
                                    // cout << d->node << "test\n";
                                    d->node->data = temp;
                                    temp->node = d->node;
                                    delete d;
                                    h->update(*temp->node);
                                    break;
                                }
                                d_prev = d;
                                d = d->next;
                            }
                            // if it is new data
                            if (nullptr == d)
                            {
                                q->push(temp);
                                h->insert(temp);
                            }
                        }
                    }
                    i++;
                }
                cout << "Collect information from local registry\n";
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
                cout << "Enter an deadline (Format: YYYYMMDD):\n";
                cin >> str;
                str[8] = '\0';
                ddl = (atoi(str) - timestart) * 24;

                // search queue to find data with certain id
                Data *pNode = q->head;
                if (nullptr == pNode)
                {
                    cout << "data not found\n";
                    break;
                }
                if (strcmp(q->tail->id,a)==0)
                {
                    cout << "find the data\n";
                    pNode = q->tail;
                    flag = true;
                }
                else
                {
                    while (pNode->next!=nullptr)
                    {
                        if (strcmp(pNode->id,a)==0)
                        {
                            cout << "find the data\n";
                            flag = true;
                            break;
                        }
                        pNode = pNode->next;
                    }
                }
                if (flag)
                {
                    pNode->priority = ddl;
                    cout << pNode->name << "——priority letter presented\n";
                }
                else
                    cout << "data not found\n";
                break;
            }
            case 4:
            {
                char a[10];
                bool flag = false;
                cout << "Enter an ID to withdraw:\n";
                cin >> a;

                // search queue to find data with certain id
                Data *pNode = q->head;
                if (strcmp(q->tail->id,a)==0)
                {
                    cout << "find the data\n";
                    pNode = q->tail;
                    flag = true;
                }
                else
                {
                    while (pNode->next!=nullptr)
                    {
                        if (strcmp(pNode->id,a)==0)
                        {
                            cout << "find the data\n";
                            flag = true;
                            break;
                        }
                        pNode = pNode->next;
                    }
                }

                // withdraw that data
                if (flag)
                {
                    if (pNode->appointment->in_alist)
                    {
                        alist.withdraw(pNode);
                    }
                    else
                        h->delete_node(*(pNode->node));
                }
                else
                    cout << "ID not found\n";

                break;
            }
            case 5:
            {
                // check for priority letter
                Data *p = q->head;
                while (nullptr != p)
                {
                    if ((p->priority - timeoffset) <= 72 && 0 != p->priority)
                    {
                        p->priority = -1;
                        h->update(*p->node);
                    }
                    p = p->next;
                }
                cout << h->highest->data->name << "\n";

                // input hospital information
                Hlist hlist;
                Hospital hospital1(100, 100, 1), hospital2(500, 500, 1);
                hlist.addh(&hospital1);
                hlist.addh(&hospital2);

                cout << "tot_capacity = " << hlist.tot_capacity << "\n";

                bool available = false;
                cout << "alist.numitems = " << alist.numitems << "\n";
                available = (alist.numitems < hlist.tot_capacity ? true : false);
                while (available && h->n != 0)
                {
                    alist.appoint(h, hlist);
                    available = (alist.numitems < hlist.tot_capacity ? true : false);
                    cout << "alist.numitems = " << alist.numitems << "\n";
                }
                break;
            }
            case 6:
            {
                break;
            }
            case 7:
            {
                timeoffset += 24; // +24h
                break;
            }
            case 8:
            {
                // print heap
                Node *p = h->highest->left;
                // cout << p->left->data->name << "\n";
                // cout << p->data->name << "\n";
                // cout << h->highest->right->data->name << "\n";
                cout <<  "highest:" << h->highest->data->name << "\n";
                cout << "names in root list:\n";
                int i = 0;
                while (p != h->highest)
                {
                    cout << p->data->name << "\n";
                    p = p->left;
                    i++;
                    if (i>10)
                        break;
                }
                cout << p->data->name << "\n";
                break;
            }
        }
    }
    while (op != 0);
    return 0;

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

    /*
    // Data a;
    // printf(a.id[0]);
    // return 0;
    char a[5] = "123\n";
    a[3] = '\0';
    cout << a;



    // appoint
    Alist alist;
    Hlist hlist;
    Hospital hospital1(114, 514, 1000), hospital2(100, 200, 500);
    hlist.append(&hospital1);
    hlist.append(&hospital2);

    bool available = false;
    available = (alist.numitems < hlist.tot_capacity ? true : false);

    while (available)
    {
        alist.appoint(h, hlist);
    }



    // withdraw
    Data *inputdata;

    if (inputdata->appointment->in_alist)
        alist.withdraw(inputdata);
    else
        cout << "0\n";
    //
    // h->delete_node(?)
    */
}
