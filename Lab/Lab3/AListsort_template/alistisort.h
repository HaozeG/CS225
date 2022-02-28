//
//  alistsort.h
//  
//
//  Created by KD on 22.01.21.
//

#ifndef alistisort_h
#define alistisort_h

template<class T> class AList
{
public:
    AList(int size = 20);
//    virtual ~AList();
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
    void isort(void);
    void isort_ip(void);
private:
    int numitems;
    int maxsize, minsize;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
    int find_min(int limit);
};

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

#endif /* alistisort_h */
