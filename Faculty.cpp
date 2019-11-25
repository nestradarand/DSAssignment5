/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#include "Faculty.h"
#include <string>
#include <iostream>

using namespace std;

//constructors
Faculty::Faculty() : Person(){
    department = "N/A";
}
Faculty::Faculty(int newId) : Person (newId){
    department = "N/A";
}
Faculty::Faculty(int newId,string newName) : Person(newId,newName){
    department = "N/A";
}
Faculty::Faculty(int newId,string newName,string newLevel) : Person(newId,newName,newLevel){
    department = "N/A";
}
//new constructor to store the department variable
Faculty::Faculty(int newId, string newName, string newLevel, string newDepartment) : Person(newId, newName, newLevel) 
{
    department = newDepartment;
}
//destructor to delete advisee list object
Faculty::~Faculty()
{
    delete advisees;
}
//returns department of the faculty member
string Faculty::getDepartment()
{
    return department;
}
//changes the department of the faculty member
void Faculty::setDepartment(string newDep)
{
    department = newDep;
}
//adds new advisee to the advisee list
void Faculty::addAdvisee(int i )
{
    advisees -> insertBack(i);
}
//prints all advisee ids
void Faculty::printAllAdvisees()
{
    advisees -> printList();
}
//removes an advisee by id
bool Faculty::removeAdvisee(int i)
{
    return advisees ->remove(i);
}
//checks to see if the faculty has an advisee by id number
bool Faculty::hasAdvisee(int studId)
{
    int result = advisees -> find(studId);
    if(result == -1)
        return false;
    else 
        return true;
}
//returns all information for the faculty member in a string format
string Faculty::toString()
{
    string returner = (Person::toString() +
                        "\nDepartment: " + department +
                        "\nNumber of Advisees: " + 
                        to_string(advisees -> getSize()));
    return returner;
}
//overloaded operators
bool Faculty::operator<(Faculty const &otherPerson)
{
    return this->id < otherPerson.id;
}
bool Faculty::operator>(Faculty const &otherPerson)
{
    return this->id > otherPerson.id;
}
bool Faculty::operator==(Faculty const &otherPerson)
{
    return this->id == otherPerson.id;
}
bool Faculty::operator!=(Faculty const &otherPerson)
{
    return this->id != otherPerson.id;
}
bool Faculty::operator>=(Faculty const &otherFaculty)
{
    return this->id >= otherFaculty.id;
}
bool Faculty::operator<=(Faculty const &otherFaculty)
{
    return this->id <= otherFaculty.id;
}
//checks if the faculty has any advisees at all
bool Faculty::hasAdvisees()
{
    return (advisees ->getSize() != 0);
}
//returns an array of all advisee ids
int* Faculty::returnAllAdvisees()
{
    //get number of iterations
    int numberofStudents = advisees ->getSize();
    //new int array to store ids
    int *output = new int[numberofStudents];
    int index =0;
    //removes all advisee ids from the list and put them in the array to be returned 
    while(!advisees ->isEmpty())
    {
        output[index++] = advisees ->removeFront();
    }
    //add all ids back to the list
    for(int i =0; i <numberofStudents;++i)
        advisees -> insertBack(output[i]);
    return output;
}
//returns the number of advisees in the list
int Faculty::getAdviseeNumber()
{
    return advisees ->getSize();
}
//returns the serializable string in comma separated format
string Faculty::getSerializable()
{
    string returner = (to_string(this->id) + "," +
                       this->name + "," + this->level + ","+
                       this->department);
    //stores advisee ids in an array
    int *adviseeIds = this ->returnAllAdvisees();
    int adviseeLength = this ->getAdviseeNumber();
    //serialize how many advisees there are
    returner = returner + ","+ to_string(adviseeLength);
    //append advisee ids to the output to be serialized
    for(int i =0; i <adviseeLength;++i)
        returner = (returner + ","+to_string(adviseeIds[i]));
    //add one comma to the end to make it work with how we read in the csv format
    returner = returner + ",";
    return returner;
}