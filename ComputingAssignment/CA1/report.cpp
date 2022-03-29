#include <runetype.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/_types/_time_t.h>
#include <time.h>
#include "fibonacii_heap.h"
#include "data.h"
#include "report.h"

using namespace std;
//for weekly report, choose the order 
int Report_system::weekly_choice(){
    char input[100];
    cout << "A weekly report is generating" << endl;
    cout << "choose the order: 1 for name, 2 for profession, 3 for age" << endl;
    cin.getline(input,1);
    return (int)input[0];
}
//open file for weekly report
void Report_system::open_file(Data *data, int Choice, Brutal_node *ptr){
    ofstream outfile;
    outfile.open("Week.txt", ios::out | ios::trunc);
    cout << "WEEK REPORT\n" << endl;
    cout << "-----people who has been treated-----" << endl;
    Writing_weekly(data, Choice, 4, ptr);
    cout << "-----people who has an appointment but not treated yet-----" << endl;
    Writing_weekly(data, Choice, 5, ptr);
    cout << "-----people who has registered but done nothing else-----" << endl;
    Writing_weekly(data, Choice, 6, ptr);
    cout << "Reporting has completed." << endl;
    outfile.close();
    return;
}

void Report_system::Writing_weekly(Data *data, int Choice, int Choice_2, Brutal_node *ptr){
    //first of all. copy a list
    Copied_list(data, ptr);
    if (1 == Choice){
        sort_by_age(ptr, Choice_2);
    }
    else if (2 == Choice){
        sort_by_profession(ptr, Choice_2);
    }
    else if (3 == Choice){
        sort_by_age(ptr, Choice_2);
    }
    else {
        cout << "It seems that you did not choose a proper order." << endl;
    }
    return;
}

//open file for monthly report
void Report_system::file_month(){
    ofstream outfile;
    outfile.open("Month.txt", ios::out | ios::trunc);
    cout << "MONTH REPORT" << endl;
    std::stringstream ss;

    //print out 
    ss << Regi_number;
    std::string Regi = ss.str();
    cout << "Till now, " << Regi << "have been registered."<< endl;

    ss << all_waiting_number;
    std::string Wait = ss.str();
    cout << Wait << "is waiting for an appointment."<< endl;

    ss << all_appointment_number;
    std::string Appo = ss.str();
    cout << Appo << "have received an appointment." << endl;

    double i = RMS_waiting_time / (all_appointment_number * 60 * 60);
    ss << i;
    std::string average = ss.str();
    cout <<"Patients have an average waiting time of "<< average << "hours." << endl;

    ss << withdraw_number;
    std::string Without = ss.str();
    cout << "There are " << Without << "patients who had withdrawn their appointment." << endl;

    cout << "_____________ENDING_____________" << endl;
    outfile.close();
}

void Report_system::stat(Data *data){
    while (NULL != data){
        //people registered
        Regi_number += 1;
        //people withdrawn once
        if (data->withdrawn){withdraw_number += 1;}
        //people ever made an appointment
        if(data->appointment->registered){all_appointment_number += 1;}
        data = data->next;
    }
    all_waiting_number = Regi_number - all_appointment_number;
    return;
}

//copy a list for sorting
Brutal_node *Report_system::Copied_list(Data *data, Brutal_node *ptr){
    //first node is a dummy
    Brutal_node *pre = ptr;
    Brutal_node *cur;
    while(NULL != data){
        cur->ptr_to_data = data;
        ptr->next = cur;
        ptr = cur;
        cur = ptr->next;
        data = data->next;
    }
    ptr = pre;
    return ptr;
}

void Report_system::sort_by_name(Brutal_node *ptr, int number){
    //people being treated
    if (4 == number){
        while (NULL != ptr){
            //如果此人没有被治疗过直接跳到下一个
            if (!ptr->ptr_to_data->treated){
                ptr = ptr->next;
                continue;
            }



        }
    }
    //people made an appointment
    else if (5 == number){
        while (NULL != ptr){
            //如果此人没有登记治疗过直接跳到下一个
            if (!ptr->ptr_to_data->appo){
                ptr = ptr->next;
                continue;
            }


        }

    }
    //people registered
    else {
        while (NULL != ptr){


        }
    }
    return;
}


