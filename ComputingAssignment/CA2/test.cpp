#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "data.h"
#include <stdlib.h>
#include <cstring>
using std::cin;
using std::cout;

int main()
{
    Local* abc = new Local();
    const char* a = "testfile.txt";
    abc->readfile(a); int i = 1;
    const char* x = "3200000002";
    //abc->local->head->bdelete(x);
    //abc->local->merge(abc->local->head, abc->local->head->next);
    //Block<relation>* tem = abc->local->head;
    for (Block<relation>* tem = abc->local->head; tem != NULL; tem = tem->next)
    {//cout<<(tem->next == NULL)<<"\n";
        cout<<"Block"<<i<<"\n"; i++;
        for (int j = 0; j < tem->length; j++)
        {
            if (tem->block[j] == NULL) continue;cout<<j<<"\n";
            cout<<"relation"<<j<<"\n";
            cout<<"person"<<" "<<tem->block[j]->person->id<<" "<<tem->block[j]->person->name
                <<" "<<tem->block[j]->person->birth<<" "<<tem->block[j]->person->age_group
                <<" "<<tem->block[j]->person->phone<<" "<<tem->block[j]->person->WeChat
                <<" "<<tem->block[j]->person->email<<"\n";
            cout<<"status"<<" "<<tem->block[j]->status->risk<<" "<<tem->block[j]->status->priority
                <<" "<<tem->block[j]->status->type<<"\n";
            cout<<"registration"<<" "<<tem->block[j]->registration->timestamp<<"\n";
            cout<<"treatment"<<" "<<tem->block[j]->treatment->time<<" "<<tem->block[j]->treatment->hospital_id<<"\n";
            cout<<"\n";
        }
        //if (tem->retrieval(x) != NULL)
        //cout<<"\n"<<tem->retrieval(x)->person->id<<"\n";
    }

    //char* c = new char [10];int i = 3201; sprintf(c,"%d",i);
    //sprintf(c, "%d.bmp", i);
    //for (int i = 0; i < ; i++)
    //cout<<c<<"\n";
    //const char* b = "3202";
    //if (strcmp(c,b) < 0)
    //cout<<strcmp(c,b)<<"\n";
    //const char* a = new char [10];
    //strcpy(a,b);
    //cout<<a<<"\n";
    return 0;
}
