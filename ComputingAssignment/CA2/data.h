#ifndef data_h
#define data_h

#include "string.h"
#include <iostream>
using std::cout;

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
        key_in_bptree = nullptr;
    };
    ~Block();

    T** block; // place holder == nullptr
    Block<T>* insert(T* item);
    void sort();
    char* bdelete(const char* id);
    char* merge(Block<T>* block1, Block<T>* block2);
    T* retrieval(const char* id); // search through the block and return the block+index
    int number;
    int overflow;
    int length;
    int overblock;
    int index; // address in blist, beginning from 1
    Block* prev;
    Block* next;
    //     Block* children;
    char* key_in_bptree;
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
    //static int numitems;
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
    //     if (strcmp(this->block[newnum - 1]->key(), item->key()) > 0) // left side
    //     {
    //         mid = this->block[newnum - 1];
    //         this->block[newnum - 1] = item;
    //         for (int i = newnum; i < this->length; i++)
    //         {
    //             newblock->insert(this->block[i]);
    //             this->block[i] = nullptr;
    //             this->number--;
    //         }
    //         this->sort();
    //     }
    //     if (strcmp(this->block[newnum]->key(), item->key()) < 0) // right side
    //     {
    mid = this->block[newnum];
    this->block[newnum] = item;
    for (int i = newnum; i < this->length; i++)
    {
        newblock->insert(this->block[i]);
        this->block[i] = nullptr;
        this->number--;
    }
    newblock->sort();
    //     }
    //     else // mid
    //     {
    //         mid = item;
    //         for (int i = newnum; i < this->length; i++)
    //         {
    //             newblock->insert(this->block[i]);
    //             this->block[i] = nullptr;
    //             this->number--;
    //         }
    //     }
    newblock->next = this->next;
    newblock->prev = this;
    if (this->next != nullptr)
        this->next->prev = newblock;
    this->next = newblock;
    return mid;
}

template<class T>
Block<T>* Block<T>::insert(T* item)
{
    if (this->number == this->length - this->overblock)
    {
        T* mid = this->split(item);
        this->insert(mid); // need to be modified when implementing trees
        return this->next;
    }
    else
    {
        this->block[overflow] = item;
        this->number++;
        this->overflow++;
        if (this->overflow == this->overblock)
            this->sort();
        return nullptr;
    }
}

/**
 * @brief delete data with id from block, return the key to be deleted in B+ tree
 *
 * @tparam T
 * @param id
 * @return char*
 */
template<class T>
char* Block<T>::bdelete(const char* id)
{
    if (this->number == 0)
        return nullptr;
    for (int i = 0; i < this->length; i++)
    {
        if (this->block[i] == nullptr)
            continue;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            this->block[i] = nullptr;
            this->number--;
            break;
        }
    }
    //     this->sort();
    // check for merge
    if (nullptr != this->prev && (this->number + this->prev->number) <= (this->length - this->overblock))
    {
        return merge(this->prev, this);
    }
    if (nullptr != this->next && (this->number + this->next->number) <= (this->length - this->overblock))
    {
        return merge(this, this->next);
    }
    return nullptr;
}

template<class T>
T* Block<T>::retrieval(const char* id)
{
    if (this->number == 0)
        return nullptr;
    int i = 0;
    for (i = 0; i < this->overflow; i++)
    {
        if (this->block[i] == nullptr)
            break;
        if (strcmp(this->block[i]->key(), id) == 0)
        {
            return this->block[i];
        }
    }
    int low, high, mid;
    low = this->overblock;
    high = (this->number - i) + low - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        cout << this->block[2]->key() << "ghighiweg\n";
        char* mid_key = this->block[mid]->key();
        cout << mid << "mid\n";
        if (strcmp(id, mid_key) == 0)
            return this->block[mid];
        else if (strcmp(id, mid_key) > 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return nullptr;
}

/**
 * @brief merge block2 to block1
 *
 * @tparam T
 * @param block1
 * @param block2
 * @return char*
 */
template<class T>
char* Block<T>::merge(Block<T>* block1, Block<T>* block2) // the final index should be the same as block1
{
    for (int i = 0; i < block2->length; i++)
    {
        if (block2->block[i] != nullptr)
            continue;
        block1->insert(block2->block[i]);
        block2->block[i] = nullptr;
    }
    //     if (block2->prev == nullptr)
    //         this->head = block2->next;
    // TODO: 改成block1
    if (block2->next != nullptr)
        block2->next->prev = block1;
    block1->next = block2->next;
    return block2->key_in_bptree;
}

#endif
