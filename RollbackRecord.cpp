/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#include "RollbackRecord.h"
#include <iostream>
#include <string>

using namespace std;
//default constructor
RollbackRecord::RollbackRecord()
{
    this ->isStudent = false;
}
//overloaded constructor
RollbackRecord::RollbackRecord(bool isStud, string newData,char newAction)
{
    this ->isStudent = isStud;
    this ->data = newData;
    this ->action = newAction;
}
//destructor
RollbackRecord::~RollbackRecord(){}

