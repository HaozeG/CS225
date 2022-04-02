#ifndef data_h
#define data_h
#include <time.h>
#include <stdint.h>
#include <stdio.h>
using namespace std;

class Contact
{
public:
    Contact();

    int addx;
    int addy;
    char* phone;
    char* WeChat;
    char* email;
};

class Appointment
{
public:
    Appointment();

    bool in_alist; // whether in Alist or not
    int addx;
    int addy;
    long date;
    long time;  // TODO: 和timestamp对应
    int hospital_id;
};

class Node;

// basic structure of one registry
class Data
{
public:
    Data();

    Appointment *appointment;

    bool withdrawn = false;
    bool appo = false;
    bool treated = false;

    long timestamp; // YY,MM,DD,HH,MM,SS
    char* id;  //TODO:再说
    char* birth; // format: YYMMDD
    int risk;

    char* name;
    int profession; // I to VIII
    int age_group;

    Contact *contact;
    Data *next = NULL;
    Node *node = NULL;
};

class queue
{
public:
    queue();
    ~queue();

    void push(Data* person);
    Data* pop();
    int num = 0;
    Data* head = NULL;
    Data* tail = NULL;
};

class Local
{
public:
    Local();
    ~Local();

    queue* Queue;
    queue* update(int time);   // update to central
    int registration();
    int readfile(const char* filename, long timeoffset);
    char str[60];
};

class Central
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};



#endif
