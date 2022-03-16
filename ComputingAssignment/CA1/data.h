#ifndef data_h
#define data_h

#include <stdint.h>
#include <string>
using namespace std;

class Contact
{
public:
    Contact();

protected:
    string address;
    string phone;
    string WeChat;
    string email;
};

// basic queue data structure
// TODO:存在外部文件中还是内存中
class Data
{
public:
    Data();
    Appointment *appointment;

private:
    int timestamp[6];          // YY,MM,DD,HH,MM,SS
    char id[9] = {"12345678"}; // TODO:再说
    string name;
    Contact *contact;
    int profession; // I to VIII
    long birth;     // format: YYMMDD
    int age_group;
};

class Local : public Data
{
public:
    Local();
    int update(); // update to central

private:
    Data *queue; // the queue of all local records
};

class Central : public Data
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};

class Appointment
{
public:
    Appointment();

    bool registered; // TODO:是否有appointment. 若withdraw则false?
    string address;
    long date; // TODO:long?
    int time;  // TODO: 和timeslot对应
};

#endif
