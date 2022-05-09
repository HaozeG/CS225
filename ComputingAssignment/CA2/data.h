#ifndef data_h
#define data_h
// #include "bp_tree.h"

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

    char* id;
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

    char* id;
    int timestamp;
    char* key();
};

class Treatment
{
public:
    Treatment();
    ~Treatment();

    char* id;
    int time;
    int hospital_id;
    char* key();
};

class Appointment
{
public:
    bool appo;
    bool treated;
    bool withdrawn;
};

namespace fibonacci
{
    class Node;
}
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
    char* key(); // return the associated key value according to the sorting type
    // TODO: pointer to Node in Fibonacci Heap
    fibonacci::Node* f_node;

    relation* next;
};

template<class T>
class Block // 0-2 is overflow block
{
public:
    Block();
    ~Block();

    T** block; // place holder == NULL
    T* insert(T* item);
    void sort();
    void bdelete(const char* id);
    T* retrieval(const char* id); // search through the block and return the block+index
    int number;
    int overflow;
    int length;
    int index; // address in blist, beginning from 1
    Block* prev;
    Block* next;
    //     Block* children;
    Block* parent;
    T* split(T* item);
};

template<class T>
class blist
{
public:
    blist();
    ~blist();

    Block<T>* head;
    //static int numitems;
    void merge(Block<T>* block1, Block<T>* block2);
};

// namespace bp_tree
// {
//     class Tree;
// }

class Local
{
public:
    Local();
    ~Local();

    blist<relation>* local;
    int readfile(const char* filename);
    char str[60];
    Block<relation>* update();
};



#endif
