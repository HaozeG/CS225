//
//  listbm.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 18.03.22.
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
    int *newd1 = new int[256];
    /* Here we should take |T| instead of 256, but let's assume that we only use string matching for T = char. Then the created array is indexed by the ASCII code. */
    for (int i = 0; i < 256; i++)
    {
        newd1[i] = numitems;
        /* initialise d1 to m = |P| */
    }
    for (int j = 0; j < numitems; j++)
    {
        newd1[reprarray[j]] = numitems - j - 1;
    }
    d1list = newd1;
    return;
}

template<class T> void BMlist<T>::create_d2(void)
{
    int *newd2 = new int[numitems - 1];
    for (int k = 0; k < numitems - 1; k++)
    {
        newd2[k] = numitems;
    }
    int count = 1;
    for (int j = numitems - 1 - count; j >= 0; j = numitems - 1 - count)
    {
        for (int i = 0; i <= j; i++)
        {
            if (reprarray[j - i] != reprarray[numitems - i - 1])
            {
                /* i = i_c*/
                newd2[numitems - i - 1] = count;
                count += i;
                if (i == 0)
                    count++;
                break;
            }
            else
            {
                if (i == j)
                {
                    count += i;
                    if (i == 0)
                        count++;
                }
            }
        }
    }
    shift = count;
    d2list = newd2;
    return;
}

template<class T> int BMlist<T>::bm(BMlist<T> *target)
{
    /* We must assume that d1list and d2list have been created */
    int position = -1;
    int move;
    int n = (*target).getlength();
    for (int pos = 0; pos < n - numitems;)
    {
        for (int i = pos + numitems - 1, j = numitems - 1; j >=0 && i >= 0; j--, i--)
        {
            if (reprarray[j] != (*target)[i+1])
            {
                if (j == numitems - 1)
                    move = d1list[(*target)[i+1]];
                else
                    move = d2list[j];
                pos += move;
                break;
            }
            else
            {
                if (j == 0)
                    position = pos;
            }
        }
        if (position != -1)
            break;
    }
    return position;
}

template<class T> void BMlist<T>::bm_all(BMlist<T> *target)
{
    /* We must assume that d1list and d2list have been created */
    int position = -1;
    int move;
    int n = (*target).getlength();
    for (int pos = 0; pos < n - numitems;)
    {
        for (int i = pos + numitems - 1, j = numitems - 1; j >=0 && i >= 0; j--, i--)
        {
            if (reprarray[j] != (*target)[i+1])
            {
                if (j == numitems - 1)
                    move = d1list[(*target)[i+1]];
                else
                    move = d2list[j];
                pos += move;
                break;
            }
            else
            {
                if (j == 0)
                {
                    position = pos;
                    cout << "The pattern list appears in the target list\n" << "at position " << position << ".\n";
                    pos += shift;
                }
            }
        }
    }
    if (position == -1)
        cout << "The pattern list does not appear in the target list.\n";
    return;
}
