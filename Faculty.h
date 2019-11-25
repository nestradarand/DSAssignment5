/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include "Person.h"
#include "DoublyLinkedList.h"

//Specialized person class to store a department variable and a list of advisees

class Faculty : public Person 
{
    public:
        //default constructors
        Faculty();
        //overloaded constructors
        Faculty(int newId);
        Faculty(int newId, std::string newName);
        Faculty(int newId, std::string newName, std::string newLevel);
        //constructor to store new department variable
        Faculty(int newId, std::string newName, std::string newLevel, std::string newDepartment);
        //desctructor
        ~Faculty();
        //returns department of the faculty member
        std::string getDepartment();
        //changes the department of the faculty member
        void setDepartment(std::string newDepartment);
        //adds advisee to their list of advisees
        void addAdvisee(int i);
        //prints all advisees' id number
        void printAllAdvisees();
        //removes an advisee by id number
        bool removeAdvisee(int i);
        //checks to see if the faculty member has an advisee
        bool hasAdvisee(int studId);
        //checks to see if the faculty has any advisees on their list
        bool hasAdvisees();
        //returns string of all information of this particular faculty member
        std::string toString();
        //returns all advisee ids in an array format
        int *returnAllAdvisees();
        //returns the number of advisees for a faculty member
        int getAdviseeNumber();

        //overloaded operators to test equality among faculty members
        bool operator==(Faculty const &otherFaculty);
        bool operator>(Faculty const &otherFaculty);
        bool operator<(Faculty const &otherFaculty);
        bool operator>=(Faculty const &otherFaculty);
        bool operator<=(Faculty const &otherFaculty);
        bool operator!=(Faculty const &otherFaculty);
    

        std::string getSerializable();
    private:
        //member variables to store department and list of advisees
        std::string department;
        DoublyLinkedList<int> *advisees = new DoublyLinkedList<int>();
};
#endif