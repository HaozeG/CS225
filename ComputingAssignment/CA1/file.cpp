#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "data.h"
#include<stdlib.h>
using std::cout;
using std::cin;
#include <cstring>
#include <time.h>

// identification number; name; address; phone; WeChat; email; profession; date of birth;
// risk status; timestamp; age group;
//: id, name, address, phone, WeChat, email, profession, birth, risk, timestamp and age group.
// Be careful or you need to start from the beginning

Local::Local()
{
    Queue = new queue();
    cout << "Create new local registry\n";
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

Data::Data()
{
    timestamp = 0;
    id = new char[10];
    name = new char[5];
    contact = new Contact();
    profession = 0;
    birth = new char[8];
    age_group = 0;
    risk = 0;
    next = NULL;
}

queue::queue()
{
    num = 0;
    head = NULL;
    tail = NULL;
    cout << "New queue\n";
}

queue::~queue()
{
    cout << "Delete queue\n";
}

Data* queue::pop()
{
    if (0 == num)
    {
        return NULL;
    }
    else
    {
        Data *temp = queue::head;
        int i = 1;
        while (i < num)
        {
            temp = temp->next;
            i++;
        }
        num--;
        temp->next = NULL;
        queue::tail = (0 == num ? NULL : temp);
        queue::head = (0 == num ? NULL : queue::head);
        return temp;
    }
    return head;
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
        queue::tail->next = person;
        queue::tail = person;
    }
    queue::num++;
}

int Local::registration()
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
}

int Local::readfile(const char* filename,long timeoffset)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL) {
     perror("打开文件时发生错误");
     return(-1);
    }
    fgets (str, 60, fp);
    str[1] = '\0';
    int i = atoi(str);
    for (; i>0; i--)
    {
        Data* person = new Data();
        if( fgets (person->id, 60, fp)!=NULL )
            person->id[10]='\0';
        else return 0;
        if( fgets (person->name, 60, fp)!=NULL )
            person->name[5]='\0';
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[2]='\0';
            int a_x = atoi(str);
            person->contact->addx = a_x;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[2]='\0';
            int a_y = atoi(str);
            person->contact->addy = a_y;
        }
        else return 0;
        if( fgets (person->contact->phone, 60, fp)!=NULL )
            person->contact->phone[11]='\0';
        else return 0;
        if( fgets (person->contact->WeChat, 60, fp)!=NULL )
            person->contact->WeChat[7]='\0';
        else return 0;
        if( fgets (person->contact->email, 60, fp)!=NULL )
            person->contact->email[15]='\0';
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            person->profession = a;
        }
        else return 0;
        if( fgets (person->birth, 60, fp)!=NULL )
            person->birth[8]='\0';
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            person->risk = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            person->timestamp = a + timeoffset;
        }
        else return 0;
        //time_t curtime;
        //person->timestamp = time(&curtime);
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            person->age_group = a;
        }
        else return 0;
        Queue->push(person);
    }
    fclose(fp);
    return 1;
}

// 传递class指针，需要什么形式？
// 如何传递，或者是center call local的函数？
// 两个local
queue* Local::update(int time)
{
    // 判断timestamp再传递
     queue* pack = new queue();
    if (Queue->num == 0 || Queue->head->timestamp > time) return pack;
    Data* tem = Queue->head; //
    while (Queue->num > 0 && tem->timestamp <= time)
    {
        tem = tem->next;
        pack->push(Queue->pop());
    }
    return pack;
}
