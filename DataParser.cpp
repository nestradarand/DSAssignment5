/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#include "DataParser.h"
#include <string>

    using namespace std;

//constructor and destructor
DataParser::DataParser(){}
DataParser::~DataParser(){}

Student* DataParser::getStudentFromDataQueue(DLQueue<string> *queue)
{
    try//used to catch any errors in the serialized data
    {
        int id, advisorId;
        double gpa;
        string name, level, major;
        /*knowing how the data is serialized we sequentially pull data from the queue storing the strings 
        previously parsed from the csv file*/
        id = std::stoi(queue->dequeue());
        name = queue->dequeue();
        level = queue->dequeue();
        major = queue->dequeue();
        gpa = std::stod(queue->dequeue());
        advisorId = std::stoi(queue->dequeue());
        //makes new student instance
        Student *newStud = new Student(id, name, level, major, gpa, advisorId);
        return newStud;
    }
    //returns null if there was an error in parsing process
    catch (std::exception e)
    {
        return NULL;
    }
}
Faculty* DataParser::getFacultyFromDataQueue(DLQueue<string> *queue)
{
    try
    {
        int id, numAdvisees;
        string name, level, department;
        /*knowing how the data is serialized we sequentially pull data from the queue storing the strings 
        previously parsed from the csv file*/
        id = std::stoi(queue->dequeue());
        name = queue->dequeue();
        level = queue->dequeue();
        department = queue->dequeue();
        numAdvisees = std::stoi(queue->dequeue());
        Faculty *newFac = new Faculty(id, name, level, department);
        //given the number of advisees the faculty had, we can add the ids of those students to the faculty's list
        for (int i = 0; i < numAdvisees; ++i)
        {
            newFac->addAdvisee(std::stoi(queue->dequeue()));
        }
        return newFac;
    }
    //returns null if any errors occur in parsing serialized data
    catch (std::exception e)
    {
        return NULL;
    }
}
//takes a string of serialized csv data and puts it into a queue for later use
void DataParser::putDataInQueue(string str, DLQueue<string> *queue)
{
    string delimiter = ",";
    ////from reference stack overflow
    int pos = 0;
    string newData;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        newData = str.substr(0, pos);
        //adds new substring to the queue
        queue->enqueue(newData);
        //erases up to the current position of the delimiter
        str.erase(0, pos + delimiter.length());
    }
}