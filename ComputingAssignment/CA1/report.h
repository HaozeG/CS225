#ifndef report_h
#define report_h

#include <ratio>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <time.h>
#include "data.h"
#include "fibonacii_heap.h"
using namespace std;


class Brutal_node
{
public:
    Brutal_node *next;
    Data *ptr;
};
//used for reporting  process,strcmp()!!!!!!!, 用建构函数写数据的初始化
class Report_system : public Brutal_node
{
public:
    long Regi_number = 0;
    long all_waiting_number = 0;
    long all_appointment_number = 0;
    double RMS_waiting_time = 0;
    long withdraw_number = 0;
    //choose the order of weekly report
    int weekly_choice();
    //open file for weekly report
    void open_file(Data *data, int Choice, Brutal_node *ptr);
    void Writing_weekly(Data *data, int Choice, int Choice_2, Brutal_node *ptr);
    //open and write for monthly report
    void file_month();
    //count different category number for one node
    void stat(Data *data);
    //copy list
    Brutal_node *Copied_list(Data *data, Brutal_node *ptr);
    //choose which operation to use
    void selection(int number, int number_two, Heap &H);

    
    //sort by name
    void sort_by_name(Brutal_node *ptr, int number);
    //sort by profession
    void sort_by_profession(Brutal_node *ptr, int number);
    //sort by age
    void sort_by_age(Brutal_node *ptr, int number);
};
//usde for counting time
class Counting_system
{
public:
    time_t timep;  
};
#endif