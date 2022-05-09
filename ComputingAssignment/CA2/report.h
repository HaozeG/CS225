#ifndef report_h
#define report_h

#include "data.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string.h>
#include <string>
using namespace std;
class Report_system
{
public:
    void Open_file(blist<relation>* ptr, long timeoffset, int length);
    void Week(blist<relation>* ptr, int Choice, int Choice_2, long timeoffset, int length, bool treating);
    void Month(blist<relation>* ptr, long timeoffset);
    relation* Sorting(blist<relation>* head, int Choice_2, int length, int Choice);
    void time_calculator(bool treating, relation *paste);
    // static bool cmp_age(Data a, Data b);
    // static bool cmp_profession(Data a, Data b);
    // static bool cmp_name(Data a, Data b);
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