Brutal_node *Report_system::sort_by_profession(Brutal_node *ptr, int number){
    Brutal_node *I, *II, *III, *IV, *V, *VI, *VII, *VIII;
    Brutal_node *I_pre, *II_pre, *III_pre, *IV_pre, *V_pre, *VI_pre, *VII_pre, *VIII_pre;
    Brutal_node *keepI = I, *keepII = II, *keepIII = III, *keepIV = IV, *keepV = V;
    Brutal_node *keepVI = VI;
    Brutal_node *keepVII = VII;
    Brutal_node *keepVIII = VIII;

    //people being treated
    if (4 == number){
        while (NULL != ptr){
            //如果此人没有被治疗过直接跳到下一个
            if (!ptr->ptr_to_data->treated){ptr = ptr->next; continue;}
            //根据profession分别塞入不同的链表中
            switch(ptr->ptr_to_data->profession){
                case 1:
                    I->ptr_to_data = ptr->ptr_to_data; I_pre = I; I = I->next;
                    break;
                case 2:
                    II->ptr_to_data = ptr->ptr_to_data; II_pre = II; II = II->next;
                    break; 
                case 3:
                    III->ptr_to_data = ptr->ptr_to_data; III_pre = III; III = III->next;
                    break;
                case 4:
                    IV->ptr_to_data = ptr->ptr_to_data; IV_pre = IV; IV = IV->next;
                    break;   
                case 5:
                    V->ptr_to_data = ptr->ptr_to_data; V_pre = V; V = V->next;
                    break;
                case 6:
                    VI->ptr_to_data = ptr->ptr_to_data; VI_pre = VI; VI = VI->next;
                    break;
                case 7:
                    VII->ptr_to_data = ptr->ptr_to_data; VII_pre = VII; VII = VII->next;
                    break; 
                case 8:
                    VIII->ptr_to_data = ptr->ptr_to_data; VIII_pre = VIII; VIII = VIII->next;
                    break;
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            //移到下一个元素
            ptr = ptr->next;
        }
    }else if (5 == number){
        while (NULL != ptr){
            //如果此人没有登记过,或者撤回了，直接跳到下一个
            if (!ptr->ptr_to_data->appo || ptr->ptr_to_data->withdrawn){ptr = ptr->next; continue;}
            //根据profession分别塞入不同的链表中
            switch(ptr->ptr_to_data->profession){
                case 1:
                    I->ptr_to_data = ptr->ptr_to_data; I_pre = I; I = I->next;
                    break;
                case 2:
                    II->ptr_to_data = ptr->ptr_to_data; II_pre = II; II = II->next;
                    break; 
                case 3:
                    III->ptr_to_data = ptr->ptr_to_data; III_pre = III; III = III->next;
                    break;
                case 4:
                    IV->ptr_to_data = ptr->ptr_to_data; IV_pre = IV; IV = IV->next;
                    break;   
                case 5:
                    V->ptr_to_data = ptr->ptr_to_data; V_pre = V; V = V->next;
                    break;
                case 6:
                    VI->ptr_to_data = ptr->ptr_to_data; VI_pre = VI; VI = VI->next;
                    break;
                case 7:
                    VII->ptr_to_data = ptr->ptr_to_data; VII_pre = VII; VII = VII->next;
                    break; 
                case 8:
                    VIII->ptr_to_data = ptr->ptr_to_data; VIII_pre = VIII; VIII = VIII->next;
                    break;
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            //移到下一个元素
            ptr = ptr->next;
        }
    }else{
        while (NULL != ptr){
            //根据profession分别塞入不同的链表中
            switch(ptr->ptr_to_data->profession){
                case 1:
                    I->ptr_to_data = ptr->ptr_to_data; I_pre = I; I = I->next;
                    break;
                case 2:
                    II->ptr_to_data = ptr->ptr_to_data; II_pre = II; II = II->next;
                    break; 
                case 3:
                    III->ptr_to_data = ptr->ptr_to_data; III_pre = III; III = III->next;
                    break;
                case 4:
                    IV->ptr_to_data = ptr->ptr_to_data; IV_pre = IV; IV = IV->next;
                    break;   
                case 5:
                    V->ptr_to_data = ptr->ptr_to_data; V_pre = V; V = V->next;
                    break;
                case 6:
                    VI->ptr_to_data = ptr->ptr_to_data; VI_pre = VI; VI = VI->next;
                    break;
                case 7:
                    VII->ptr_to_data = ptr->ptr_to_data; VII_pre = VII; VII = VII->next;
                    break; 
                case 8:
                    VIII->ptr_to_data = ptr->ptr_to_data; VIII_pre = VIII; VIII = VIII->next;
                    break;
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            //移到下一个元素
            ptr = ptr->next;
        }
    }
    //合成大西瓜！
    I_pre->next = keepII;
    II_pre->next = keepIII;
    III_pre->next = keepIV;
    IV_pre->next = keepV;
    V_pre->next = keepVI;
    VI_pre->next = keepVII;
    VII_pre->next = keepVIII;
    //返回已合成链表的头节点
    return keepI;
}

void Report_system::sort_by_age(Brutal_node *ptr, int number){
    //people being treated
    if (4 == number){
        while (NULL != ptr){
            //如果此人没有被治疗过直接跳到下一个
            if (!ptr->ptr_to_data->treated){ptr = ptr->next;continue;}


        }
    }else if (5 == number){
        while (NULL != ptr){
            //如果此人没有登记治疗过直接跳到下一个
            if (!ptr->ptr_to_data->appo){ptr = ptr->next;continue;}


        }

    }else {
        while (NULL != ptr){


        }
    }
    return;
}
