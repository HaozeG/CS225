#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
// #include <time.h>
#include "data.h"
#include "timeoffset.h"
using std::cout;
// using std::cin;

// identification number; name; address; phone; WeChat; email; profession; date of birth;
// risk status; timestamp; age group;
//: id, name, address, phone, WeChat, email, profession, birth, risk, timestamp and age group.
// Be careful or you need to start from the beginning

Local::Local()
{
    Queue = new queue();
    cout << "Create one local registry\n";
}

Local::~Local()
{
    delete Queue;
    cout << "Delete one local registry\n";
}

Contact::Contact()
{
    addx = 0;
    addy = 0;
    phone = new char[11];
    WeChat = new char[7];
    email = new char[15];
}

Contact::~Contact()
{
    delete phone;
    delete WeChat;
    delete email;
}

Data::Data()
{
    withdrawn = false;
    appo = false;
    treated = false;
    twice = false;
    appointment = new Appointment();
    timestamp = 0;
    id = new char[10];
    name = new char[5];
    contact = new Contact();
    profession = 0;
    birth = new char[8];
    age_group = 0;
    risk = 0;
    next = nullptr;
    priority = 0;
    locale = -1;
    // cout << "Create data\n";
}

Data::~Data()
{
    // has some problems in copying the content of pointers
    // delete appointment;
    // delete contact;
    // delete id;
    // delete birth;
    // cout << "Delete data\n";
}

queue::queue()
{
    num = 0;
    head = nullptr;
    tail = nullptr;
    cout << "Create queue\n";
}

queue::~queue()
{
    cout << "Delete queue\n";
}

void queue::push(Data *person)
{
    if (0 == num)
    {
        queue::head = person;
        queue::tail = person;
    }
    else
    {
        person->next = head;
        head = person;
    }
    queue::num++;
    cout << "push one data\n";
}


Data* queue::pop()
{
    if (num == 0)
    {
        cout<<"queue is empty now!\n";
        return nullptr;
    }
    num -= 1;
    Data* element = head;
    head = head->next;
    tail = (0 == num ? nullptr : tail);
    element->next = nullptr;
    return element;
}

/*int Local::registration()
{
    FILE *fp; char filename[8] ;
    cout<<"Please type your file name within eight characters."<<endl;
    cin>>filename;
    if (fp = fopen(filename, "w+")) // 怎么起不同的文件名？
    {
        char name[10]; char phone[11]; char WeChat[12]; char email[18]; char id[9]; char birth[9];
        int profession, risk, age_group, addx, addy; long timestamp;
        cout<<"Please type in the information in order."<<endl;
        if (cin>>id && cin>>name && cin>>addx && cin>>addy && cin>>phone && cin>>WeChat && cin>>email &&
            cin>>profession && cin>>birth && cin>>risk && cin>>timestamp && cin>>age_group)
        {
            if (fprintf(fp,"%s",id)<0 || fprintf(fp,"%s",name)<0 || fprintf(fp,"%d",addx)<0 ||
                fprintf(fp,"%d",addx)<0 || fprintf(fp,"%s",phone)<0 || fprintf(fp,"%s",WeChat)<0 ||
                fprintf(fp,"%s",email)<0 || fprintf(fp,"%d",profession)<0 || fprintf(fp,"%s",birth)<0 ||
                fprintf(fp,"%d",risk)<0 || fprintf(fp,"%ld",timestamp)<0 || fprintf(fp,"%d",age_group)<0)
                {
                    fclose(fp);
                    cout<<"Error when storing."<<endl;
                    return 0;
                }
            else
            {
                fclose(fp);
                return 1;
            }
        }
        else cout<<"Sorry! Your input is in the wrong format."<<endl;
        return 0;
    }
    else
    {
        cout<<"Error when opening the file."<<endl;
        return 0;
    }
}*/

int Local::readfile(const char* filename, int locale)
{
    FILE *fp;
    fp = fopen(filename , "r");
    if(fp == nullptr) {
        perror("打开文件时发生错误");
        return(-1);
    }
    fgets (str, 60, fp);
    str[1] = '\0';
    int i = atoi(str);
    for (; i>0; i--)
    {
        Data* person = new Data();
        if( fgets (person->id, 60, fp)!=nullptr )
            person->id[10]='\0';
        else return 0;
        if( fgets (person->name, 60, fp)==nullptr )
            return 0;// cout<<person->name;
        if( fgets (str, 60, fp)!=nullptr )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            person->contact->addx = a;
            // cout<<person->contact->addx<<"\n";
        }
        else return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            person->contact->addy = a;
            // cout<<person->contact->addy<<"\n";
        }
        else return 0;
        if( fgets (person->contact->phone, 60, fp)!=nullptr )
            person->contact->phone[11]='\0';
        else return 0;
        if( fgets (person->contact->WeChat, 60, fp)==nullptr )
            return 0;
        if( fgets (person->contact->email, 60, fp)==nullptr )
            return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            str[1]='\0';
            int a = atoi(str);
            person->profession = a;
        }
        else return 0;
        if( fgets (person->birth, 60, fp)!=nullptr )
            person->birth[8]='\0';
        else return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            str[1]='\0';
            int a = atoi(str);
            person->risk = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            person->timestamp = a - (timestart*100) + 24 * (a/100 - timestart) + 30 * 24 * (a/10000 - timestart/100);
        }
        else return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            str[1]='\0';
            int a = atoi(str);
            person->age_group = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=nullptr )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            person->priority = a;
            // cout<<person->priority<<"\n";
        } else
          return 0;
        person->locale = locale;
        Queue->push(person);
    }
    fclose(fp);
    return 1;
}

// // 传递class指针，需要什么形式？
// // 如何传递，或者是center call local的函数？
// // 两个local
// queue* Local::update(int time)
// {
//     // 判断timestamp再传递
//      queue* pack = new queue();
//     if (Queue->num == 0 || Queue->head->timestamp > time) return pack;
//     Data* tem = Queue->head; //
//     while (Queue->num > 0 && tem->timestamp <= time)
//     {
//         tem = tem->next;
//         pack->push(Queue->pop());
//     }
//     return pack;
// }
