#ifndef data_h
#define data_h
using namespace std;

class Contact
{
public:
    Contact();
    ~Contact();

    int addx;
    int addy;
    char *phone;
    char *WeChat;
    char *email;
};

class Appointment
{
public:
    Appointment();

    bool in_alist;  // whether in Alist or not
    long time;
    int hospital_id;
};

class Node;

// basic structure of one registry
class Data
{
public:
    Data();
    ~Data();

    Appointment *appointment;

    bool withdrawn;
    bool appo;
    bool treated;
    bool twice;     // register again after withdrawing
    int locale;

    long timestamp; // a time offset
    char *id;
    char *birth;    // format: YYMMDD
    int risk;

    char *name;
    int profession; // I to VIII
    int age_group;
    int priority;

    Contact *contact;
    Data *next;
    Node *node;
};

class queue
{
public:
    queue();
    ~queue();

    void push(Data *person);
    Data *pop();
    int num;
    Data *head;
    Data *tail;
};

class Local
{
public:
    Local();
    ~Local();

    queue *Queue;
    // queue *update(int time); // update to central
    // int registration();
    int readfile(const char *filename, int locale);
    char str[60];
};

#endif
