#include "report.h"
#include "data.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <new>
#include <typeinfo>
using namespace std;

//用在main里面，管week report
/*

    head: central中的头节点
    timeoffset： 当前时间（不是自然时间，程序中可以选择7让时间往后推一天）
    length：central中链表的长度

*/

void Report_system::Open_file(blist<relation>* head, long timeoffset)
{
    string user_choice;
    int decision_type = 0;
    ofstream outfile;
    stringstream ss;

    const char* one = "1";
    const char* two = "2";
    const char* three = "3";
    const char* zero = "0";

    //首先IO，要求用户选择呈现的顺序，只有输入了123时才能继续，输入0时退出
    cout << "A week report is generating..." << endl;
    do
    {
        cout << "Please user_choice the order: 1 for name, 2 for profession, 3 for "
                "age, 0 for quit."
             << endl;
        cin >> user_choice;
    } while (0 != strcmp(one, user_choice.c_str()) &&
             0 != strcmp(two, user_choice.c_str()) &&
             0 != strcmp(three, user_choice.c_str()) &&
             0 != strcmp(zero, user_choice.c_str()));

    //输入的char转换为int，采用sstream流的方法,选择0时中断报告
    ss << user_choice;
    ss >> decision_type;
    ss.clear();
    if (0 == decision_type)
    {
        cout << "Quitting..." << endl;
        return;
    }

    //打开报告文件，如果错误则退出
    outfile.open("./report/Week.txt", ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    //接下来就是一系列的输出
    outfile << "————————————WEEK REPORT————————————\n\n";
    outfile << "-----People who have been treated-----\n";
    outfile.close();

    // 4代表“being treated“，用在sorting中的复制链表的操作中
    Week(head, decision_type, 4, timeoffset, true);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Registered people with a set appointment-----\n";
    outfile.close();

    // 5代表”appointed“
    Week(head, decision_type, 5, timeoffset, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "-----Queueing people without a set appointment-----\n";
    outfile.close();

    // 6代表”waiting“
    Week(head, decision_type, 6, timeoffset, false);

    outfile.open("./report/Week.txt", ios::out | ios::app);
    outfile << "REPORT ENDS" << endl;
    outfile.close();

    cout << "Week.txt generates ssuccessfully." << endl;
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
void Report_system::Week(blist<relation>* ptr, int User_Choice, int Choice_2, long timeoffset, bool treating)
{
    //paste是relation，最基本的数据储存空间
    relation* paste;
    long TIME;
    ofstream outfile;

    //重新打开同名文件，在Open_file函数中已经关闭了原文件，所以不会覆盖，ios::app保证新输入的数据加在末尾
    outfile.open("./report/Week.txt", ios::out | ios::app);
    if (!outfile.is_open())
    {
        cout << "Error in Week" << endl;
        return;
    }

    switch (User_Choice)
    {
    //用户选择了按姓名排序
    case 1:
        paste = Sorting(ptr, Choice_2, 1);

        while (nullptr != paste)
        {
            //因为age——group
            //不可能等于0，当age——group等于0时说明sorting的时候没有这个节点
            if (0 == paste->person->age_group)
            {
                paste = paste->next;
                continue;
            }
            //名字放在最前面
            outfile << "\n"
                    << "Name: " << paste->person->name;
            outfile << "Profession: " << paste->person->profession << "\n";
            outfile << "Age: " << paste->person->age_group << "\n";
            outfile << "Risk status: " << paste->status->risk << "\n";
            outfile << "Priority rule: " << paste->status->type << "\n";
            outfile.close();
            //判断时间是否锁定
            // if (treating)
            // {
            //     TIME = paste->treatment->time - paste->registration->timestamp;
            //     outfile << "Waiting time from registration to treatment: "
            //             << floor(TIME / 24) << " days and " << TIME % 24 << " hours." << endl;
            // }
            // else
            // {
            //     TIME = timeoffset - paste->registration->timestamp;
            //     outfile << "Waiting time until now: " << floor(TIME / 24)
            //             << " days and " << TIME % 24 << " hours." << endl;
            // }
            time_calculator(treating, paste, timeoffset);
            outfile.open("./report/Week.txt", ios::out | ios::app);
            paste = paste->next;
        }
        break;
    //用户选择了profession排序
    case 2:
        paste = Sorting(ptr, Choice_2, 2);

        while (nullptr != paste)
        {
            if (0 == paste->person->age_group)
            {
                paste = paste->next;
                continue;
            }
            // profession排在最前面
            outfile << "\n"
                    << "Profession: " << paste->person->profession << "\n";
            outfile << "Name: " << paste->person->name;
            outfile << "Age: " << paste->person->age_group << "\n";
            outfile << "Risk status: " << paste->status->risk << "\n";
            outfile << "Priority rule: " << paste->status->type << "\n";
            outfile.close();
            // if (treating)
            // {
            //     TIME = paste->treatment->time - paste->registration->timestamp;
            //     outfile << "Waiting time from registration to treatment: "
            //             << floor(TIME / 24) << " days and " << TIME % 24 << " hours."
            //             << endl;
            // }
            // else
            // {
            //     TIME = timeoffset - paste->registration->timestamp;
            //     outfile << "Waiting time until now: " << floor(TIME / 24)
            //             << " days and " << TIME % 24 << " hours." << endl;
            // }
            time_calculator(treating, paste, timeoffset);
            outfile.open("./report/Week.txt", ios::out | ios::app);
            paste = paste->next;
        }
        break;

    case 3:
        paste = Sorting(ptr, Choice_2, 3);

        while (nullptr != paste)
        {
            if (0 == paste->person->age_group)
            {
                paste = paste->next;
                continue;
            }
            outfile << "\n"
                    << "Age group: " << paste->person->age_group << endl;
            outfile << "Name: " << paste->person->name;
            outfile << "Profession: " << paste->person->profession << endl;
            outfile << "Risk status: " << paste->status->risk << endl;
            outfile << "Priority rule: " << paste->status->type << "\n";
            outfile.close();
            // if (treating)
            // {
            //     TIME = paste->treatment->time - paste->registration->timestamp;
            //     outfile << "Waiting time from registration to treatment: "
            //             << floor(TIME / 24) << " days and " << TIME % 24 << " hours."
            //             << endl;
            // }
            // else
            // {
            //     TIME = timeoffset - paste->registration->timestamp;
            //     outfile << "Waiting time until now: " << floor(TIME / 24)
            //             << " days and " << TIME % 24 << " hours." << endl;
            // }
            time_calculator(treating, paste, timeoffset);
            outfile.open("./report/Week.txt", ios::out | ios::app);
            paste = paste->next;
        }
        break;

    default:
        cout << "Error." << endl;
    }
    outfile.close();
    return;
}
//排序，先根据不同标准复制central中的链表到数组中，然后用sort进行排序
relation* Report_system::Sorting(blist<relation>* ptr, int Choice_2, int Choice)
{
    Block<relation>* block_head = ptr->head;
    Block<relation>* count_block = ptr->head;
    int num_relation = 0;
    do
    {
        num_relation += count_block->length;
        count_block = count_block->next;
    } while (nullptr != count_block);

    Block<relation>* temp_block = block_head;
    relation* result = new relation[num_relation];
    int index = 0;

    switch (Choice_2)
    {
        do
        {
            relation** relation_array = temp_block->block;
            for (int j = 0; j < temp_block->length; j++)
            {
                relation* temp_relation = relation_array[j];
                if (nullptr == temp_relation)
                {
                    continue;
                }
                if (temp_relation->appoint->treated)
                {
                    result[index].person->name = temp_relation->person->name;
                    result[index].person->age_group = temp_relation->person->age_group;
                    result[index].person->profession = temp_relation->person->profession;
                    result[index].status->risk = temp_relation->status->risk;
                    result[index].registration->timestamp = temp_relation->registration->timestamp;
                    result[index].treatment->time = temp_relation->treatment->time;
                    index += 1;
                }
            }
            temp_block = temp_block->next;
        } while (block_head != temp_block);
        break;
    // People who have been treated
    //            if (ptr->treated)
    case 4:

        break;
    // Registered people with a set appointment
    //            if (ptr->appo && !ptr->treated && !ptr->withdrawn)
    case 5:
        do
        {
            relation** relation_array = temp_block->block;
            for (int j = 0; j < temp_block->length; j++)
            {
                relation* temp_relation = relation_array[j];
                if (nullptr == temp_relation)
                {
                    continue;
                }
                if (temp_relation->appoint->appo && !temp_relation->appoint->treated && !temp_relation->appoint->withdrawn)
                {
                    result[index].person->name = temp_relation->person->name;
                    result[index].person->age_group = temp_relation->person->age_group;
                    result[index].person->profession = temp_relation->person->profession;
                    result[index].status->risk = temp_relation->status->risk;
                    result[index].registration->timestamp = temp_relation->registration->timestamp;
                    result[index].treatment->time = temp_relation->treatment->time;
                    index += 1;
                }
            }
            temp_block = temp_block->next;
        } while (block_head != temp_block);
        break;
    // Queueing people without a set appointment
    //            if (!ptr->appo && !ptr->withdrawn)
    case 6:
        do
        {
            relation** relation_array = temp_block->block;
            for (int j = 0; j < temp_block->length; j++)
            {
                relation* temp_relation = relation_array[j];
                if (nullptr == temp_relation)
                {
                    continue;
                }
                if (!temp_relation->appoint->appo && !temp_relation->appoint->withdrawn)
                {
                    result[index].person->name = temp_relation->person->name;
                    result[index].person->age_group = temp_relation->person->age_group;
                    result[index].person->profession = temp_relation->person->profession;
                    result[index].status->risk = temp_relation->status->risk;
                    result[index].registration->timestamp = temp_relation->registration->timestamp;
                    result[index].treatment->time = temp_relation->treatment->time;
                    index += 1;
                }
            }
            temp_block = temp_block->next;
        } while (block_head != temp_block);
        break;
    }

    switch (Choice)
    {
    case 1:
        sort(result, result + num_relation, cmp_name);
        break;
    case 2:
        sort(result, result + num_relation, cmp_profession);
        break;
    case 3:
        sort(result, result + num_relation, cmp_age);
        break;
    }
    for (int i = 0; i < num_relation - 1; i++)
    {
        result[i].next = &result[i + 1];
    }
    return result;
}
// cmp函数，用于自定义sort函数
bool Report_system::cmp_name(relation a, relation b)
{
    return strcmp(a.person->name, b.person->name) < 0 ? true : false;
}
bool Report_system::cmp_profession(relation a, relation b)
{
    return a.person->profession < b.person->profession;
}
bool Report_system::cmp_age(relation a, relation b)
{
    return a.person->age_group < b.person->age_group;
}

void Report_system::time_calculator(bool treating, relation* paste, long timeoffset)
{
    ofstream outfile;
    outfile.open("./report/Week.txt", ios::out | ios::app);
    int TIME;
    if (!outfile.is_open())
    {
        cout << "Error in Week when calculating time" << endl;
        return;
    }

    if (treating)
    {
        TIME = paste->treatment->time - paste->registration->timestamp;
        outfile << "Waiting time from registration to treatment: "
                << floor(TIME / 24) << " days and " << TIME % 24 << " hours."
                << endl;
    }
    else
    {
        TIME = timeoffset - paste->registration->timestamp;
        outfile << "Waiting time until now: " << floor(TIME / 24)
                << " days and " << TIME % 24 << " hours." << endl;
    }
    outfile.close();
    return;
}

//用在main里面，管month report
/*
    head：头节点
    time offset：当前时间（不是自然时间，同上）
*/

//缺locale的更改
void Report_system::Month(blist<relation>* ptr, long timeoffset)
{
    ofstream outfile;
    int* keep = new int[9];
    //temp是Block，一个Block里有好几个relation，根据number计数
    Block<relation>* temp = ptr->head;

    // 0: How many people have registered?
    // 1: How many of them are waiting?（没有用到，一开始理解错误了）
    // 2: How many are waiting in total?
    // 3: How many people had been treated?
    // 4: Average waiting time
    // 5: How many people had withdrew their registration?
    // 6: How many treatment appointments have been made?
    // 7: How many of them are waiting in locale1?
    // 8: How many of them are waiting in locale2?

    for (int i = 0; i <= 8; i++)
    {
        keep[i] = 0;
    }
    //外循环：遍历所有的Block
    do
    {
        //内循环：遍历一个Block里的relation
        for (int relation_index = 0; relation_index < temp->number;
             relation_index++)
        {
            //只要进入系统（只要有了relation）就算登记过
            keep[0] += 1;
            //已经预约 && 没有治疗 && 没有退出（不过没有用到）
            if ((temp->block[relation_index])->appoint->appo &&
                !(temp->block[relation_index])->appoint->treated &&
                !(temp->block[relation_index])->appoint->withdrawn)
            {
                keep[1] += 1;
            }
            //没有预约 && 没有退出（退出指不想在我们系统内参与治疗，即不想等待的人）
            if (!(temp->block[relation_index])->appoint->appo &&
                !(temp->block[relation_index])->appoint->withdrawn)
            {
                keep[2] += 1;
            }
            //已经治疗的人
            if ((temp->block[relation_index])->appoint->treated)
            {
                //已经治疗的人
                keep[3] += 1;
                //收集等待时间
                keep[4] += ((temp->block[relation_index])->treatment->time - (temp->block[relation_index])->registration->timestamp);
            }
            //退出的人
            if ((temp->block[relation_index])->appoint->withdrawn)
            {
                keep[5] += 1;
            }
            //预约的人 ｜｜ 退出的人（在退出时appo = false， 所以要另外判断）
            if ((temp->block[relation_index])->appoint->appo ||
                (temp->block[relation_index])->appoint->withdrawn)
            {
                keep[6] += 1;
            }
        }
        //移到下一个Block
        temp = temp->next;
        //因为是环，check是否结束
    } while (ptr->head != temp);

    outfile.open("./report/Month.txt", ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }

    outfile << "MONTH REPORT\n";
    outfile << "How many people have registered? " << keep[0] << "\n";
    outfile << "How many are waiting in total? " << keep[2] << "\n";
    outfile << "How many treatment appointments have been made? " << keep[6]
            << "\n";
    //当没有人被治疗过时，等待时间自然是0
    if (0 == keep[3])
    {
        outfile << "Average waiting time: "
                << "0 days 0 hours."
                << "\n";
    }
    else
    {
        outfile << "Average waiting time: " << floor(keep[4] / (24 * keep[3]))
                << " days " << (keep[4] / keep[3]) % 24 << " hours."
                << "\n";
    }
    outfile << "How many people had withdrew their registration? " << keep[5]
            << "\n";
    outfile << "_____________ENDING_____________\n";
    outfile.close();

    cout << "Month.txt generates successfully." << endl;
    return;
}