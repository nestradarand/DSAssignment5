/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef DATAPARSER_H
#define DATAPARSER_H
#include "DLQueue.h"
#include "Student.h"
#include "Faculty.h"
#include <string>

//Class to manage the parsing through csv serialized data for students and faculty to a queue for later use

class DataParser
{
    public:
        //constructor
        DataParser();
        //destructor
        ~DataParser();
        //takes serialized data and puts it into a queue for later use
        void putDataInQueue(std::string str, DLQueue<std::string> *queue);
        //returns a student object from the data stored in a queue
        Student *getStudentFromDataQueue(DLQueue<std::string> *queue);
        //returns a faculty object from the data stored in a given queue
        Faculty *getFacultyFromDataQueue(DLQueue<std::string> *queue);
};
#endif