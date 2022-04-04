#ifndef appoint_h
#define appoint_h

#include "fibonacii_heap.h"

template <class T>
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
    T *array;
};

class Hospital
{
public:
    Hospital(int x, int y, int c);

    int addx;
    int addy;
    int capacity;
    int numpatient;
    int timeslot; // 医院默认早上8点开始工作，18点结束
};

class Hlist : public List<Hospital *>
{
public:
    Hlist();
    void addh(Hospital *value); // add a hospital to hlist
    void removeh(int index);    // remove a hospital from hlist
    void treat_done();          // clear numpatients in each hospital.

    int tot_capacity;
};

class Alist : public List<Data *>
{
public:
    Alist();

    void appoint(Heap *H, Hlist hlist); // appoint one person with highest priority
    void withdraw(Data *data);          // withdraw a person from alist
    void clear();                       // set treated = true and clear alist.
    // const int INFINITY = 10000;
};

#endif
