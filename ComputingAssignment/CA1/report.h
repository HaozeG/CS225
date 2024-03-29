#ifndef report_h
#define report_h

#include <ratio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "data.h"
using namespace std;
class Report_system
{
public:
    void Open_file(Data *head, long timeoffset, int length);
    void Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating);
    void Month(Data *head, long timeoffset);

    Data *Sorting(Data *head, int Choice_2, int length, int Choice);
    static bool cmp_age(Data a, Data b);
    static bool cmp_profession(Data a, Data b);
    static bool cmp_name(Data a, Data b);
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
