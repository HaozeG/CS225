#ifndef report_h
#define report_h

#include <ratio>
#include <stdint.h>
#include <string>
#include <time.h>
#include "data.h"
#include "fibonacii_heap.h"
using namespace std;

//used for reporting  process,strcmp()!!!!!!!, 用建构函数写数据的初始化
class Report_system
{
public:
    long Regi_number = 0;
    long all_waiting_number = 0;
    long all_appointment_numebr = 0;
    double RMS_waiting_time = 0;
    long withdraw_number = 0;
    //choose the order of weekly report
    int weekly_choice();
    //open file for weekly report
    void open_file();
    void Writing_weekly(Node *node, int choice);
    //open and write for monthly report
    void file_month();
    //count different category number for one node
    void stat(Node *node);
    //choose which operation to use
    void selection(int number, int number_two, Heap &H);
    //sort by name
    void sort_by_name(Heap &H, int number);
    //sort by profession
    void sort_by_profession(Heap &H, int number);
    //sort by age
    void sort_by_age(Heap &H, int number);
};
//usde for counting time
class Counting_system
{
public:
    time_t timep;  
};

class Brutal_node
{
public:
    Brutal_node *next;
};
#endif