#ifndef report_h
#define report_h

#include <stdint.h>
#include <string>
#include <time.h>
#include "data.h"
#include "fibonacii_heap.h"
using namespace std;

//used for reporting process
class Report_system
{
public:
    long Regi_number = 0;
    long all_waiting_number = 0;
    long all_appointment_numebr = 0;
    double RMS_waiting_time = 0;
    long withdraw_number = 0;
    int weekly_choice();
    void open_file();
    void file_month();
    void Writing_weekly(Node *node, int choice);
    void stat(Node *node);
};
//usde for counting time
class Counting_system
{
public:
    time_t timep;
    
};






#endif