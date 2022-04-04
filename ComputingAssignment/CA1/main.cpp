#include <stdio.h>
#include <iostream>
#include "timeoffset.h"
#include "fibonacii_heap.h"
#include "data.h"
#include "appoint.h"
#include "report.h"
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
    Alist alist;
    Hlist hlist;
    Hospital hospital1(100, 100, 1), hospital2(500, 500, 1);
    hlist.addh(&hospital1);
    hlist.addh(&hospital2);
    do
    {
        cout << "---NEW DAY---\n";
        // 输出今天是几月几日
        cout << "TODAY IS " << timestart + int(int(timeoffset/24)/30)*100 + (int(timeoffset/24) - 30 * int(int(timeoffset/24)/30)) << "\n";
        cout << "-------------\n";
        do
        {
            cout << "Choose an operation:\n";
            cout << "0: QUIT\n";
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
                                if (true == d_prev->withdrawn)
                                    d_prev->twice = true;
                                temp->priority = d_prev->priority;
                                temp->withdrawn = d_prev->withdrawn;
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
                                    if (true == d_prev->withdrawn)
                                        d_prev->twice = true;
                                    temp->priority = d_prev->priority;
                                    temp->withdrawn = d_prev->withdrawn;
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

                // search queue to find data with certain id
                Data *pNode = q->head;
                if (nullptr == pNode)
                {
                    cout << "data not found\n";
                    break;
                }
                if (strcmp(q->tail->id,a)==0)
                {
                    pNode = q->tail;
                    flag = true;
                }
                else
                {
                    while (pNode->next!=nullptr)
                    {
                        if (strcmp(pNode->id,a)==0)
                        {

                            flag = true;
                            break;
                        }
                        pNode = pNode->next;
                    }
                }
                if (flag)
                {
                    pNode->priority = ddl;
                    cout << pNode->name << "=>priority letter presented\n";
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
                if (pNode==nullptr)
                {
                    cout << "data not found\n";
                    break;
                }
                if (strcmp(q->tail->id,a)==0)
                {
                    pNode = q->tail;
                    flag = true;
                }
                else
                {
                    while (pNode->next!=nullptr)
                    {
                        if (strcmp(pNode->id,a)==0)
                        {
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
                        pNode->appo = false;
                    }
                    else if(pNode->node!=nullptr)
                    {
                        pNode->withdrawn = true;
                        h->delete_node(*(pNode->node));
                    }
                    else
                        cout << "data not found\n";
                }
                else
                    cout << "data not found\n";

                break;
            }
            case 5:
            {
                // check for priority letter
                Data *p = q->head;
                while (nullptr != p)
                {
                    if ((nullptr != p->node) && (p->priority - timeoffset) <= 72 && -1 != p->priority)
                    {
                        Data *new_data = new Data;
                        new_data->name = p->name;
                        new_data->profession = -1; // make sure it has the highest priority
                        new_data->risk = 0;
                        p->node->data = new_data;

                        // call decrease and delete_min
                        h->update(*p->node);
                        p->node->data = p;
                        delete new_data;
                    }
                    p = p->next;
                }
                // if (nullptr != h->highest)
                //     cout << h->highest->data->name << "\n";
                // else
                // {
                //     cout << "Heap already empty!\n";
                //     break;
                // }

                // input hospital information
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
                char c = 'a';
                do
                {
                    cout << "w for weekly report; m for monthly report\n";
                    cin >> c;
                }
                while (c != 'w' && c != 'm');
                switch (c)
                {
                    case ('w'):
                    {
                        Report_system report;
                        report.Open_file(q->head, timeoffset, q->num);
                        break;
                    }
                    case ('m'):
                    {
                        Report_system report;
                        report.Month(q->head, timeoffset);
                    }
                }
                break;
            }
            case 7:
            {
                hlist.treat_done();
                alist.clear();

                timeoffset += 24; // +24h
                if ((timeoffset/24) % 7 == 0 && 0 != timeoffset)
                {
                    Report_system report;
                    report.Open_file(q->head, timeoffset, q->num);
                }
                if ((timeoffset/24) % 30 == 0 && 0 != timeoffset)
                {
                    Report_system report;
                    report.Month(q->head, timeoffset);
                }
                break;
            }
            case 8:
            {
                // print heap
                if (nullptr == h->highest)
                {
                    cout << "Heap already empty!\n";
                    break;
                }
                Node *p = h->highest->left;
                // cout << p->left->data->name << "\n";
                // cout << p->data->name << "\n";
                // cout << h->highest->right->data->name << "\n";
                cout << "Name of highest:\n" << h->highest->data->name << "\n";
                cout << "Names in root list:\n";
                int i = 0;
                while (p != h->highest)
                {
                    cout << p->data->name << "->\n";
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
