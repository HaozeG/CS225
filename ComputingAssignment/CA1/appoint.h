#ifndef appoint_h
#define appoint_h

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

class Alist : public List<Data *>
{
public:
    Alist();

    void appoint(Heap *H, Hlist hlist);
    void withdraw(Data *data);
    void clear();
    const int INFINITY = 10000;
};

class Hospital
{
public:
    Hospital(int x,int y,int c);

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
    void addh(Hospital *value);
    void removeh(int index);

    int tot_capacity;
};

#endif
