#include <stdio.h>
#include <iostream>
#include "fibonacci_heap.h"
#include "appointment.h"
#include "data.h"
using std::cin;
using std::cout;

Hospital_list::Hospital_list()
{
    numitems = 0;
    total_capacity = 0;
}

Appointment::Appointment()
{
    registered = false;
}

Appoint_list::Appoint_list()
{
    numitems = 0;
}

void Appoint_list::appoint(Heap &H, Hospital_list &Hlist)
{
    appoint_list[numitems] = H.highest->data;
    H.delete_highest();

    // assign this person to certain hospital
    int distance;
    int min_distance = INFINITY;
    int min_id = 0;
    for (int i = 0; i < Hlist.numitems; i++)
    {
        if (Hlist.hospital_list[i].capacity > Hlist.hospital_list[i].numpatient)
        {
            distance = sqrt((Hlist.hospital_list[i].addx - appoint_list[numitems].contact->addx) ^ 2 + (Hlist.hospital_list[i].addy - appoint_list[numitems].contact->addy) ^ 2);
            if (distance < min_distance)
            {
                min_distance = distance;
                min_id = i;
            }
        }
    }
    // change hospital information
    Hlist.hospital_list[min_id].numpatient++;

    // change person data information
    appoint_list[numitems].appointment->registered = true;
    appoint_list[numitems].appointment->hospital_id = min_id;
    // TODO: appoint_list[numitems].appointment->date =  ;
    // appoint_list[numitems].appointment->time = ;

    numitems++;
}

void Appoint_list::withdraw(Data &data)
{
    data.withdrawn = true; // if register again, two weeks penalty

    if (data.appointment->registered)
    {
        for (int i = 0; i <= numitems - 1; i++)
        {
            if (appoint_list[i].id == data.id)
            {
                for (int j = i + 1; j <= numitems - 1; j++)
                {
                    appoint_list[j - 1] = appoint_list[j];
                }
                numitems--;
                break;
            }
        }
    }
    else
    {
        // 从斐波那契堆中去除？
    }
    

}

