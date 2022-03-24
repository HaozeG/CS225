#include <cstdio>
#include <stdio.h>
#include <iostream>
#include "fibonacii_heap.h"
#include "data.h"
#include "appointment.h"
using std::cout;
using std::cin;

int main()
{
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
