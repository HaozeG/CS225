#ifndef data_h
#define data_h

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/_types/_time_t.h>
using namespace std;

class Contact
{
public:
    Contact();
    int addx;
    int addy;

protected:
    char phone[11];
    char WeChat[12];
    char email[18];
};

class Appointment
{
public:
    Appointment();

    bool registered; // 是否有appointment.
    int addx;
    int addy;
    long date; // TODO:long?
    int time;  // TODO: 和timeslot对应
    int hospital_id;
    time_t timpe_app;
};

// basic queue data structure
// TODO:存在外部文件中还是内存中
class Data
{
public:
    Data();

    Appointment *appointment;
    time_t timep;
    long timestamp; // YY,MM,DD,HH,MM,SS
    // TODO: 写成bias
    bool withdrawn;
    char id[9] = {"12345678"}; // TODO:再说
    char name[10];
    Contact *contact;
    int profession; // I to VIII
    long birth;     // format: YYMMDD
    int age_group;
    int risk;
    Data *next = NULL;
};

class queue : public Data
{
public:
    queue();
    void push(Data *person);
    Data *pop();
    int num = 0;
    Data *head = NULL;
    Data *tail = NULL;
};

class Local : public queue
{
public:
    Local();
    Data *update(); // update to central
    int registration();
};

class Central : public Data
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};

#endif
