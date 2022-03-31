#include "report.h"
#include <algorithm>
#include <cstddef>
#include <new>
using namespace std;

//for weekly report, choose the order，加入do, while循环来保证输入了123
int Report_system::weekly_choice(){
    int choose;
    cout << "A weekly report is generating" << endl;
    do{
        cout << "choose the order: 1 for name, 2 for profession, 3 for age" << endl;
        cin >> choose;
    }while( 1 != choose || 2 != choose || 3 != choose);
    return choose;
}
//open file for weekly report； choice = 排序顺序； ptr = 从data复制的单链表
void Report_system::open_file_weekly(Data *data, int Choice, Brutal_node *ptr){
    //文件输出流
    ofstream outfile;
    //打开文件，不能防止文件已存在
    outfile.open("Week.txt", ios::out);
    //标题
    cout << "————————————WEEK REPORT————————————\n" << endl;
    //已经被治疗的人，即：data->treated = true
    cout << "\f-----people who has been treated-----" << endl;
    Writing_weekly(data, Choice, 4, ptr);
    //已经做了预约但是没有治疗的人，排除withdraw的人
    cout << "-----people who has an appointment but not treated yet-----" << endl;
    Writing_weekly(data, Choice, 5, ptr);
    //做了登记但是没有预约也没有被治疗， 即：appo = false && treated = false 或 appo = true && withdraw = true
    cout << "-----people who has registered but done nothing else-----" << endl;
    Writing_weekly(data, Choice, 6, ptr);
    //结尾
    cout << "\fReporting has completed." << endl;
    //关闭文件
    outfile.close();
}
//open_file_weekly里面调用了3次的函数，choice = 排序顺序， choice_2 = treated || appointed || registered
void Report_system::Writing_weekly(Data *data, int Choice, int Choice_2, Brutal_node *ptr){
    //临时链表，在每个if状态中都用了一次，用于存储排序好的链表
    Brutal_node *print;
    //如果选择用名字排序，A在前
    if (1 == Choice){
        //获得排序后到链表
        print = sort_by_name(Copied_list(data), Choice_2);
        //将数字转换为字符串的前置条件
        std::stringstream ss;
        //当指针不为空时继续，注意头节点不能是dummy，目前没有排除这种情况
        while (nullptr != print){
            //输出名字
            cout <<  print->ptr_to_data->name << endl;

            //将数字导入流中
            ss << print->ptr_to_data->profession;
            //将数字转换为字符
            std::string profession = ss.str();
            //输出职业
            cout << "\f" << profession << endl;

            //将数字导入流中
            ss << print->ptr_to_data->age_group;
            //将数字转为字符
            std::string age = ss.str();
            //输出年龄段，默认1～7，没有按要求上的小于等于号来，若按要求也许需要switch一下
            cout << "\f" << age << endl;

            //将数字导入流中
            ss << print->ptr_to_data->risk;
            //将数字转为字符
            std::string risk = ss.str();
            //输出风险级
            cout << "\f" << risk << endl;

            //移到下一个节点
            print = print->next;
        }
    }
    //如果选择用职业排序，职业1～8
    else if (2 == Choice){
        print = sort_by_profession(Copied_list(data), Choice_2);
        std::stringstream ss;
        while (NULL != print){

            ss << print->ptr_to_data->profession;
            std::string profession = ss.str();
            cout << profession << endl;

            cout << "\f" << print->ptr_to_data->name << endl;

            ss << print->ptr_to_data->age_group;
            std::string age = ss.str();
            cout << "\f" << age << endl;

            ss << print->ptr_to_data->risk;
            std::string risk = ss.str();
            cout << "\f" << risk << endl;

            print = print->next;
        }
    }
    //如果选择用年龄排序，默认年龄是1～7
    else if (3 == Choice){
        print = sort_by_age(Copied_list(data), Choice_2);
        std::stringstream ss;
        while (NULL != print){

            ss << print->ptr_to_data->age_group;
            std::string age = ss.str();
            cout << age << endl;

            cout << "\f" << print->ptr_to_data->name << endl;

            ss << print->ptr_to_data->profession;
            std::string profession = ss.str();
            cout << "\f" << profession << endl;

            ss << print->ptr_to_data->risk;
            std::string risk = ss.str();
            cout << "\f" << risk << endl;

            print = print->next;
        }
    }
    else {
        //为了保证这种情况不会发生，也许需要在一开始选择顺序时加一个循环
        cout << "It seems that you did not choose a proper order." << endl;
    }
    return;
}
//从data拷贝一份单链表,改完了，但是有一大堆new
Brutal_node *Report_system::Copied_list(Data *data){
    Brutal_node *head = new Brutal_node();
    Brutal_node *ptr = head;
    while(nullptr != data){
        ptr->ptr_to_data = data;
        ptr = ptr->next = new Brutal_node();
        data = data->next;
    }
    return head;
}

