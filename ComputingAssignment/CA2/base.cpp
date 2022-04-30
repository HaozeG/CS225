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
    risk = 0;
    priority = -1;
    type = 1;
}

Registration::Registration()
{
    timestamp = 0;
}

Treatment::Treatment()
{
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

Block::Block()
{
    block = new relation*[9];
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

blist::blist()
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
    char* a = new char[10];
    sprintf(a, "%d", this->priority);
    return a; //return this->priority;
}

char* Registration::key()
{
    char* a = new char[10];
    sprintf(a, "%d", this->timestamp);
    return a; //return this->timestamp;
}

char* Treatment::key()
{
    char* a = new char[10];
    sprintf(a, "%d", this->time);
    return a; //return this->time;
}

class blist;

int relation::key()
{
    if (this->status->type == 0)
        return this->registration->timestamp;
    else if (this->status->type == 1)
        return this->status->risk;
    else
        return this->status->priority;
}

void Block::sort() // Need to add parts to update pointers in tree
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
            if (strcmp(this->block[i]->person->id, this->block[j]->person->id) > 0)
            {
                relation* temp = this->block[i];
                this->block[i] = this->block[j];
                this->block[j] = temp;
            }
        }
    }
    this->overflow = 0;
}

relation* Block::split(relation* item)
{
    Block* newblock = new Block();
    int newnum = this->number / 2 + 3;
    relation* mid;
    if (strcmp(this->block[newnum - 1]->person->id, item->person->id) > 0) // left side
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
    else if (strcmp(this->block[newnum]->person->id, item->person->id) < 0) // right side
    {
        mid = this->block[newnum];
        cout << newnum << " " << mid->person->id << "\n";
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
    //blist::numitems++;
    return mid;
}

void Block::insert(relation* item)
{ //cout<<"ha\n";//cout<<this->number<<"ha\n";
    if (this->number == this->length - 3)
    {
        relation* mid = this->split(item);
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

void Block::bdelete(const char* id)
{
    if (this->number == 0)
        return;
    for (int i = 0; i < this->length; i++)
    {
        if (this->block[i] == NULL)
            continue;
        if (strcmp(this->block[i]->person->id, id) == 0)
        {
            this->block[i] = NULL;
            this->number--;
            return;
        }
    }
    return;
}

relation* Block::retrieval(const char* id)
{
    if (this->number == 0)
        return NULL;
    for (int i = 0; i < this->overflow; i++)
    {
        if (this->block[i] == NULL)
            break;
        if (strcmp(this->block[i]->person->id, id) == 0)
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
        if (strcmp(this->block[mid]->person->id, id) == 0)
            return this->block[mid];
        else if (strcmp(this->block[mid]->person->id, id) > 0)
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

void blist::merge(Block* block1, Block* block2) // the final index should be the same as block1
{
    for (int i = 0; i < block2->number; i++)
        block1->insert(block2->block[i]);
    //this->numitems--;
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
