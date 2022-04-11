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

//用在main里面，管week report
/*

    head: central中的头节点
    timeoffset： 当前时间（不是自然时间，程序中可以选择7让时间往后推一天）
    length：central中链表的长度

*/
void Report_system::Open_file(Data *head, long timeoffset, int length)
{
    string choose;
    int your_choice = 0;
    ofstream outfile;
    stringstream ss;

    const char *one = "1";
    const char *two = "2";
    const char *three = "3";
    const char *zero = "0";

    //首先IO，要求用户选择呈现的顺序，只有输入了123时才能继续，输入0时退出
    cout << "A week report is generating..." << endl;
    do
    {
        cout << "Please choose the order: 1 for name, 2 for profession, 3 for age, 0 for quit." << endl;
        cin >> choose;
    } while (0 != strcmp(one, choose.c_str())  && 0 != strcmp(two, choose.c_str()) && 0 != strcmp(three, choose.c_str()) && 0 != strcmp(zero, choose.c_str()));

    //输入的char转换为int，采用sstream流的方法
    ss << choose;
    ss >> your_choice;
    ss.clear();

    //选择0时中断报告
    if (0 == your_choice)
    {
        cout << "quitting..." << endl;
        return;
    }

    //打开报告文件，如果错误则退出
    outfile.open("./report/Week.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){
        cout << "Error opening file" << endl;
        return;
    }

    //接下来就是一系列的输出
    outfile << "————————————WEEK REPORT————————————\n" << endl;
    outfile << "-----People who have been treated-----" << endl;
    outfile.close();

    //4代表“being treated“，用在sorting中的复制链表的操作中
    Week(head, your_choice, 4, timeoffset, length, true);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Registered people with a set appointment-----" << endl;
    outfile.close();

    //5代表”appointed“
    Week(head, your_choice, 5, timeoffset, length, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Queueing people without a set appointment-----" << endl;
    outfile.close();

    //6代表”waiting“
    Week(head, your_choice, 6, timeoffset, length, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "REPORT ENDS" << endl;
    outfile.close();
    cout << "Week.txt generates ssuccessfully." << endl;
    return;
}


//用在main里面，管month report
/*
    head：头节点
    time offset：当前时间（不是自然时间，同上）
*/
void Report_system::Month(Data *head, long timeoffset)
{
    ofstream outfile;
    Data *temp = head;
    int *keep = new int[9];

    // 0: How many people have registered?
    // 1: How many of them are waiting?（没有用到，一开始理解错误了）
    // 2: How many are waiting in total?
    // 3: How many people had been treated?
    // 4: Average waiting time
    // 5: How many people had withdrew their registration?
    // 6: How many treatment appointments have been made?
    // 7: How many of them are waiting in locale1?
    // 8: How many of them are waiting in locale2?


    for (int i = 0; i <= 8; i++){keep[i] = 0;}
    while (nullptr != temp)
    {
        //只要进入系统了就算登记过
        keep[0] += 1;
        //已经预约 && 没有治疗 && 没有退出（不过没有用到）
        if(temp->appo && !temp->treated && !temp->withdrawn){keep[1] += 1;}
        //没有预约 && 没有退出（退出指不想在我们系统内参与治疗，即不想等待的人）
        if(!temp->appo && !temp->withdrawn){keep[2] += 1;}
        if (temp->treated)
        {
            //已经治疗的人
            keep[3] += 1;
            //收集等待时间
            keep[4] += (temp->appointment->time - temp->timestamp);
        }
        //如果这个人来自locale1则输出
        if (1 == temp->locale){keep[7] += 1;}
        //如果这个人来自locale2
        if (2 == temp->locale){keep[8] += 1;}
        //退出的人
        if(temp->withdrawn){keep[5] += 1;}
        //预约的人 ｜｜ 退出的人（在退出时appo = false， 所以要另外判断）
        if (temp->appo || temp->withdrawn){keep[6] += 1;}

        temp = temp->next;
    }

    outfile.open("./report/Month.txt", ios::out | ios::trunc);
    if (!outfile.is_open()){cout << "Error opening file" << endl; return;}

    outfile << "MONTH REPORT" << endl;
    outfile << "How many people have registered? " << keep[0] << endl;
    outfile << "How many of them are waiting in locale 1? " << keep[7] << endl;
    outfile << "How many of them are waiting in locale 2? " << keep[8] << endl;   
    outfile << "How many are waiting in total? " << keep[2] << endl;
    outfile << "How many treatment appointments have been made? " << keep[6] << endl;
    //当没有人被治疗过时，等待时间自然是0
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
    cout << "Month.txt generates successfully." << endl;
    return;
}




//用在open——file里面，进行关于name、profession还是age的分类
/*

    head： central中的头节点
    choice：用户选择的顺序
    choice2: 用于区分不同的部分：treated ｜｜ appointed ｜｜ 啥事没干的
    time offset：当前时间，同上
    length：central链表长度
    treating：判断是否治疗了，如果已经治疗了，那么等待时间已经固定

*/
void Report_system::Week(Data *head, int Choice, int Choice_2, long timeoffset, int length, bool treating)
{
    Data *paste;
    long TIME;
    ofstream outfile;

    //重新打开同名文件，在Open_file函数中已经关闭了原文件，所以不会覆盖，ios::app保证新输入的数据加在末尾
    outfile.open("./report/Week.txt", ios::out | ios::app);
    if (!outfile.is_open()){cout << "Error in Week" << endl; return;}

    switch (Choice)
    {
    //用户选择了按姓名排序
    case 1:
        paste = Sorting(head, Choice_2, length, 1);

        while (nullptr != paste)
        {
            //因为age——group 不可能等于0，当age——group等于0时说明sorting的时候没有这个节点
            if (0 == paste->age_group)
            {
                paste = paste->next;
                continue;
            }
            //名字放在最前面
            outfile << "\n" << "Name: " << paste->name;
            outfile << "Profession: " << paste->profession << endl;
            outfile << "Age: " << paste->age_group << endl;
            outfile << "Risk status: " << paste->risk << endl;
            //判断时间是否锁定
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
    //用户选择了profession排序
    case 2:
        paste = Sorting(head, Choice_2, length, 2);

        while (nullptr != paste)
        {
            if (0 == paste->age_group)
            {
                paste = paste->next;
                continue;
            }
            //profession排在最前面
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
//排序，先根据不同标准复制central中的链表到数组中，然后用sort进行排序
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
//cmp函数，用于自定义sort函数
bool Report_system::cmp_name(Data a, Data b) { return strcmp(a.name, b.name) < 0 ? true : false; }
bool Report_system::cmp_profession(Data a, Data b) { return a.profession < b.profession; }
bool Report_system::cmp_age(Data a, Data b) { return a.age_group < b.age_group; }
