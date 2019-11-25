
/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#include "Person.h"
#include <iostream>
#include <string>

using namespace std;


//default constructor and overloaded constructors
Person::Person()
{
    id = -1;
    name = "N/A";
    level = "N/A";
}
Person::Person(int newId)
{
    id = newId;
    name = "N/A";
    level = "N/A";
}
Person::Person(int newId, std::string newName)
{
    id = newId;
    name = newName;
    level = "N/A";
}
Person::Person(int newId, std::string newName, std::string newLevel)
{
    id = newId;
    name = newName;
    level = newLevel;
}
//destructor
Person::~Person()
{

}
//changes the id of the person
void Person::setId(int i)
{
    id = i;
}
//returns the id of the person
int Person::getId()
{
    return id;
}
//changes the name of the person
void Person::setName(string newName)
{
    name = newName;
}
//returns the name of the person
string Person::getName()
{
    return name;
}
//changes the level of the person object
void Person::setLevel(string str)
{
    level = str;
}
//returns the level of the person
string Person::getLevel()
{
    return name;
}
//returns string information of the person
string Person::toString()
{
    string returner = ("Name: " + name + 
                        "\nId number: " + to_string(id) +
                        "\nLevel: " + level);
    return returner;
}
