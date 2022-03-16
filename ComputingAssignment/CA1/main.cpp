#include <cstdio>
#include "fibonacii_heap.h"
#include "data.h"
#include "appointment.h"

int main()
{
        // Data a;
        // printf(a.id[0]);
        // return 0;
        Heap a;
        printf("%d\n", a.n);
        return 0;

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
