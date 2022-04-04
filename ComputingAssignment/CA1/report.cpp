#include "report.h"
#include "data.h"
#include <typeinfo>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include "timeoffset.h"
#include <new>
using namespace std;

void Report_system::Open_file(Data *head, long timeoffset, int length){
    char choose;
    int your_choice = 0;
    ofstream outfile;
    stringstream ss;

    cout << "A week report is generating..." << endl;
    do{
        cout << "Please choose the order: 1 for name, 2 for profession, 3 for age" << endl;
        cin >> choose;
        ss << choose;
        ss >> your_choice;
        ss.clear();
    }while(1 != your_choice && 2 != your_choice && 3 != your_choice);

    outfile.open("Week.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "————————————WEEK REPORT————————————\n" << endl;
    //已经被治疗的人
    //data->treated = true
    outfile << "-----people who has been treated-----" << endl;
    outfile.close();
    Week(head, your_choice, 4, timeoffset, length, true);

    outfile.open("Week.txt", ios::out | ios::app);
    //已经做了预约但是没有治疗的人，排除withdraw的人
    //appo == true && treated == false && withdraw == false
    outfile << "-----people who has an appointment but not treated yet-----" << endl;
    outfile.close();
    Week(head, your_choice, 5, timeoffset, length, false);

    outfile.open("Week.txt", ios::out | ios::app);
    //做了登记但是没有预约也没有被治疗
    //appo = false && treated = false 或 appo = true && withdraw = true
    outfile << "-----people who has registered but done nothing else-----" << endl;
    outfile.close();
    Week(head, your_choice, 6, timeoffset, length, false);

    outfile.open("Week.txt", ios::out | ios::app);
    outfile << "Reporting has completed." << endl;
    outfile.close();
}
void Report_system::Month(Data *head, long timeoffset){
    ofstream outfile;
    int *keep = new int[6];
    //0:registered
    //1:withdraw
    //2:appo
    //3:waiting
    //4:treated
    //5:waiting time

    for (int i = 0; i <= 5; i++){keep[i] = 0;}
    Data *temp = head;
    while (NULL != temp){
        //people registered
        keep[0] += 1;
        //people withdrawn once
        if (temp->withdrawn){keep[1] += 1;}
        //people ever made an appointment
        if(temp->appo){keep[2] += 1;}
        if (temp->treated){
            keep[4] += 1;
            keep[5] += (temp->appointment->time - temp->timestamp);
        }
        temp = temp->next;
    }
    keep[3] = keep[0] - keep[2] + keep[1];
    //all_waiting_number = Regi_number - all_appointment_number + withdraw_number;
    keep[5] = keep[5] / 1;
    //Waiting_time = keep[5];

    outfile.open("Month.txt", ios::out | ios::trunc);
    if(!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "MONTH REPORT" << endl;

    outfile << "Till now, " << keep[0] << " have been registered."<< endl;

    outfile << keep[3] << " are waiting for an appointment."<< endl;

    outfile << keep[2] << " have received an appointment." << endl;

    outfile << "There are " << keep[1] << " patients who had withdrawn their appointment." << endl;

    long W = keep[5] / 24;
    outfile << "The average waiting time is " << W << " days." << endl;

    outfile << "_____________ENDING_____________" << endl;
    outfile.close();
}
void Report_system::Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating){
    Data *paste;
    long TIME;
    ofstream outfile;

    outfile.open("Week.txt", ios::out | ios::app);
    if (!outfile.is_open()){cout << "Error in Week" << endl; return;}

    switch(Choice){
        case 1:
            paste = Sorting(head, Choice_2, length, 1);

            while (nullptr != paste){
                if (0 == paste->age_group){paste = paste->next; continue;}
                outfile <<  "\n" << paste->name;
                outfile << "Profession: "  << paste->profession << endl;
                outfile << "Age: "  << paste->age_group << endl;
                outfile << "Risk status: "  << paste->risk << endl;
                if (treating){
                    TIME = paste->appointment->time - paste->timestamp;
                    outfile << "Total waiting time: "  << TIME << endl;
                }else{
                    TIME = timeoffset - paste->timestamp;
                    outfile << "Waiting time till now: "  << TIME << endl;
                }
                paste = paste->next;
            }
            break;

        case 2:
            paste = Sorting(head, Choice_2, length, 2);

            while (nullptr != paste){
                if (0 == paste->age_group){paste = paste->next; continue;}
                outfile << "\n" << "Profession: " << paste->profession << endl;
                outfile << "Name: "  << paste->name;
                outfile << "Age: "  << paste->age_group << endl;
                outfile << "Risk status: "  << paste->risk << endl;
                if (treating){
                    TIME = paste->appointment->time - paste->timestamp;
                    outfile << "Total waiting time: "  << TIME << endl;
                }else{
                    TIME = timeoffset - paste->timestamp;
                    outfile << "Waiting time till now: " << TIME << endl;
                }
                paste = paste->next;
            }
            break;

        case 3:
            paste = Sorting(head, Choice_2, length, 3);

            while (nullptr != paste){
                if (0 == paste->age_group){paste = paste->next; continue;}
                outfile << "\n" << "Age group: " << paste->age_group << endl;
                outfile <<"Name: "  << paste->name;
                outfile <<"Profession: "  << paste->profession << endl;
                outfile <<"Risk status: "  << paste->risk << endl;
                if (treating){
                    TIME = paste->appointment->time - paste->timestamp;
                    outfile <<"Total waiting time: "  << TIME << endl;
                }else{
                    TIME = timeoffset - paste->timestamp;
                    outfile <<"Waiting time till now: "  << TIME << endl;
                }
                paste = paste->next;
            }
            break;

        default:
            cout << "It seems that you did not choose a proper order." << endl;
    }
    outfile.close();
}
Data *Report_system::Sorting(Data *head, int Choice_2, int length, int Choice){
    Data *ptr = head;
    Data *temp = new Data[length];
    int i = 0;

    switch(Choice_2){
        case 4:
            while (nullptr != ptr){
            if (!ptr->treated){ptr = ptr->next; continue;}

            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;

            i += 1;
            ptr = ptr->next;
            }
            break;

        case 5:
            while (nullptr != ptr){
            if (ptr->treated || !ptr->appo || (ptr->appo && ptr->withdrawn && !ptr->twice)){ptr = ptr->next; continue;}

            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;

            i += 1;
            ptr = ptr->next;
            }
            break;

        case 6:
            while(nullptr != ptr){
            if ((ptr->appo && !ptr->withdrawn) || (ptr->appo && ptr->withdrawn && !ptr->twice) || ptr->treated){ptr = ptr->next; continue;}

            temp[i].name = ptr->name;
            temp[i].age_group = ptr->age_group;
            temp[i].profession = ptr->profession;
            temp[i].risk = ptr->risk;
            temp[i].timestamp = ptr->timestamp;

            i += 1;
            ptr = ptr->next;
            }
            break;
    }
    switch(Choice){
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
    for (int i = 0; i < length - 1; i++){
        temp[i].next = &temp[i + 1];
    }
    return temp;
}
bool Report_system::cmp_name(Data a, Data b){return strcmp(a.name, b.name) < 0 ? true : false;}
bool Report_system::cmp_profession(Data a, Data b){return a.profession < b.profession;}
bool Report_system::cmp_age(Data a, Data b){return a.age_group < b.age_group;}


