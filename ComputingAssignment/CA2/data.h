#ifndef data_h
#define data_h

#include "string.h"

class Person
{
public:
    Person();
    ~Person();

    char* id;
    char* name;
    int profession;
    char* birth;
    int age_group;
    int addx;
    int addy;
    char* phone;
    char* WeChat;
    char* email;
    char* key();
};

class Status
{
public:
    Status();
    ~Status();

    char* id;
    int risk;
    int priority;
    int type; // treatment type, leading to different priority rule
    char* key();
    // Three different rule: register time, risk status, priority
};

class Registration
{
public:
    Registration();
    ~Registration();

    char* id;
    int timestamp;
    char* key();
};

class Treatment
{
public:
    Treatment();
    ~Treatment();

    char* id;
    int time;
    int hospital_id;
    char* key();
};

class Appointment
{
public:
    Appointment();
    ~Appointment();

    bool appo;
    bool treated;
    bool withdrawn;
};

namespace fibonacci
{
    class Node;
}
class relation
{
public:
    relation();
    ~relation();

    Appointment* appoint;
    Person* person;
    Status* status;
    Registration* registration;
    Treatment* treatment;
    char* key(); // return the associated key value according to the sorting type
    // TODO: pointer to Node in Fibonacci Heap
    fibonacci::Node* f_node;

    relation* next;
};

template<class T>
class Block // 0-2 is overflow block
{
public:
    Block()
    {
        block = new T*[5];
        for (int i = 0; i < 5; i++)
            block[i] = nullptr;
        number = 0;
        overflow = 0;
        length = 5;
        overblock = 2;
        prev = nullptr;
        next = nullptr;
        parent = nullptr;
    };
    ~Block();

    T** block; // place holder == nullptr
    void insert(T* item);
    void sort();
    void bdelete(const char* id);
    T* retrieval(const char* id); // search through the block and return the block+index
    int number;
    int overflow;
    int length;
    int overblock;
    int index; // address in blist, beginning from 1
    Block* prev;
    Block* next;
    //     Block* children;
    Block* parent;
    T* split(T* item);
};

template<class T>
class blist
{
public:
    blist()
    {
        head = nullptr;
        //numitems = 0;
    };
    ~blist(){};

    Block<T>* head;
    // TODO: numitems
    //static int numitems;
    void merge(Block<T>* block1, Block<T>* block2);
};

// namespace bp_tree
// {
//     class Tree;
// }

class Local
{
public:
    Local();
    ~Local();

    blist<relation>* local;
    int readfile(const char* filename);
    char str[60];
    Block<relation>* update();
};

template<class T>
void Block<T>::sort() // Need to add parts to update pointers in tree
{
    for (int i = this->overblock; i < this->length; i++) // clear the empty spaces in ordered place
    {
        if (this->block[i] == nullptr)
        {
            for (; i < this->length - 1; i++)
                this->block[i] = this->block[i + 1];
        }
    }
    for (int i = 0; i < this->overflow; i++) // insert overflow ones into ordered place
    {
        this->block[this->overblock + this->number - this->overflow + i] = this->block[i];
        this->block[i] = nullptr;
    }
    for (int i = this->overblock; i < this->length; i++) // bubble sort
    {
        if (this->block[i] == nullptr)
            break;
        for (int j = i + 1; j < this->length; j++)
        {
            if (this->block[j] == nullptr)
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
    this->sort();
    Block* newblock = new Block();
    int newnum = this->number / 2 + this->overblock;
    T* mid;
    if (strcmp(this->block[newnum - 1]->key(), item->key()) > 0) // left side
    {
        mid = this->block[newnum - 1];
        this->block[newnum - 1] = item;
        for (int i = newnum; i < this->length; i++)
        {
            newblock->insert(this->block[i]);
            this->block[i] = nullptr;
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
            this->block[i] = nullptr;
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
            this->block[i] = nullptr;
            this->number--;
        }
    }
    newblock->next = this->next;
    newblock->prev = this;
    if (this->next != nullptr)
        this->next->prev = newblock;
    this->next = newblock;
    return mid;
}

template<class T>
void Block<T>::insert(T* item)
{
    if (this->number == this->length - this->overblock)
    {
        T* mid = this->split(item);
        this->insert(mid); // need to be modified when implementing trees
        // TODO: insert into b+ tree
    }
    else
    {
        this->block[overflow] = item;
        this->number++;
        this->overflow++;
        if (this->overflow == this->overblock)
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
        if (this->block[i] == nullptr)
            continue;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            this->block[i] = nullptr;
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
        return nullptr;
    for (int i = 0; i < this->overflow; i++)
    {
        if (this->block[i] == nullptr)
            break;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            return this->block[i];
        }
    }
    int low, high, mid;
    mid = this->overblock + (this->number - this->overflow) / 2;
    low = this->overblock;
    high = this->length - 1;
    while (low <= mid && high >= mid)
    {
        if (this->block[mid] == nullptr) // 再想想被删掉的情况
        {
            while (this->block[mid] == nullptr && mid < high)
                mid++;
            if (this->block[mid] == nullptr)
                while (this->block[mid] == nullptr && mid > low)
                    mid--;
            if (this->block[mid] == nullptr)
                return nullptr;
        }
        if (strcmp(this->block[mid]->key(), id) == 0)
            return this->block[mid];
        else if (strcmp(this->block[mid]->key(), id) > 0)
        {
            int tem = mid;
            if (mid - low == 1)
                mid = mid - 1;
            else
                mid = mid - (mid - low) / 2;
            high = tem;
        }
        else
        {
            int tem = mid;
            if (high - mid == 1)
                mid = mid + 1;
            else
                mid = mid + (high - mid) / 2;
            low = tem;
        }
    }
    return nullptr;
}
template<class T>
void blist<T>::merge(Block<T>* block1, Block<T>* block2) // the final index should be the same as block1
{
    for (int i = 0; i < block2->number + block2->overblock; i++)
    {
        if (block2->block[i] == nullptr)
            continue;
        block1->insert(block2->block[i]);
    }
    if (block2->prev == nullptr)
        this->head = block2->next;
    else if (block2->next == nullptr)
        block2->prev->next = nullptr;
    else
    {
        block2->prev->next = block2->next;
        block2->next->prev = block2->prev;
    }
    return;
}

#endif
