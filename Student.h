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
        Student(int newId, std::string newName,
                 std::string newLevel,std::string newMajor);
        Student(int newId, std::string newName,
                std::string newLevel, std::string newMajor,
                double newGPA);
        Student(int newId, std::string newName,
                std::string newLevel, std::string newMajor,
                double newGPA,int newAdvisorId);
        std::string toString();
        void setMajor(std::string newMajory);
        std::string getMajor();
        void setGPA(double newGPA);
        double getGPA();
        void setAdvisorId(int i );
        int getAdvisorId();

    private:
        std::string major;
        double gpa;
        int advisorId;
};
#endif