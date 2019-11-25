/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef PERSON_H
#define PERSON_H
#include <string>


//Class to store basic info about a person including name, id, and level

class Person
{
    public:
        //constructors
        Person();
        Person(int newId);
        Person(int newId,std::string newName);
        Person(int newId,std::string newName,std::string newLevel);
        //destructor
        ~Person();
        //returns the name of the object
        std::string getName();
        //function to change name of student object
        void setName(std::string newName);
        //returns the level of the person
        std::string getLevel();
        //allows to change the level of the person
        void setLevel(std::string newLevel);
        //returns the id for the person
        int getId();
        //changes persons id number
        void setId(int newId);
        //returns the information stored for a person in string form
        std::string toString();
        //checks to see if a string is greater than zero characters
        bool isvalidString(std::string str);

        //member variables to store id, level,name
        int id;
        std::string level;
        std::string name;      
};

#endif