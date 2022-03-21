//
//  listbm.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 15.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listbm.h"
using std::cout;
using std::cin;

template<class T> BMlist<T>::BMlist(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
    d1list = 0;
    d2list = 0;
}

/* Most of the member functions are the same as for AList */

template<class T> T &BMlist<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int BMlist<T>::getlength(void)
{
    return numitems;
}

template<class T> void BMlist<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T BMlist<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void BMlist<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void BMlist<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void BMlist<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void BMlist<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void BMlist<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void BMlist<T>::concat(BMlist<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool BMlist<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool BMlist<T>::equal(BMlist<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool BMlist<T>::sublist(BMlist<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void BMlist<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i+1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* the added member functions create_d1, create_d2 and bm need to be implemented */

template<class T> void BMlist<T>::create_d1(void)
{
    /* This member function needs to be implemented. It pre-computes the d1 values used in the BM algorithm */
}

template<class T> void BMlist<T>::create_d2(void)
{
    /* This member function needs to be implemented. It pre-computes the d2 values used in the BM algorithm and the shift in case of success*/
}

template<class T> int BMlist<T>::bm(BMlist<T> *target)
{
    /* This member function needs to be implemented. It implements the BM algorithm with this list as pattern list and an arbitrary target list given as input */
}

template<class T> void BMlist<T>::bm_all(BMlist<T> *target)
{
    /* This member function needs to be implemented. It implements the extended BM algorithm with this list as pattern list and an arbitrary target list given as input, and prints all locations in the target list, where a substring equal to the pattern starts */
}
