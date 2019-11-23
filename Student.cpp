#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student() : Person()
{
    major = "N/A";
    gpa = -1.00;
    advisorId = -1;
}
Student::Student(int newId) : Person (newId){
    major = "N/A";
    gpa = -1.00;
    advisorId = -1;
}
Student::Student(int newId, std::string newName) : Person(newId,newName){
    major = "N/A";
    gpa = -1.00;
    advisorId = -1;
}
Student::Student(int newId, std::string newName, std::string newLevel) : Person(newId,newName,newLevel){
    major = "N/A";
    gpa = -1.00;
    advisorId = -1;
}
Student::Student(int newId,std::string newName,std::string newLevel,
                std::string newMajor) : Person(newId,newName,newLevel)
{
    major = newMajor;
    gpa = -1.00;
    advisorId == -1;
}
Student::Student(int newId, std::string newName,std::string newLevel, std::string newMajor,
                                                    double newGPA) : Person(newId,newName,newLevel)
{
    major = newMajor;
    gpa = newGPA;
    advisorId = -1;
}
Student::Student(int newId, std::string newName, std::string newLevel, std::string newMajor,
                 double newGPA,int newAdvisorId) : Person(newId, newName, newLevel)
{
    major = newMajor;
    gpa = newGPA;
    advisorId = newAdvisorId;
}
string Student::toString()
{
    string returner = (Person::toString() +
                        "\nMajor: " + major +
                        "\nGPA: " + to_string(gpa) + 
                        "\nAdvisor ID: " + to_string(advisorId));
    return returner;
}
void Student::setMajor(std::string newMajor)
{
    major = newMajor;
}
std::string Student::getMajor()
{
    return major;
}
void Student::setGPA(double newGPA)
{
    gpa = newGPA;
}
double Student::getGPA()
{
    return gpa;
}
void Student::setAdvisorId(int i)
{
    advisorId = i;
}
int Student::getAdvisorId()
{
    return advisorId;
}
bool Student::operator<(Student const &otherPerson) 
{
    return this -> id < otherPerson.id;
}
bool Student::operator>(Student const &otherPerson)
{
    return this->id > otherPerson.id;
}
bool Student::operator==(Student const &otherPerson)
{
    return this->id == otherPerson.id;
}
bool Student::operator!=(Student const &otherPerson)
{
    return this->id != otherPerson.id;
}
bool Student::operator>=(Student const &otherStudent)
{
    return this -> id >= otherStudent.id;
}
bool Student::operator<=(Student const &otherStudent)
{
    return this->id <= otherStudent.id;
}
Student::~Student(){
}
string Student::getSerializable()
{
    string returner = (to_string(this->id) + "," + 
                       this->name + "," + this ->level + ","+ 
                       this ->major + "," + to_string(this->gpa)+
                       "," + to_string(this->advisorId)+",");
    return returner;
}
