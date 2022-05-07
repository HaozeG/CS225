#ifndef appoint_h
#define appoint_h

#include "fibonacci_heap.h"
#include "data.h"

template<class T>
class List
{
public:
    List(int value = 20);

    void append(T value);
    void remove(int index);

    void allocate();
    void deallocate();

    int numitems;
    int size;
    T* array;
};

class Hospital
{
public:
    Hospital(int x, int y, int c1, int c2, int c3);

    int addx;
    int addy;
    int capacity[3]; // three type of treatment
    int numpatient[3] = { 0 };
    int timeslot; // 医院默认早上8点开始工作，18点结束
};

class Hlist : public List<Hospital*>
{
public:
    Hlist();
    void addh(Hospital* value); // add a hospital to hlist
    void removeh(int index); // remove a hospital from hlist
    void treat_done(); // clear numpatients in each hospital.

    int tot_capacity[3]={0};
};

class Alist : public List<relation*>
{
public:
    Alist();

    void appoint(Heap* H, Hlist hlist,int type); // appoint one person with highest priority
    void withdraw(relation* relation); // withdraw a person from alist
    void clear(); // set treated = true and clear alist.
    // const int INFINITY = 10000;
};

#endif
