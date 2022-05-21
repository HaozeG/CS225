#ifndef base_cpp
#define base_cpp
#include "data.h"

Person::Person()
{
    id = new char[10];
    name = new char[5];
    profession = 0;
    birth = new char[8];
    age_group = 0;
    addx = 0;
    addy = 0;
    phone = new char[11];
    WeChat = new char[7];
    email = new char[15];
}

Status::Status()
{
    id = new char[10];
    risk = 0;
    priority = -1;
    type = 1;
}

Registration::Registration()
{
    id = new char[10];
    timestamp = 0;
}

Treatment::Treatment()
{
    id = new char[10];
    time = 0;
    hospital_id = 0;
}

Appointment::Appointment()
{
    appo = false;
    treated = false;
    withdrawn = false;
}

relation::relation()
{
    person = new Person();
    status = new Status();
    registration = new Registration();
    treatment = new Treatment();
    appoint = new Appointment();
    f_node = nullptr;
}

char* Person::key()
{
    return this->id;
}

char* Status::key()
{
    return this->id;
}

char* Registration::key()
{
    return this->id;
}

char* Treatment::key()
{
    /*char* a = new char [10];
    sprintf(a,"%d",this->time);
    return a;//return this->time;*/
    return this->id;
}

char* relation::key()
{
    return this->person->id;
}

relation::~relation()
{
}

// template<class T>
// T* Block<T>::retrieval(const char* id)
// {
//     if (this->number == 0)
//         return NULL;
//     for (int i = 0; i < this->overflow; i++)
//     {
//         if (this->block[i] == NULL)
//             break;
//         if (strcmp(this->block[i]->key(), id) == 0)
//         {
//             return this->block[i];
//         }
//     }
//     int low, high, mid;
//     mid = this->overblock + (this->number - this->overflow) / 2;
//     low = this->overblock;
//     high = this->length - 1;
//     while (low <= mid && high >= mid)
//     {
//         if (this->block[mid] == NULL) // 再想想被删掉的情况
//         {
//             while (this->block[mid] == NULL && mid < high)
//                 mid++;
//             if (this->block[mid] == NULL)
//                 while (this->block[mid] == NULL && mid > low)
//                     mid--;
//             if (this->block[mid] == NULL)
//                 return NULL;
//         }
//         if (strcmp(this->block[mid]->key(), id) == 0)
//             return this->block[mid];
//         else if (strcmp(this->block[mid]->key(), id) > 0)
//         {
//             cout << "ha\n";
//             int tem = mid;
//             if (mid - low == 1)
//                 mid = mid - 1;
//             else
//                 mid = mid - (mid - low) / 2;
//             high = tem;
//         }
//         else
//         {
//             int tem = mid;
//             if (high - mid == 1)
//                 mid = mid + 1;
//             else
//                 mid = mid + (high - mid) / 2;
//             low = tem;
//         }
//     }
//     return NULL;
// }

// Local::Local()
// {
//     local = new blist<relation>;
// }

// int Local::readfile(const char* filename)
// {
//     FILE* fp;
//     fp = fopen(filename, "r");
//     if (fp == NULL)
//     {
//         perror("打开文件时发生错误");
//         return (-1);
//     }
//     Block<relation>* block = new Block<relation>();
//     if (this->local->head == NULL)
//         this->local->head = block;
//     fgets(str, 60, fp);
//     str[1] = '\0';
//     int i = atoi(str);
//     for (; i > 0; i--)
//     {
//         relation* data = new relation();
//         if (fgets(data->person->id, 60, fp) != NULL)
//         {
//             data->person->id[10] = '\0';
//             strcpy(data->status->id, data->person->id);
//             strcpy(data->registration->id, data->person->id);
//             strcpy(data->treatment->id, data->person->id);
//         }
//         else
//             return 0;
//         if (fgets(data->person->name, 60, fp) == NULL)
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             int a = sizeof(str);
//             str[a - 1] = '\0';
//             a = atoi(str);
//             data->person->addx = a;
//         }
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             int a = sizeof(str);
//             str[a - 1] = '\0';
//             a = atoi(str);
//             data->person->addy = a;
//         }
//         else
//             return 0;
//         if (fgets(data->person->phone, 60, fp) != NULL)
//             data->person->phone[11] = '\0';
//         else
//             return 0;
//         if (fgets(data->person->WeChat, 60, fp) == NULL)
//             return 0;
//         if (fgets(data->person->email, 60, fp) == NULL)
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             str[1] = '\0';
//             int a = atoi(str);
//             data->person->profession = a;
//         }
//         else
//             return 0;
//         if (fgets(data->person->birth, 60, fp) != NULL)
//             data->person->birth[8] = '\0';
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             str[1] = '\0';
//             int a = atoi(str);
//             data->status->risk = a;
//         }
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             int a = sizeof(str);
//             str[a - 1] = '\0';
//             a = atoi(str);
//             data->registration->timestamp = a;
//         }
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             str[1] = '\0';
//             int a = atoi(str);
//             data->person->age_group = a;
//         }
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL)
//         {
//             int a = sizeof(str);
//             str[a - 1] = '\0';
//             a = atoi(str);
//             data->status->priority = a;
//         }
//         else
//             return 0;
//         if (fgets(str, 60, fp) != NULL) // new parts!!!
//         {
//             int a = sizeof(str);
//             str[a - 1] = '\0';
//             a = atoi(str);
//             data->status->type = a;
//         }
//         else
//             return 0;
//         block->insert(data);
//     }
//     fclose(fp);
//     return 1;
// }

// Block<relation>* Local::update()
// {
//     Block<relation>* head = local->head;
//     return head;
// }
#endif
