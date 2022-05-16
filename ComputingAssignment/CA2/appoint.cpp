#include <stdio.h>
#include <iostream>
#include <math.h>
#include "appoint.h"
#include "data.h"
#include "timeoffset.h"
using std::cin;
using std::cout;

template<class T>
List<T>::List(int value)
{
    numitems = 0;
    size = value;
    array = new T[value];
}

template<class T>
void List<T>::append(T value)
{
    array[numitems] = value;
    numitems++;
    if (numitems == size)
        allocate();
}

template<class T>
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

template<class T>
void List<T>::allocate()
{
    int newsize = 2 * size;
    T* newarray = new T[newsize];
    for (int i = 0; i < numitems; i++)
    {
        newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
    size = newsize;
}

template<class T>
void List<T>::deallocate()
{
    int newsize = size / 2;
    T* newarray = new T[newsize];
    for (int i = 0; i < numitems; i++)
    {
        newarray[i] = array[i];
    }
    delete[] array;
    array = newarray;
    size = newsize;
}

Hlist::Hlist() :
    List(20){}

void Hlist::addh(Hospital* value)
{
    append(value);
    for (int i = 0; i < 3; i++)
    {
        tot_capacity[i] += value->capacity[i];
    }


}

void Hlist::removeh(int index)
{
    remove(index);
    for (int i = 0; i < 3; i++)
    {
        tot_capacity[i] -= array[index]->capacity[i];
    }

}

void Hlist::treat_done()
{
    for (int i = 0; i < numitems; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            array[i]->numpatient[j] = 0;
        }
    }
    cout << "Treated done.\n";
}

Alist::Alist() :
    List(20) {}

void Alist::appoint(Heap* H, Hlist hlist,int type) // TODO: 按照type调整医院信息
{
    relation* relation = H->get_highest();
    if (relation != nullptr)
        cout << relation->person->name << "\n";

    // add to Alist
    append(relation);

    // find a Hospital
    int dist;
    int min_dist = 10000;
    int min_id = 0;
    for (int i = 0; i < hlist.numitems; i++)
    {
        if (hlist.array[i]->capacity[type] > hlist.array[i]->numpatient[type])
        {
            dist = (int)sqrt(pow((hlist.array[i]->addx - relation->person->addx), 2) + pow((hlist.array[i]->addy - relation->person->addy), 2));

            if (dist < min_dist)
            {
                min_dist = dist;
                min_id = i;
            }
        }
    }

    cout << "hospital id = " << min_id << "\n";
    cout << "hospital" << min_id << " address: addx = " << hlist.array[min_id]->addx << " addy = " << hlist.array[min_id]->addy << "\n";
    cout << "person address: addx = " << relation->person->addx << " addy = " << relation->person->addy << "\n";
    // change hospital information
    hlist.array[min_id]->numpatient[type]++;

    // change person data information
    relation->appoint->appo = true;
    relation->appoint->in_alist = true;
    relation->appoint->hospital_id = min_id;
    relation->appoint->time = timeoffset + 24 + 8 + 10 * ((hlist.array[min_id]->numpatient[type] - 1) / hlist.array[min_id]->capacity[type]); // 从8到18点分配一个整数时间
    cout << "treated time = " << relation->appoint->time << "\n";

    cout << "Finish appoint one person! Id = " << relation->person->id << "\n";
}

void Alist::withdraw(relation* relation) // withdraw在Alist里的元素
{
    relation->appoint->withdrawn = true;
    relation->appoint->in_alist = false;

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
    cout << "Withdrawn Person: " << relation->person->name;
    cout << "There are " << numitems << " people remained in alist.\n";
}

void Alist::clear()
{
    for (int i = 0; i < numitems; i++)
    {
        array[i]->appoint->in_alist = false;
        array[i]->appoint->treated = true;
    }

    numitems = 0;
    cout << "Alist cleared!\n";
}

Hospital::Hospital(int x, int y, int c1, int c2, int c3)
{
    addx = x;
    addy = y;
    capacity[0] = c1;
    capacity[1] = c2;
    capacity[2] = c3;
}
