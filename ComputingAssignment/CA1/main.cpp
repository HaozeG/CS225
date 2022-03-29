#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "fibonacii_heap.h"
#include "data.h"
#include "appointment.h"
using std::cout;
using std::cin;

int main()
{
    int op;
    // Local *local = new Local;
    Heap *h = new Heap;

    do
    {
        cout << "---NEW DAY---\n";
        // 输出今天是几月几日
        // 自动完成read registry

        do
        {
            cout << "Choose an operation:\n";
            cout << "0: quit\n";
            cout << "1: read registry to local\n";
            cout << "2: update registry to central\n";
            cout << "3: update information of registry\n";
            cout << "4: withdraw while waiting\n";
            cout << "5: make appointments\n";
            cout << "6: manual reporting\n";
            cout << "7: GO TO NEXT DAY\n";
            cin >> op;
        }
        while ((op < 0 && op > 7));
        switch (op)
        {
            case 0:
            {
                delete h;
                return 0;
            }
            case 1:
            {
                // update();
            }
            case 2:
            {
                // 读入，形成链表
            }
            case 3:
            {
                // 手动更新某人的信息
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

            // Data a;
            // printf(a.id[0]);
            // return 0;
            char a[5] = "123\n";
        a[3] = '\0';
        cout << a;

        // 导入数据，存入local registry queue，合并为centralized queue

        // 存入斐波那契堆
        Heap H;


        // 安排appointment
        Appoint_list Alist;  // Alist is appointment list.
        Hospital_list Hlist; // Hlist is hospital list.
        bool available;
        available = (Alist.numitems < Hlist.total_capacity ? true : false);

        while (available)
        {
                Alist.appoint(H, Hlist);
        }

}
