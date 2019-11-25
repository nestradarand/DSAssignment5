/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "Person.h"


//Class to extend person functionality to store major, GPA, and advisorId information

class Student : public Person
{
    public:
        //constructors
        Student();
        Student(int newId);
        Student(int newId, std::string newName);
        Student(int newId, std::string newName, std::string newLevel);
        //extended constructors to get major, gpa, and advisor id information
        Student(int newId, std::string newName,
                 std::string newLevel,std::string newMajor);
        Student(int newId, std::string newName,
                std::string newLevel, std::string newMajor,
                double newGPA);
        Student(int newId, std::string newName,
                std::string newLevel, std::string newMajor,
                double newGPA,int newAdvisorId);
        //destructor
        ~Student();
        //returns all info in a string
        std::string toString();
        //allows the changing of the student's majro
        void setMajor(std::string newMajory);
        //returns the major of the student
        std::string getMajor();
        //changes the GPA of a student
        void setGPA(double newGPA);
        //returns the GPA of the student
        double getGPA();
        //changes the student's advisor id
        void setAdvisorId(int i );
        //returns the student advisors id
        int getAdvisorId();
        //returns a string that can be serialized
        std::string getSerializable();

        //overloaded operators to test equality between students
        bool operator==(Student const &otherStudent);
        bool operator>(Student const &otherStudent);
        bool operator<(Student const &otherStudent);
        bool operator>=(Student const &otherStudent);
        bool operator<=(Student const &otherStudent);
        bool operator!=(Student const &otherStudent);


private:
        //member variables to store major gpa and advisor id
        std::string major;
        double gpa;
        int advisorId;
};
#endif