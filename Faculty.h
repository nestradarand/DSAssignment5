#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include "Person.h"
#include "DoublyLinkedList.h"

class Faculty : public Person 
{
    public:
        Faculty();
        Faculty(int newId);
        Faculty(int newId, std::string newName);
        Faculty(int newId, std::string newName, std::string newLevel);
        Faculty(int newId, std::string newName, std::string newLevel, std::string newDepartment);
        ~Faculty();
        std::string getDepartment();
        void setDepartment(std::string newDepartment);
        void addAdvisee(int i);
        void printAllAdvisees();
        bool removeAdvisee(int i);
        bool hasAdvisee(int studId);
        bool hasAdvisees();
        std::string toString();
        std::string department;
        DoublyLinkedList<int> *advisees = new DoublyLinkedList<int>();

        bool operator==(Faculty const &otherFaculty);
        bool operator>(Faculty const &otherFaculty);
        bool operator<(Faculty const &otherFaculty);
        bool operator>=(Faculty const &otherFaculty);
        bool operator<=(Faculty const &otherFaculty);
        bool operator!=(Faculty const &otherFaculty);
};
#endif