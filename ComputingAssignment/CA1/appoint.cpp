#include <stdio.h>
#include <iostream>
#include <math.h>
#include "appoint.h"
#include "data.h"
using std::cin;
using std::cout;

Appointment::Appointment()
{
    in_alist = false;
}

template <class T>
List<T>::List(int value)
{
    numitems = 0;
    size = value;
    array = new T[value];
}

template <class T>
void List<T>::append(T value)
{
    array[numitems] = value;
    numitems++;
    if (numitems == size)
        allocate();
}

template <class T>
void List<T>::remove(int index)
{
    if (index <= numitems - 1)
    {
        for (int i = index; i < numitems; i++)
        {
            array[i] = array[i + 1];
        }
        numitems--;
        if (numitems == size / 4)
            deallocate();
    }
    else
        cout << "Index error: list index out of range\n";
}

template <class T>
void List<T>::allocate()
{
    int newsize = 2 * size;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; i++)
    {
        newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
    size = newsize;
}

template <class T>
void List<T>::deallocate()
{
    int newsize = size / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; i++)
    {
        newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
    size = newsize;
}

Hlist::Hlist() : List(20) // TODO: 是这样写的吗？
{
    tot_capacity = 0;
}

void Hlist::addh(Hospital *value)
{
    append(value);
    tot_capacity += value->capacity;
}

void Hlist::removeh(int index)
{
    remove(index);
    tot_capacity -= array[index]->capacity;
}

Alist::Alist() : List(20) {}

void Alist::appoint(Heap *H, Hlist hlist)
{
    Data *data = H->get_highest();
    if (data != NULL)
        cout << data->name << "\n";

    // add to Alist
    append(data);

    // find a Hospital
    int dist;
    int min_dist = 10000;
    int min_id = 0;
    for (int i = 0; i < hlist.numitems; i++)
    {
        if (hlist.array[i]->capacity > hlist.array[i]->numpatient)
        {
            cout << "hospital" << i << " address: addx = " << hlist.array[i]->addx << " addy = " << hlist.array[i]->addy << "\n";
            cout << "person address: addx = " << data->contact->addx << " addy = " << data->contact->addy << "\n";
            dist = (int)sqrt(pow((hlist.array[i]->addx - data->contact->addx), 2) + pow((hlist.array[i]->addy - data->contact->addy), 2));

            if (dist < min_dist)
            {
                min_dist = dist;
                min_id = i;
            }
            cout << "dist = " << dist << "\n";
            cout << "min_dist = " << min_dist << "\n";
        }
    }

    // change hospital information
    hlist.array[min_id]->numpatient++;
    cout << "hospital id = " << min_id << "\n";

    // change person data information
    data->appo = true;
    data->appointment->in_alist = true;
    data->appointment->hospital_id = min_id;
    data->appointment->time = 8 + 10 * (hlist.array[min_id]->numpatient / hlist.array[min_id]->capacity); // 从8到18点分配一个整数时间
    // data->appointment->date =
    // TODO: 有关时间，date? time?
    cout << "Finish appoint one person! Id = " << data->id << "\n";
}

void Alist::withdraw(Data *data) // withdraw在Alist里的元素
{
    data->withdrawn = true;
    data->appointment->in_alist = false;

    int index = 0;
    for (int i = 0; i < numitems; i++)
    {
        if (data->id == array[i]->id)
        {
            index = i;
            break;
        }
        else if (i == numitems - 1)
        {
            cout << "wrong data: not in Alist\n";
            return;
        }
    }
    remove(index);
    cout << "Withdrawn Person: " << data->name;
    cout << "There are " << numitems << " people remained in alist.\n";
}

void Alist::clear()
{
    numitems = 0;
    cout << "Alist cleared!\n";
}

Hospital::Hospital(int x, int y, int c)
{
    numpatient = 0;
    addx = x;
    addy = y;
    capacity = c;
}
