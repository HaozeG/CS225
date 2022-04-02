#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include "fibonacii_heap.h"
#include "data.h"
#include "appoint.h"
using std::cin;
using std::cout;

int main()
{
    int op, f;
    long timeoffset = 0;
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
            cout << "3: manual update information\n";
            cout << "4: withdraw while waiting\n";
            cout << "5: make appointments\n";
            cout << "6: manual reporting\n";
            cout << "7: GO TO NEXT DAY\n";
            cin >> op;
        }
        while (op < 0 && op > 7);
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
                // char filename;
                // cout << "Specify the directory of the input file:\n";
                // cin >> filename;
                // cin.get();
                do
                {
                    cout << "Choose one local registry from 1 to 2: ";
                    cin >> f;
                }
                while (f < 1 && f > 2);
                local[f - 1]->readfile("testfile2", timeoffset);
                cout << "This queue has " << local[f - 1]->Queue->num << " items now\n";
                break;
            }
            case 2:
            {
                int i = 0;
                Data *temp = NULL;
                while (i < 2)
                {
                    while (local[i]->Queue->num != 0)
                    {
                        temp = local[i]->Queue->pop();
                        cout << temp->id << "\n";
                        if (0 == q->num)
                        {
                            q->head = temp;
                            q->tail = temp;
                            q->num++;
                            h->insert(temp);
                        }
                        else
                        {
                            // check if it has registered
                            Data *d_prev = q->head;
                            Data *d = d_prev->next;
                            // check the first data
                            cout << d_prev->id << "\n";
                            if (!strcmp(d_prev->id, temp->id))
                            {
                                temp->next = d;
                                q->head = temp;
                                delete d_prev->node->data;
                                cout << "update first one\n";
                                d_prev->node->data = temp;
                                h->update(*d_prev->node);
                                continue;
                            }
                            // cout << "test\n";
                            while (NULL != d)
                            {
                                // cout << "OMG\n";
                                if (!strcmp(d->id, temp->id))
                                {
                                    d_prev->next = temp;
                                    temp->next = d->next;
                                    delete d->node->data;
                                    d->node->data = temp;
                                    h->update(*d->node);
                                    break;
                                }
                                d_prev = d_prev->next;
                                d = d->next;
                            }
                            // if it is new data
                            if (NULL == d)
                            {
                                q->tail->next = temp;
                                q->tail = temp;
                                q->num++;
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
                // 手动更新某人的信息
                // do
                // {
                //     cout << "Choose one local registry from 1 to 3:";
                //     cin >> f;
                // }
                // while (f < 1 && f > 3);
                // local[f - 1]->readfile("updateinfo", timeoffset);
                // break;
            }
            case 4:
            {
                char a[10];
                bool flag = false;
                cout << "Enter an ID to withdraw\n";
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
                    while (pNode->next!=NULL)
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
                // Data *p = NULL;
                // p = h->get_highest();
                // if (NULL != p)
                //     cout << p->name << "\n";

                // input hospital information
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
