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

    bool in_alist; // whether in Alist or not
    // long date;
    long time; // TODO: 和timestamp对应
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

    bool withdrawn = false;
    bool appo = false;
    bool treated = false;
    bool twice = false;

    long timestamp; // a time offset
    char *id;
    char *birth; // format: YYMMDD
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
    int num = 0;
    Data *head = nullptr;
    Data *tail = nullptr;
};

class Local
{
public:
    Local();
    ~Local();

    queue *Queue;
    queue *update(int time); // update to central
    int registration();
    int readfile(const char *filename);
    char str[60];
};

// class Central
// {
// public:
//     Central();
//     void Selection(); // select people with the higest priority
//     void Report();
// };

#endif
