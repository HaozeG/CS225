#ifndef data_h
#define data_h
#include <time.h>
#include <stdint.h>
#include <string>
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

// basic queue data structure
//TODO:存在外部文件中还是内存中
class Data
{
public:
    Data();


    long timestamp; // YY,MM,DD,HH,MM,SS
    char* id;  //TODO:再说
    char* name;
    Contact *contact;
    int profession; // I to VIII
    char* birth; // format: YYMMDD
    int age_group;
    int risk;
    Data* next = NULL;
};

class queue : public Data
{
public:
    queue();
    void push(Data* person);
    Data* pop();
    int num = 0;
    Data* head = NULL;
    Data* tail = NULL;
};

class Local : public queue
{
public:
    Local();
    queue* Queue;
    queue* update(int time);   // update to central
    int registration();
    int readfile(const char* filename);
    char str[60];
};

class Central : public Data
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};



#endif
