#include <stdio.h>
#include <iostream>
#include <math.h>
#include "appoint.h"
#include "data.h"
#include "timeoffset.h"
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

<<<<<<< HEAD
Hlist::Hlist() : List(20)
=======
Hlist::Hlist() : List(20)
>>>>>>> master
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

void Hlist::treat_done()
{
    for (int i = 0; i < numitems; i++)
    {
        array[i]->numpatient = 0;
    }
    cout << "Treated done.\n";
}

Alist::Alist() : List(20) {}

void Alist::appoint(Heap *H, Hlist hlist)
{
    Data *data = H->get_highest();
    if (data != nullptr)
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

            dist = (int)sqrt(pow((hlist.array[i]->addx - data->contact->addx), 2) + pow((hlist.array[i]->addy - data->contact->addy), 2));

            if (dist < min_dist)
            {
                min_dist = dist;
                min_id = i;
            }
        }
    }

    cout << "hospital id = " << min_id << "\n";
    cout << "hospital" << min_id << " address: addx = " << hlist.array[min_id]->addx << " addy = " << hlist.array[min_id]->addy << "\n";
    cout << "person address: addx = " << data->contact->addx << " addy = " << data->contact->addy << "\n";
    // change hospital information
    hlist.array[min_id]->numpatient++;

    // change person data information
    data->appo = true;
    data->appointment->in_alist = true;
    data->appointment->hospital_id = min_id;
    data->appointment->time = timeoffset + 24 + 8 + 10 * ((hlist.array[min_id]->numpatient - 1) / hlist.array[min_id]->capacity); // 从8到18点分配一个整数时间
    cout << "treated time = " << data->appointment->time << "\n";

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
    for (int i = 0; i < numitems; i++)
    {
        array[i]->appointment->in_alist = false;
        array[i]->treated = true;
    }

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
