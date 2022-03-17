#ifndef appointment_h
#define appointment_h

#include <stdint.h>
#include <string>
using namespace std;

class Hospital_list
{
public:
    Hospital_list();

    Hospital *hospital_list;
    int numitems;
    int total_capacity;
};

class Hospital
{
public:
    Hospital();

    string address; // TODO: 怎么找closest
    int capacity;
    int timeslot; // TODO:类型以及用途
};

class Appoint_list
{
public:
    Appoint_list();
    void appoint(Heap &H, Hospital_list &Hlist);
    void withdraw(Data &data);

    Data *appoint_list;
    int numitems;
};

#endif