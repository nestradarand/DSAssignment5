/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef ROLLBACKRECORD_H
#define ROLLBACKRECORD_H
#include <string>

//Class to store information of how to roll back given an alteration to the database for students and faculty

class RollbackRecord 
{
    public:
        //default constructor
        RollbackRecord();
        //overloaded constructor to take if the action was done to a student, their serialized data and what action to take to reverse
        RollbackRecord(bool isStud,std::string newData,char newAction);
        //destructor
        ~RollbackRecord();
        //stores if the action concerns a student
        bool isStudent;
        //concerns what kind of action to be used to revert what was done
        char action;
        //serialized data for whoever was added or deleted
        std::string data;
};
#endif