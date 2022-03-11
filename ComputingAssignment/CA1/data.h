#include <stdint.h>
#include <string>
using namespace std;

// basic queue data structure
//TODO:存在外部文件中还是内存中
template<class T> class Data
{
public:
    Data();

private:
    int timestamp[6]; // YY,MM,DD,HH,MM,SS
    char id[8] = {"12345678"};  //TODO:再说
    string name;
    Contact contact;
    int profession; // I to VIII
    long birth; // format: YYMMDD
    int age_group;
};

template<class T> class Contact
{
private:
    string address;
    T phone;
    T WeChat;
    T email;
};

template<class T> class Local : public Data
{
public:
    Local();
    int update();   // update to central

private:
    T *queue;   // the queue of all local records
};

template<class T> class Central
{
public:
    Central();
    void Selection(); // select people with the higest priority
    void Report();
};
