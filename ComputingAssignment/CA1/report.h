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
class Brutal_node
{
public:
    Brutal_node();
    Brutal_node *next;
    Data *ptr_to_data;
};
class Report_system : public Brutal_node
{
public:
    long Regi_number = 0;
    long all_waiting_number = 0;
    long all_appointment_number = 0;
    double RMS_waiting_time = 0;
    long withdraw_number = 0;

    int weekly_choice();
    void open_file_weekly(Data *data, int Choice, Brutal_node *ptr);
    void Writing_weekly(Data *data, int Choice, int Choice_2, Brutal_node *ptr);

    Brutal_node *Copied_list(Data *data);
    Brutal_node *sort_by_name(Brutal_node *ptr, int number);
    Brutal_node *sort_by_profession(Brutal_node *ptr, int number);
    Brutal_node *sort_by_age(Brutal_node *ptr, int number);

    Brutal_node *sortList(Brutal_node *ptr);
    Brutal_node *merge(Brutal_node *ptr1, Brutal_node *ptr2);
    Brutal_node *split(Brutal_node *ptr);

    void Writing_monthly();
    void stat(Data *data);
};
#endif