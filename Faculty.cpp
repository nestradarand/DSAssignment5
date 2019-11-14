#include "Faculty.h"
#include <string>
#include <iostream>

using namespace std;


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
Faculty::Faculty(int newId, string newName, string newLevel, string newDepartment) : Person(newId, newName, newLevel) 
{
    department = newDepartment;
}
Faculty::~Faculty()
{
    delete advisees;
}
string Faculty::getDepartment()
{
    return department;
}
void Faculty::setDepartment(string newDep)
{
    department = newDep;
}
void Faculty::addAdvisee(int i )
{
    advisees -> insertBack(i);
}
void Faculty::printAllAdvisees()
{
    advisees -> printList();
}
void Faculty::removeAdvisee(int i)
{
    advisees -> remove(i);
}
bool Faculty::hasAdvisee(int studId)
{
    int result = advisees -> find(studId);
    if(result == -1)
        return false;
    else 
        return true;
}
string Faculty::toString()
{
    string returner = (Person::toString() +
                        "\nDepartment: " + department +
                        "\nNumber of Advisees: " + 
                        to_string(advisees -> getSize()));
    return returner;
}
