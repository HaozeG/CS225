#ifndef report_h
#define report_h

#include <ratio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <runetype.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "data.h"

using namespace std;

class Report_system
{
public:

    long Regi_number = 0;
    long all_waiting_number = 0;
    long all_appointment_number = 0;
    long Waiting_time = 0;
    long withdraw_number = 0;

    void Open_file(Data *head, long timeoffset, int length);
    void Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating);
    void Month(Data *head, long timeoffset);

    Data *Sorting(Data *head, int number, int length, bool NAME);
    static bool cmp(Data *a, Data *b);
    static bool cmp_name(Data *a, Data *b);
    int *stat(Data *data);

};
#endif



/*


    Brutal_node *Copied_list(Data *data);
    Brutal_node *sort_by_name(Brutal_node *ptr, int number);
    Data *sort_by_age(Brutal_node *ptr, int number, int length);
    Brutal_node *sortList(Brutal_node *ptr);
    Brutal_node *merge(Brutal_node *ptr1, Brutal_node *ptr2);
    Brutal_node *split(Brutal_node *ptr);

*/