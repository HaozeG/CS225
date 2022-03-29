#include <runetype.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/_types/_time_t.h>
#include <time.h>
#include "fibonacii_heap.h"
#include "data.h"
#include "report.h"

using namespace std;
//for weekly report, choose the order 
int Report_system::weekly_choice(){
    char input[100];
    cout << "A weekly report is generating" << endl;
    cout << "choose the order: 1 for name, 2 for profession, 3 for age" << endl;
    cin.getline(input,1);
    return (int)input[0];
}
//open file for weekly report
void Report_system::open_file(Data *data, int Choice, Brutal_node *ptr){
    ofstream outfile;
    outfile.open("Week.txt", ios::out | ios::trunc);
    cout << "WEEK REPORT\n" << endl;
    cout << "-----people who has been treated-----" << endl;
    Writing_weekly(data, Choice, 4, ptr);
    cout << "-----people who has an appointment but not treated yet-----" << endl;
    Writing_weekly(data, Choice, 5, ptr);
    cout << "-----people who has registered but done nothing else-----" << endl;
    Writing_weekly(data, Choice, 6, ptr);
    cout << "Reporting has completed." << endl;
    outfile.close();
    return;
}

void Report_system::Writing_weekly(Data *data, int Choice, int Choice_2, Brutal_node *ptr){
    //first of all. copy a list
    Copied_list(data, ptr);
    if (1 == Choice){
        sort_by_age(ptr, Choice_2);
    }
    else if (2 == Choice){
        sort_by_profession(ptr, Choice_2);
    }
    else if (3 == Choice){
        sort_by_age(ptr, Choice_2);
    }
    else {
        cout << "It seems that you did not choose a proper order." << endl;
    }
    return;
}

//open file for monthly report
void Report_system::file_month(){
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
        if(data->appointment->registered){all_appointment_number += 1;}
        data = data->next;
    }
    all_waiting_number = Regi_number - all_appointment_number;
    return;
}

//copy a list for sorting
Brutal_node *Report_system::Copied_list(Data *data, Brutal_node *ptr){
    //first node is a dummy
    Brutal_node *pre = ptr;
    Brutal_node *cur;
    while(NULL != data){
        cur->ptr = data;
        ptr->next = cur;
        ptr = cur;
        cur = ptr->next;
        data = data->next;
    }
    ptr = pre;
    return ptr;
}

void Report_system::sort_by_name(Brutal_node *ptr, int number){
    //people being treated
    if (4 == number){


    }
    //people made an appointment
    else if (5 == number){

    }
    //people registered
    else {

    }
    return;
}

void Report_system::sort_by_profession(Brutal_node *ptr, int number){
    //people being treated
    if (4 == number){


    }
    //people made an appointment
    else if (5 == number){

    }
    //people registered
    else {

    }
    return;
}

void Report_system::sort_by_age(Brutal_node *ptr, int number){
    //people being treated
    if (4 == number){


    }
    //people made an appointment
    else if (5 == number){

    }
    //people registered
    else {

    }
    return;
}