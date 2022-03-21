//
//  listbm.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 15.03.22
//

#ifndef listbm_h
#define listbm_h

template<class T> class BMlist
{
public:
    BMlist(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(BMlist<T> &list);
    bool member(T value);
    bool equal(BMlist<T> &list);
    bool sublist(BMlist<T> &list);
    void prettyprint(void);
    void rotate(int m);
    T select(int k);
    void create_d1(void);
    void create_d2(void);
    int bm(BMlist<T> *target);
    void bm_all(BMlist<T> *target);
private:
    int numitems;
    T *reprarray;
    int * d1list;
    int * d2list;
    int shift;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

#endif /* listbm_h */
