#include <stdio.h>
#include <iostream>
#include "fibonacii_heap.h"
#include "appointment.h"
#include "data.h"
using std::cin;
using std::cout;

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
    H.highest->data->appointment->registered = true;
}

void Appoint_list::withdraw(Data &data)
{
    for (int i = 0; i <= numitems - 1; i++)
    {
        if (appoint_list[i] == data)
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

Hospital_list::Hospital_list()
{
    numitems = 0;
    total_capacity = 0;
}