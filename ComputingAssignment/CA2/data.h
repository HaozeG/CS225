#ifndef data_h
#define data_h
using namespace std;

/*class Contact
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
};*/

class Person
{
public:
    Person();
    ~Person();

    char* id;
    char* name;
    int profession;
    char* birth;
    int age_group;
    int addx;
    int addy;
    char* phone;
    char* WeChat;
    char* email;
    char* key();
};

class Status
{
public:
    Status();
    ~Status();

    int risk;
    int priority;
    int type; // treatment type, leading to different priority rule
    char* key();
    // Three different rule: register time, risk status, priority
};

class Registration
{
public:
    Registration();
    ~Registration();

    int timestamp;
    char* key();
};

class Treatment
{
public:
    Treatment();
    ~Treatment();

    int time;
    int hospital_id;
    char* key();
};

class Appointment
{
public:
    bool in_alist = false;  // whether in Alist or not
    long time;
    int hospital_id;

    bool appo;
    bool treated;
    bool withdrawn;
};

class relation
{
public:
    relation();
    ~relation();

    Appointment* appoint;
    Person* person;
    Status* status;
    Registration* registration;
    Treatment* treatment;
    int key(); // return the associated key value according to the sorting type
};

class Block // 0-2 is overflow block
{
public:
    Block();
    ~Block();

    relation** block; // place holder == NULL
    void insert(relation* item);
    void sort();
    void bdelete(const char* id);
    relation* retrieval(const char* id); // search through the block and return the block+index
    int number;
    int overflow;
    int length;
    int index; // address in blist, beginning from 1
    Block* prev;
    Block* next;
    Block* children;
    Block* parent;
    relation* split(relation* item);
};

class blist
{
public:
    blist();
    ~blist();

    Block* head;
    //static int numitems;
    void merge(Block* block1, Block* block2);
};

class Local
{
public:
    Local();
    ~Local();

    blist* local;
    int readfile(const char* filename);
    char str[60];
};

#endif
