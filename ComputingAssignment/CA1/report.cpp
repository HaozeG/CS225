#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <sys/_types/_time_t.h>
#include <time.h>
#include "fibonacii_heap.h"
#include "data.h"
#include "report.h"

using namespace std;
//for weekly report, choose the order 
int Report_system::weekly_choice(){
    char input[1];
    cout << "A weekly report is generating\n" << endl;
    cout << "choose the order: 1 for name, 2 for profession, 3 for age\n" << endl;
    cin.getline(input,1);
    return (int)input[0];
}
//open file for weekly report
void Report_system::open_file(){
    ofstream outfile;
    outfile.open("Week.txt", ios::out | ios::trunc);
    cout << "WEEK REPORT\n" << endl;
}

void Report_system::Writing_weekly(Node *node, int Choice){
    if (NULL == node->data){return;}
    if (node->Written){return;}
    if (1 == Choice){
        for (int i = 65; 90 >= i; i++){
            
        }
    }
    else if (2 == Choice){

    }
    else{

    }
    node->Written = true;
    return Writing_weekly(node->child, Choice);
    return Writing_weekly(node->left,Choice);
}

//open file for monthly report
void Report_system::file_month(){
    ofstream outfile;
    outfile.open("Month.txt", ios::out | ios::trunc);
    cout << "MONTH REPORT\n" << endl;
    std::stringstream ss;

    ss << Regi_number;
    std::string Regi = ss.str();
    cout << "Till now, " << Regi << "have been registered.\n"<< endl;

    ss << all_waiting_number;
    std::string Wait = ss.str();
    cout << Wait << "is waiting for an appointment.\n"<< endl;

    ss << all_appointment_numebr;
    std::string Appo = ss.str();
    cout << Appo << "have received an appointment.\n" << endl;

    double i = RMS_waiting_time / (all_appointment_numebr * 60 * 60);
    ss << i;
    std::string average = ss.str();
    cout <<"Patients have an average waiting time of "<< average << "hours.\n" << endl;

    ss << withdraw_number;
    std::string Without = ss.str();
    cout << "There are " << Without << "patients who had withdrawn their appointment.\n" << endl;

    cout << "_____________ENDING_____________" << endl;
    outfile.close();
}

void Report_system::stat(Node *node){
    if (NULL == node){return;}
    Regi_number += 1;
    if (node->data->withdrawn){withdraw_number += 1;}
    if (node->data->appointment->registered){
        all_appointment_numebr += 1;
        RMS_waiting_time += difftime(node->data->appointment->timpe_app, node->data->timep);
        }
    else{all_waiting_number += 1;}
    return;
}