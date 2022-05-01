#ifndef base_cpp
#define base_cpp
using namespace std;
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "data.h"
#include <stdlib.h>
using std::cin;
using std::cout;
#include <cstring>

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

relation::relation()
{
    person = new Person();
    status = new Status();
    registration = new Registration();
    treatment = new Treatment();
}

template<class T>
Block<T>::Block()
{
    block = new T*[9];
    for (int i = 0; i < 9; i++)
        block[i] = NULL;
    number = 0;
    overflow = 0;
    length = 9;
    prev = NULL;
    next = NULL;
    children = NULL;
    parent = NULL;
}

template<class T>
blist<T>::blist()
{
    head = NULL;
    //numitems = 0;
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

template<class T>
void Block<T>::sort() // Need to add parts to update pointers in tree
{
    for (int i = 3; i < this->length; i++) // clear the empty spaces in ordered place
    {
        if (this->block[i] == NULL)
        {
            for (; i < this->length - 1; i++)
                this->block[i] = this->block[i + 1];
        }
    }
    for (int i = 0; i < this->overflow; i++) // insert overflow ones into ordered place
    {
        this->block[3 + this->number - this->overflow + i] = this->block[i];
        this->block[i] = NULL;
    }
    for (int i = 3; i < this->length; i++) // bubble sort
    {
        if (this->block[i] == NULL)
            break;
        for (int j = i + 1; j < this->length; j++)
        {
            if (this->block[j] == NULL)
                break;
            if (strcmp(this->block[i]->key(), this->block[j]->key()) > 0)
            {
                T* temp = this->block[i];
                this->block[i] = this->block[j];
                this->block[j] = temp;
            }
        }
    }
    this->overflow = 0;
}

template<class T>
T* Block<T>::split(T* item)
{
    Block* newblock = new Block();
    int newnum = this->number / 2 + 3;
    T* mid;
    if (strcmp(this->block[newnum - 1]->key(), item->key()) > 0) // left side
    {
        mid = this->block[newnum - 1];
        this->block[newnum - 1] = item;
        for (int i = newnum; i < this->length; i++)
        {
            newblock->insert(this->block[i]);
            this->block[i] = NULL;
            this->number--;
        }
        this->sort();
    }
    else if (strcmp(this->block[newnum]->key(), item->key()) < 0) // right side
    {
        mid = this->block[newnum];
        this->block[newnum] = item;
        for (int i = newnum; i < this->length; i++)
        {
            newblock->insert(this->block[i]);
            this->block[i] = NULL;
            this->number--;
        }
        newblock->sort();
    }
    else // mid
    {
        mid = item;
        for (int i = newnum; i < this->length; i++)
        {
            newblock->insert(this->block[i]);
            this->block[i] = NULL;
            this->number--;
        }
    }
    newblock->next = this->next;
    newblock->prev = this;
    if (this->next != NULL)
        this->next->prev = newblock;
    this->next = newblock;
    return mid;
}

template<class T>
void Block<T>::insert(T* item)
{
    if (this->number == this->length - 3)
    {
        T* mid = this->split(item);
        this->insert(mid); // need to be modified when implementing trees
    }
    else
    {
        this->block[overflow] = item;
        this->number++;
        this->overflow++;
        if (this->overflow == 3)
            this->sort();
        return;
    }
}

template<class T>
void Block<T>::bdelete(const char* id) // no consideration about merging
{
    if (this->number == 0)
        return;
    for (int i = 0; i < this->length; i++)
    {
        if (this->block[i] == NULL)
            continue;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            this->block[i] = NULL;
            this->number--;
            return;
        }
    }
    return;
}

template<class T>
T* Block<T>::retrieval(const char* id)
{
    if (this->number == 0)
        return NULL;
    for (int i = 0; i < this->overflow; i++)
    {
        if (this->block[i] == NULL)
            break;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            return this->block[i];
        }
    }
    int low, high, mid;
    mid = 3 + (this->number - this->overflow) / 2;
    low = 3;
    high = this->length - 1;
    while (low <= mid && high >= mid)
    {
        if (this->block[mid] == NULL) // 再想想被删掉的情况
        {
            while (this->block[mid] == NULL && mid < high)
                mid++;
            if (this->block[mid] == NULL)
                while (this->block[mid] == NULL && mid > low)
                    mid--;
            if (this->block[mid] == NULL)
                return NULL;
        }
        if (strcmp(this->block[mid]->key(), id) == 0)
            return this->block[mid];
        else if (strcmp(this->block[mid]->key(), id) > 0)
        {
            int tem = mid;
            mid = mid - (mid - low) / 2;
            high = tem - 1;
        }
        else
        {
            int tem = mid;
            mid = mid + (high - mid) / 2;
            low = tem + 1;
        }
    }
    return NULL;
}

template<class T>
void blist<T>::merge(Block<T>* block1, Block<T>* block2) // the final index should be the same as block1
{
    for (int i = 0; i < block2->number + 3; i++)
    {
        if (block2->block[i] == NULL)
            continue;
        block1->insert(block2->block[i]);
    }
    if (block2->prev == NULL)
        this->head = block2->next;
    else if (block2->next == NULL)
        block2->prev->next = NULL;
    else
    {
        block2->prev->next = block2->next;
        block2->next->prev = block2->prev;
    }
    return;
}

/*Local::Local()
{
    local = new blist<relation>;
}

int Local::readfile(const char* filename)
{
     FILE *fp;
    fp = fopen(filename , "r");
    if(fp == NULL) {
     perror("打开文件时发生错误");
     return(-1);
    }
    Block<relation>* block = new Block<relation>();
    if (this->local->head == NULL) this->local->head = block;
    fgets (str, 60, fp);
    str[1] = '\0';
    int i = atoi(str);
    for (; i>0; i--)
    {
        relation* data = new relation();
        if( fgets (data->person->id, 60, fp)!=NULL )
        {
            data->person->id[10]='\0';
            strcpy(data->status->id, data->person->id);
            strcpy(data->registration->id, data->person->id);
            strcpy(data->treatment->id, data->person->id);
        }
        else return 0;
        if( fgets (data->person->name, 60, fp)==NULL )
            return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            data->person->addx = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            data->person->addy = a;
        }
        else return 0;
        if( fgets (data->person->phone, 60, fp)!=NULL )
            data->person->phone[11]='\0';
        else return 0;
        if( fgets (data->person->WeChat, 60, fp)==NULL )
            return 0;
        if( fgets (data->person->email, 60, fp)==NULL )
            return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            data->person->profession = a;
        }
        else return 0;
        if( fgets (data->person->birth, 60, fp)!=NULL )
            data->person->birth[8]='\0';
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            data->status->risk = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            data->registration->timestamp = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            str[1]='\0';
            int a = atoi(str);
            data->person->age_group = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL )
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            data->status->priority = a;
        }
        else return 0;
        if( fgets (str, 60, fp)!=NULL ) // new parts!!!
        {
            int a = sizeof(str);
            str[a-1]='\0';
            a = atoi(str);
            data->status->type = a;
        }
        else return 0;
        block->insert(data);//cout<<i<<"\n";
    }
    fclose(fp);
    return 1;
}

Block<relation>* Local::update()
{
    Block<relation>* head = local->head;
    return head;
}*/
#endif
