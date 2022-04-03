#include "report.h"
#include "data.h"
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <i386/types.h>
#include <new>
using namespace std;

//对于每周报告，主程序中只需要调用Open——file
//open file for weekly report； 
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
//对于每月报告，主程序中需要调用month
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

    ss << withdraw_number;
    std::string Without = ss.str();
    cout << "There are " << Without << "patients who had withdrawn their appointment." << endl;

    long W = Waiting_time / 24;
    ss << W;
    std::string avg = ss.str();
    cout << "The average waiting time is " << avg << "days." << endl;

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
    int TIME;
    //名字
    if (1 == Choice){
        paste = Sorting(head, Choice_2, length, true);

        std::stringstream ss;
        while (nullptr != paste){
            cout <<  paste->name;

            ss << paste->profession;
            std::string profession = ss.str();
            cout << "Profession:" << "\f" << profession << endl;

            ss << paste->age_group;
            std::string age = ss.str();
            cout << "Age:" << "\f" << age << endl;

            ss << paste->risk;
            std::string risk = ss.str();
            cout << "Risk status:" << "\f" << risk << endl;

            if (treating){
                TIME = timeoffset - paste->timestamp;
                ss << TIME;
                std::string TIME = ss.str();
                cout << "Total waiting time:" << "\f" << TIME << endl;
            }else{
                TIME = paste->appointment->time;
                ss << TIME;
                std::string TIME = ss.str();
                cout << "Waiting time till now" << "\f" << TIME << endl;
            }      

            paste = paste->next;
        }
    }
    //职业
    else if (2 == Choice){
        paste = Sorting(head, Choice_2, length, false);
        std::stringstream ss;
        while (nullptr != paste){

            ss << paste->profession;
            std::string profession = ss.str();
            cout << profession << endl;

            cout << "Name:" << "\f" << paste->name;

            ss << paste->age_group;
            std::string age = ss.str();
            cout << "Age:" << "\f" << age << endl;

            ss << paste->risk;
            std::string risk = ss.str();
            cout << "Risk status:" << "\f" << risk << endl;

            if (treating){
                TIME = timeoffset - paste->timestamp;
                ss << TIME;
                std::string TIME = ss.str();
                cout << "Total waiting time:" << "\f" << TIME << endl;
            }else{
                TIME = paste->appointment->time;
                ss << TIME;
                std::string TIME = ss.str();
                cout << "Waiting time till now:" << "\f" << TIME << endl;
            } 

            paste = paste->next;     
        }
    }
    //如果选择用年龄排序，默认年龄是1～7
    else if (3 == Choice){
        paste = Sorting(head, Choice_2, length, false);
        std::stringstream ss;
        while (nullptr != paste){

            ss << paste->age_group;
            std::string age = ss.str();
            cout << age << endl;

            cout <<"Name:" << "\f" << paste->name;

            ss << paste->profession;
            std::string profession = ss.str();
            cout <<"Profession:" << "\f" << profession << endl;

            ss << paste->risk;
            std::string risk = ss.str();
            cout <<"Risk status:" << "\f" << risk << endl;

            if (treating){
                TIME = timeoffset - paste->timestamp;
                ss << TIME;
                std::string TIME = ss.str();
                cout <<"Total waiting time:" << "\f" << TIME << endl;
            }else{
                TIME = paste->appointment->time;
                ss << TIME;
                std::string TIME = ss.str();
                cout <<"Waiting time till now:" << "\f" << TIME << endl;
            }      

            paste = paste->next;
        }
    }
    else {
        //为了保证这种情况不会发生，也许需要在一开始选择顺序时加一个循环
        cout << "It seems that you did not choose a proper order." << endl;
    }
    return;
}
Data *Report_system::Sorting(Data *head, int number, int length, bool NAME){
    Data *ptr = head;
    Data *temp = new Data[length];
    Data *keep = temp;
    int i = 0;

    if (4 == number){
        while (nullptr != ptr){
            if (!ptr->treated){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
        }
    }else if (5 == number){
        while (nullptr != ptr){
            if (!ptr->appo || ptr->treated || ptr->withdrawn){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
        }
    }else{
        while(nullptr != ptr){
            if (ptr->appo && !ptr->withdrawn){ptr = ptr->next; continue;}
            temp[i] = *ptr;
            i += 1;
            ptr = ptr->next;
        }
    }
    if (NAME){
        sort(keep, keep + length, cmp_name);
    }else{
        sort(keep, keep + length, cmp);
    }
    return keep;
}
bool Report_system::cmp(Data *a, Data *b){return a->profession < b->profession ? -1 : 1;}
bool Report_system::cmp_name(Data *a, Data *b){return strcmp(a->name, b->name);}


/*
便于统一修改shit mountain 代码
        while (NULL != ptr){
            //根据profession分别塞入不同的链表中
            switch(ptr->ptr_to_data->profession){
                case 1:
                    I->ptr_to_data = ptr->ptr_to_data; I = I->next;
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




                    case 1:
                    I->ptr_to_data = ptr->ptr_to_data; I = I->next = new Brutal_node();
                    break;
                case 2:
                    II->ptr_to_data = ptr->ptr_to_data; II = II->next = new Brutal_node();
                    break; 
                case 3:
                    III->ptr_to_data = ptr->ptr_to_data; III = III->next = new Brutal_node();
                    break;
                case 4:
                    IV->ptr_to_data = ptr->ptr_to_data; IV = IV->next = new Brutal_node();
                    break;   
                case 5:
                    V->ptr_to_data = ptr->ptr_to_data; V = V->next = new Brutal_node();
                    break;
                case 6:
                    VI->ptr_to_data = ptr->ptr_to_data; VI = VI->next = new Brutal_node();
                    break;
                case 7:
                    VII->ptr_to_data = ptr->ptr_to_data; VII = VII->next = new Brutal_node();
                    break; 
                case 8:
                    VIII->ptr_to_data = ptr->ptr_to_data; VIII = VIII->next = new Brutal_node();
                    break;
                default:
                    cout << "A fetal error occurs" << endl;   

                        Brutal_node *name_list;
    Brutal_node *keep = name_list;
    //people being treated
    if (4 == number){
        while (NULL != ptr){
            //如果此人没有被治疗过直接跳到下一个
            if (!ptr->ptr_to_data->treated){ptr = ptr->next; continue;}
            //copy a name list
            name_list->ptr_to_data = ptr->ptr_to_data;
            name_list = name_list->next;
            ptr = ptr->next;
        }
    }
    //people made an appointment
    else if (5 == number){
        while (NULL != ptr){
            //如果此人没有登记治疗过直接跳到下一个
            if ((!ptr->ptr_to_data->appo) || ptr->ptr_to_data->treated || ptr->ptr_to_data->withdrawn){ptr = ptr->next; continue;}
            //copy a name list
            name_list->ptr_to_data = ptr->ptr_to_data;
            name_list = name_list->next;
            ptr = ptr->next;
        }

    }
    //people registered
    else {
        while (NULL != ptr){
            if (ptr->ptr_to_data->appo || ptr->ptr_to_data->withdrawn){ptr = ptr->next; continue;}
            name_list->ptr_to_data = ptr->ptr_to_data;
            name_list = name_list->next;
            ptr = ptr->next;
        }
    }
    return sortList(keep);



    Brutal_node *Report_system::Copied_list(Data *data){
    Brutal_node *head = new Brutal_node();
    Brutal_node *ptr = head;
    while(nullptr != data){
        ptr->ptr_to_data = data;
        ptr = ptr->next = new Brutal_node();
        data = data->next;
    }
    return head;



Brutal_node::Brutal_node(){
    ptr_to_data = nullptr;
    next = nullptr;
}
}
*/