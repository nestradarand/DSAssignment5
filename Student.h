#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include "Person.h"

class Student : public Person
{
    public:
        Student();
        Student(int newId);
        Student(int newId, std::string newName);
        Student(int newId, std::string newName, std::string newLevel);

    private:
        std::string major;
        double gpa;
        int advisorId;
};
#endif