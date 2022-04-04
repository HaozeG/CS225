#include "report.h"
#include "data.h"
#include <typeinfo>
#include <algorithm>

#include <cstddef>
#include <cstring>
#include <cmath>
#include "timeoffset.h"
#include <new>
using namespace std;

void Report_system::Open_file(Data *head, long timeoffset, int length)
{
    string choose;
    int your_choice = 0;
    ofstream outfile;
    stringstream ss;

    const char *one = "1";
    const char *two = "2";
    const char *three = "3";

    cout << "A week report is generating..." << endl;
    do
    {
        cout << "Please choose the order: 1 for name, 2 for profession, 3 for age" << endl;
        cin >> choose;
    } while (0 != strcmp(one, choose.c_str())  && 0 != strcmp(two, choose.c_str()) && 0 != strcmp(three, choose.c_str()));

    ss << choose;
    ss >> your_choice;
    ss.clear();

    outfile.open("./report/Week.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    outfile << "————————————WEEK REPORT————————————\n" << endl;
    outfile << "-----People who have been treated-----" << endl;
    outfile.close();

    Week(head, your_choice, 4, timeoffset, length, true);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Registered people with a set appointment-----" << endl;
    outfile.close();

    Week(head, your_choice, 5, timeoffset, length, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Queueing people without a set appointment-----" << endl;
    outfile.close();

    Week(head, your_choice, 6, timeoffset, length, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "REPORT ENDS" << endl;
    outfile.close();
    return;
}


void Report_system::Month(Data *head, long timeoffset)
{
    ofstream outfile;
    Data *temp = head;
    int *keep = new int[7];
    // 0: How many people have registered?
    // 1: How many of them are waiting?
    // 2: How many are waiting in total?
    // 3: How many people had been treated?
    // 4: Average waiting time
    // 5: How many people had withdrew their registration?
    // 6: How many treatment appointments have been made?

    for (int i = 0; i <= 6; i++){keep[i] = 0;}
    while (NULL != temp)
    {
        keep[0] += 1;
        if(temp->appo && !temp->treated && !temp->withdrawn){keep[1] += 1;}
        if(!temp->appo && !temp->withdrawn){keep[2] += 1;}
        if (temp->treated)
        {
            keep[3] += 1;
            keep[4] += (temp->appointment->time - temp->timestamp);
        }
        if(temp->withdrawn){keep[5] += 1;}
        if (temp->appo || temp->withdrawn){keep[6] += 1;}

        temp = temp->next;
    }

    outfile.open("./report/Month.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "MONTH REPORT" << endl;
    outfile << "How many people have registered? " << keep[0] << endl;
    outfile << "How many of them are waiting? " << keep[1] << endl;
    outfile << "How many are waiting in total? " << keep[2] << endl;
    outfile << "How many treatment appointments have been made? " << keep[6] << endl;
    if(0 ==keep[3])
    {
        outfile << "Average waiting time: " << "0 days 0 hours." << endl;
    }
    else
    {
        outfile << "Average waiting time: " << floor( keep[4] / (24 * keep[3]) ) << " days " << (keep[4] / keep[3]) % 24 << " hours." << endl;
    }
    outfile << "How many people had withdrew their registration? " << keep[5] << endl;
    outfile << "_____________ENDING_____________" << endl;

    outfile.close();
}


void Report_system::Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating)
{
    Data *paste;
    long TIME;
    ofstream outfile;

    outfile.open("./report/Week.txt", ios::out | ios::app);
    if (!outfile.is_open()){cout << "Error in Week" << endl; return;}

    switch (Choice)
    {
    case 1:
        paste = Sorting(head, Choice_2, length, 1);

        while (nullptr != paste)
        {
            if (0 == paste->age_group)
            {
                paste = paste->next;
                continue;
            }
            outfile << "\n" << "Name: " << paste->name;
            outfile << "Profession: " << paste->profession << endl;
            outfile << "Age: " << paste->age_group << endl;
            outfile << "Risk status: " << paste->risk << endl;
            if (treating)
            {
                TIME = paste->appointment->time - paste->timestamp;
                outfile << "Waiting time from registration to treatment: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            else
            {
                TIME = timeoffset - paste->timestamp;
                outfile << "Waiting time until now: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            paste = paste->next;
        }
        break;

    case 2:
        paste = Sorting(head, Choice_2, length, 2);

        while (nullptr != paste)
        {
            if (0 == paste->age_group)
            {
                paste = paste->next;
                continue;
            }
            outfile << "\n"
                    << "Profession: " << paste->profession << endl;
            outfile << "Name: " << paste->name;
            outfile << "Age: " << paste->age_group << endl;
            outfile << "Risk status: " << paste->risk << endl;
            if (treating)
            {
                TIME = paste->appointment->time - paste->timestamp;
                outfile << "Waiting time from registration to treatment: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            else
            {
                TIME = timeoffset - paste->timestamp;
                outfile << "Waiting time until now: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            paste = paste->next;
        }
        break;

    case 3:
        paste = Sorting(head, Choice_2, length, 3);

        while (nullptr != paste)
        {
            if (0 == paste->age_group)
            {
                paste = paste->next;
                continue;
            }
            outfile << "\n"
                    << "Age group: " << paste->age_group << endl;
            outfile << "Name: " << paste->name;
            outfile << "Profession: " << paste->profession << endl;
            outfile << "Risk status: " << paste->risk << endl;
            if (treating)
            {
                TIME = paste->appointment->time - paste->timestamp;
                outfile << "Waiting time from registration to treatment: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            else
            {
                TIME = timeoffset - paste->timestamp;
                outfile << "Waiting time until now: " << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            }
            paste = paste->next;
        }
        break;

    default:
        cout << "It seems that you did not choose a proper order." << endl;
    }
    outfile.close();
}
Data *Report_system::Sorting(Data *head, int Choice_2, int length, int Choice)
{
    Data *ptr = head;
    Data *temp = new Data[length];
    int i = 0;

    switch (Choice_2)
    {
    //People who have been treated
    case 4:
        while (nullptr != ptr)
        {
            if (ptr->treated)
            {
            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;
            temp[i].appointment = ptr->appointment;

            i += 1;
            ptr = ptr->next;
            }
            else
            {
                ptr = ptr->next;
                continue;
            }
        }
        break;
    //Registered people with a set appointment
    case 5:
        while (nullptr != ptr)
        {
            if(ptr->appo && !ptr->treated && !ptr->withdrawn)
            {
            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;
            temp[i].appointment = ptr->appointment;

            i += 1;
            ptr = ptr->next;
            }
            else
            {
                ptr = ptr->next;
                continue;
            }
        }
        break;
    //Queueing people without a set appointment
    case 6:
        while (nullptr != ptr)
        {
            if(!ptr->appo && !ptr->withdrawn)
            {
            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;
            temp[i].appointment = ptr->appointment;

            i += 1;
            ptr = ptr->next;
            }
            else
            {
                ptr = ptr->next;
                continue;
            }
        }
        break;
    }

    switch (Choice)
    {
    case 1:
        sort(temp, temp + length, cmp_name);
        break;
    case 2:
        sort(temp, temp + length, cmp_profession);
        break;
    case 3:
        sort(temp, temp + length, cmp_age);
        break;
    }
    for (int i = 0; i < length - 1; i++)
    {
        temp[i].next = &temp[i + 1];
    }
    return temp;
}
bool Report_system::cmp_name(Data a, Data b) { return strcmp(a.name, b.name) < 0 ? true : false; }
bool Report_system::cmp_profession(Data a, Data b) { return a.profession < b.profession; }
bool Report_system::cmp_age(Data a, Data b) { return a.age_group < b.age_group; }
