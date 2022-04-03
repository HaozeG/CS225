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
    cout << "A weekly report is generating..." << endl;
    do{
        cout << "Please choose the order: 1 for name, 2 for profession, 3 for age" << endl;
        cin >> your_choice;
    }while( 1 != your_choice || 2 != your_choice || 3 != your_choice);

    ofstream outfile;
    outfile.open("Week.txt", ios::out);
    cout << "————————————WEEK REPORT————————————\n" << endl;
    //已经被治疗的人
    //data->treated = true
    cout << "\f-----people who has been treated-----" << endl;
    Week(head, your_choice, 4, timeoffset, length, true);
    //已经做了预约但是没有治疗的人，排除withdraw的人
    //appo == true && treated == false && withdraw == false
    cout << "\f-----people who has an appointment but not treated yet-----" << endl;
    Week(head, your_choice, 5, timeoffset, length, false);
    //做了登记但是没有预约也没有被治疗
    //appo = false && treated = false 或 appo = true && withdraw = true
    cout << "\f-----people who has registered but done nothing else-----" << endl;
    Week(head, your_choice, 6, timeoffset, length, false);

    cout << "Reporting has completed." << endl;
    outfile.close();
}
//head: data头节点
//timeoffset:当前时间
void Report_system::Month(Data *head, long timeoffset){
    //0:registered
    //1:withdraw
    //2:appo
    //3:waiting
    //4:treated
    //5:waiting time
    int *keep = new int[6];
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

    ofstream outfile;
    outfile.open("Month.txt", ios::out | ios::trunc);
    cout << "MONTH REPORT" << endl;

    cout << "Till now, " << Regi_number << "have been registered."<< endl;

    cout << all_waiting_number << "is waiting for an appointment."<< endl;

    cout << all_appointment_number << "have received an appointment." << endl;

    cout << "There are " << withdraw_number << "patients who had withdrawn their appointment." << endl;

    long W = Waiting_time / 24;
    cout << "The average waiting time is " << W << "days." << endl;

    cout << "_____________ENDING_____________" << endl;
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
    switch(Choice){
        case 1:
            paste = Sorting(head, Choice_2, length, true);

            while (nullptr != paste){
                cout <<  paste->name;
                cout << "Profession:" << "\f" << paste->profession << endl;
                cout << "Age:" << "\f" << paste->age_group << endl;
                cout << "Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    cout << "Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    cout << "Waiting time till now" << "\f" << TIME << endl;
                }      
                paste = paste->next;
            }
            break;

        case 2:
            paste = Sorting(head, Choice_2, length, false);

            while (nullptr != paste){
                cout << paste->profession << endl;
                cout << "Name:" << "\f" << paste->name;
                cout << "Age:" << "\f" << paste->age_group << endl;
                cout << "Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    cout << "Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    cout << "Waiting time till now:" << "\f" << TIME << endl;
                } 
                paste = paste->next;     
            }
            break;

        case 3:
             paste = Sorting(head, Choice_2, length, false);

            while (nullptr != paste){
                cout << paste->age_group << endl;
                cout <<"Name:" << "\f" << paste->name;
                cout <<"Profession:" << "\f" << paste->profession << endl;
                cout <<"Risk status:" << "\f" << paste->risk << endl;
                if (treating){
                    TIME = timeoffset - paste->timestamp;
                    cout <<"Total waiting time:" << "\f" << TIME << endl;
                }else{
                    TIME = paste->appointment->time;
                    cout <<"Waiting time till now:" << "\f" << TIME << endl;
                }      
                paste = paste->next;
            }
            break;

        default:
            cout << "It seems that you did not choose a proper order." << endl;
    }
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