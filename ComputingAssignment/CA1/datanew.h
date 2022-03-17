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
    int addx; 
    int addy;
    char[11] phone;
    char[12] WeChat;
    char[18] email;
};

// basic queue data structure
//TODO:存在外部文件中还是内存中
class Data
{
public:
    Data();

private:
    long timestamp; // YY,MM,DD,HH,MM,SS
    char id[9] = {"12345678"};  //TODO:再说
    char name[10];
    Contact *contact;
    int profession; // I to VIII
    long birth; // format: YYMMDD
    int age_group;
    int risk;
    Data* next = NULL;
};


class Local : public queue
{
public:
    Local();
    int update();   // update to central
    int registration();
};

class Central : public Data
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};

class queue : public Data
{
public:
    queue();
    void push(data* person);
    data* pop();
    int num = 0;
    Data* head = NULL;
    Data* tail = NULL;
}

#endif
