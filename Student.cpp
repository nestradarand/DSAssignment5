#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

Student::Student() : Person()
{
    major = "N/A";
    gpa = 0.00;
    advisorId = -1;
}
Student::Student(int newId) : Person (newId){}
Student::Student(int newId, std::string newName) : Person(newId,newName){}
Student::Student(int newId, std::string newName, std::string newLevel) : Person(newId,newName,newLevel){}