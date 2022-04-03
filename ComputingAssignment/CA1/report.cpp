#include "report.h"
#include "data.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <i386/types.h>
#include <new>
using namespace std;
//timeoffset = 当前时间
//length = data中链表的长度
void Report_system::Open_file(Data *head, long timeoffset, int length){
    int your_choice = 0;
    ofstream outfile;

    cout << "A weekly report is generating..." << endl;
    do{
        cout << "Please choose the order: 1 for name, 2 for profession, 3 for age" << endl;
        cin >> your_choice;
    }while( 1 != your_choice || 2 != your_choice || 3 != your_choice);

    outfile.open("Week.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "————————————WEEK REPORT————————————\n" << endl;
    //已经被治疗的人
    //data->treated = true
    outfile << "\f-----people who has been treated-----" << endl;
    outfile.close();
    Week(head, your_choice, 4, timeoffset, length, true);

    outfile.open("Week.txt", ios::out | ios::app);
    //已经做了预约但是没有治疗的人，排除withdraw的人
    //appo == true && treated == false && withdraw == false
    outfile << "\f-----people who has an appointment but not treated yet-----" << endl;
    outfile.close();
    Week(head, your_choice, 5, timeoffset, length, false);

    outfile.open("Week.txt", ios::out | ios::app);
    //做了登记但是没有预约也没有被治疗
    //appo = false && treated = false 或 appo = true && withdraw = true
    outfile << "\f-----people who has registered but done nothing else-----" << endl;
    outfile.close();
    Week(head, your_choice, 6, timeoffset, length, false);

    outfile.open("Week.txt", ios::out | ios::app);
    outfile << "Reporting has completed." << endl;
    outfile.close();
}
//head: data头节点
//timeoffset:当前时间
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
    int *returnNumber = keep;
    Data *temp = head;
    while (NULL != temp){
        //people registered
        keep[0] += 1;
        Regi_number += 1;
        //people withdrawn once
        if (temp->withdrawn){withdraw_number += 1; keep[1] += 1;}
        //people ever made an appointment
        if(temp->appo){all_appointment_number += 1; keep[2] += 1;}
        if (temp->treated){
            keep[4] += 1;
            keep[5] += (temp->appointment->time - temp->timestamp);
        }
        temp = temp->next;
    }
    keep[3] = keep[0] - keep[2] + keep[1];
    all_waiting_number = Regi_number - all_appointment_number + withdraw_number;
    keep[5] = keep[5] / keep[4];
    Waiting_time = keep[5];

    outfile.open("Month.txt", ios::out | ios::trunc);
    if(!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "MONTH REPORT" << endl;

    outfile << "Till now, " << Regi_number << "have been registered."<< endl;

    outfile << all_waiting_number << "is waiting for an appointment."<< endl;

    outfile << all_appointment_number << "have received an appointment." << endl;

    outfile << "There are " << withdraw_number << "patients who had withdrawn their appointment." << endl;

    long W = Waiting_time / 24;
    outfile << "The average waiting time is " << W << "days." << endl;

    outfile << "_____________ENDING_____________" << endl;
    outfile.close();
}
//choice = 排序顺序
//choice_2 = treated || appointed || registered
//offset = 当前时间
//length:data中单链表的长度
//treating: 是否已经被治疗了
void Report_system::Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating){
    Data *paste;
    long TIME;
    ofstream outfile;

    outfile.open("Week.txt", ios::out | ios::app);
    if (!outfile.is_open()){cout << "Error in Week" << endl; return;}

    switch(Choice){
        case 1:
            paste = Sorting(head, Choice_2, length, true);

            while (nullptr != paste){
                outfile <<  paste->name;
                outfile << "Profession:" << "\f" << paste->profession << endl;
                outfile << "Age:" << "\f" << paste->age_group << endl;
                outfile << "Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    outfile << "Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    outfile << "Waiting time till now" << "\f" << TIME << endl;
                }      
                paste = paste->next;
            }
            break;

        case 2:
            paste = Sorting(head, Choice_2, length, false);

            while (nullptr != paste){
                outfile << paste->profession << endl;
                outfile << "Name:" << "\f" << paste->name;
                outfile << "Age:" << "\f" << paste->age_group << endl;
                outfile << "Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    outfile << "Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    outfile << "Waiting time till now:" << "\f" << TIME << endl;
                } 
                paste = paste->next;     
            }
            break;

        case 3:
            paste = Sorting(head, Choice_2, length, false);

            while (nullptr != paste){
                outfile << paste->age_group << endl;
                outfile <<"Name:" << "\f" << paste->name;
                outfile <<"Profession:" << "\f" << paste->profession << endl;
                outfile <<"Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    outfile <<"Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    outfile <<"Waiting time till now:" << "\f" << TIME << endl;
                }      
                paste = paste->next;
            }
            break;

        default:
            cout << "It seems that you did not choose a proper order." << endl;
    }
    outfile.close();
}
Data *Report_system::Sorting(Data *head, int number, int length, bool NAME){
    Data *ptr = head;
    Data *temp = new Data[length];
    int i = 0;

    switch(number){
        case 4:
            while (nullptr != ptr){
            if (!ptr->treated){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
            }
            break;

        case 5:
            while (nullptr != ptr){
            if (!ptr->appo || ptr->treated || ptr->withdrawn){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
            }
            break;
            
        case 6:
            while(nullptr != ptr){
            if (ptr->appo && !ptr->withdrawn){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
            }
            break;
    }

    if (NAME){
        sort(temp, temp + length, cmp_name);
    }else{
        sort(temp, temp + length, cmp);
    }
    return temp;
}
bool Report_system::cmp(Data a, Data b){return a.profession < b.profession ? -1 : 1;}
bool Report_system::cmp_name(Data a, Data b){return strcmp(a.name, b.name);}