Brutal_node *Report_system::sort_by_name(Brutal_node *ptr, int number){
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
            if (!ptr->ptr_to_data->appo){ptr = ptr->next; continue;}
            //copy a name list
            name_list->ptr_to_data = ptr->ptr_to_data;
            name_list = name_list->next;
            ptr = ptr->next;
        }

    }
    //people registered
    else {
        while (NULL != ptr){
            //copy a name list
            name_list->ptr_to_data = ptr->ptr_to_data;
            name_list = name_list->next;
            ptr = ptr->next;
        }
    }
    return sortList(keep);
}
//名字排序的主函数，返回一个排好的链表的头指针
Brutal_node *Report_system::sortList(Brutal_node *ptr){
    if (nullptr == ptr || nullptr == ptr->next){return ptr;}
    Brutal_node* head1 = ptr;
    Brutal_node* head2 = split(ptr);
    head1 = sortList(head1);        //一条链表分成两段分别递归排序
    head2 = sortList(head2);
    return merge(head1, head2); 
}
//第一个节点是空节点，两个链表比较大小再整合进一个链表中
Brutal_node *Report_system::merge(Brutal_node *ptr1, Brutal_node *ptr2){
    Brutal_node *p;
    Brutal_node *keep = p;
    while (nullptr != ptr1 && nullptr != ptr2){
        if (0 > strcmp(ptr1->ptr_to_data->name, ptr2->ptr_to_data->name)){
            p->next = ptr1;
            p = p->next;
            ptr1 = ptr1->next;
        }else{
            p->next = ptr2;
            p = p->next;
            ptr2 = ptr2->next;
        }
    }
    if (nullptr != ptr1){p->next = ptr1;}
    if (nullptr != ptr2){p->next = ptr2;}
    return p->next;
}
//将链表从中间拆开
Brutal_node *Report_system::split(Brutal_node *ptr){
    Brutal_node *slow = ptr;
    Brutal_node *fast = ptr->next;
    while (fast != nullptr && fast->next != nullptr)
    {slow = slow->next; fast = fast->next->next;}
    Brutal_node* mid = slow->next;
    slow->next = nullptr;           //断尾
    return mid;
}
//分拆成8个链表，再从1到8连起来
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
//分拆成7个链表，再从1到7连起来
Brutal_node *Report_system::sort_by_age(Brutal_node *ptr, int number){

    Brutal_node *I, *II, *III, *IV, *V, *VI, *VII;
    Brutal_node *I_pre, *II_pre, *III_pre, *IV_pre, *V_pre, *VI_pre, *VII_pre;
    Brutal_node *keepI = I, *keepII = II, *keepIII = III, *keepIV = IV, *keepV = V;
    Brutal_node *keepVI = VI;
    Brutal_node *keepVII = VII;

    //people being treated
    if (4 == number){
        while (NULL != ptr){
            //如果此人没有被治疗过直接跳到下一个
            if (!ptr->ptr_to_data->treated){ptr = ptr->next;continue;}
            switch(ptr->ptr_to_data->age_group){
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
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            ptr = ptr->next;
        }
    }else if (5 == number){
        while (NULL != ptr){
            //如果此人没有登记治疗过直接跳到下一个
            if (!ptr->ptr_to_data->appo){ptr = ptr->next;continue;}
            switch(ptr->ptr_to_data->age_group){
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
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            ptr = ptr->next;
        }

    }else {
        while (NULL != ptr){
            switch(ptr->ptr_to_data->age_group){
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
                default:
                    cout << "A fetal error occurs" << endl;          
            }
            ptr = ptr->next;
        }
    }
    I_pre->next = keepII;
    II_pre->next = keepIII;
    III_pre->next = keepIV;
    IV_pre->next = keepV;
    V_pre->next = keepVI;
    VI_pre->next = keepVII;
    return keepI;
}

void Report_system::Writing_monthly(){
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
        if(data->appo){all_appointment_number += 1;}
        data = data->next;
    }
    all_waiting_number = Regi_number - all_appointment_number;
    return;
}
//构造函数,用于构造dummy头节点
Brutal_node::Brutal_node(){
    ptr_to_data = nullptr;
    next = nullptr;
}
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
*/