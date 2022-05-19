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
    void Open_file(blist<relation>* ptr, long timeoffset);
    void Week(blist<relation>* ptr, int Choice, int Choice_2, long timeoffset, bool treating);
    void Month(blist<relation>* ptr, long timeoffset);
    relation* Sorting(blist<relation>* head, int Choice_2, int Choice);
    void time_calculator(bool treating, relation* paste, long timeoffset);
    static bool cmp_age(relation a, relation b);
    static bool cmp_profession(relation a, relation b);
    static bool cmp_name(relation a, relation b);
};
#endif

