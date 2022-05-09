#include <cstddef>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "data.h"
#include <stdlib.h>
#include <cstring>
#include "base.cpp"
using std::cin;
using std::cout;

Local::Local()
{
    local = new blist<relation>;
    cout << "Create new local\n";
}

Local::~Local()
{
}

int Local::readfile(const char* filename)
{
    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror("打开文件时发生错误");
        return (-1);
    }
    Block<relation>* block = new Block<relation>();
    if (this->local->head == NULL)
        this->local->head = block;
    fgets(str, 60, fp);
    str[1] = '\0';
    int i = atoi(str);
    for (; i > 0; i--)
    {
        relation* data = new relation();
        if (fgets(data->person->id, 60, fp) != NULL)
        {
            data->person->id[10] = '\0';
            strcpy(data->status->id, data->person->id);
            strcpy(data->registration->id, data->person->id);
            strcpy(data->treatment->id, data->person->id);
        }
        else
            return 0;
        if (fgets(data->person->name, 60, fp) == NULL)
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            int a = sizeof(str);
            str[a - 1] = '\0';
            a = atoi(str);
            data->person->addx = a;
        }
        else
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            int a = sizeof(str);
            str[a - 1] = '\0';
            a = atoi(str);
            data->person->addy = a;
        }
        else
            return 0;
        if (fgets(data->person->phone, 60, fp) != NULL)
            data->person->phone[11] = '\0';
        else
            return 0;
        if (fgets(data->person->WeChat, 60, fp) == NULL)
            return 0;
        if (fgets(data->person->email, 60, fp) == NULL)
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            str[1] = '\0';
            int a = atoi(str);
            data->person->profession = a;
        }
        else
            return 0;
        if (fgets(data->person->birth, 60, fp) != NULL)
            data->person->birth[8] = '\0';
        else
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            str[1] = '\0';
            int a = atoi(str);
            data->status->risk = a;
        }
        else
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            int a = sizeof(str);
            str[a - 1] = '\0';
            a = atoi(str);
            data->registration->timestamp = a;
        }
        else
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            str[1] = '\0';
            int a = atoi(str);
            data->person->age_group = a;
        }
        else
            return 0;
        if (fgets(str, 60, fp) != NULL)
        {
            int a = sizeof(str);
            str[a - 1] = '\0';
            a = atoi(str);
            data->status->priority = a;
        }
        else
            return 0;
        if (fgets(str, 60, fp) != NULL) // new parts!!!
        {
            int a = sizeof(str);
            str[a - 1] = '\0';
            a = atoi(str);
            data->status->type = a;
        }
        else
            return 0;
        block->insert(data);
    }
    fclose(fp);
    return 1;
}

Block<relation>* Local::update()
{
    Block<relation>* head = local->head;
    return head;
}
