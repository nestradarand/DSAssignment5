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

    private:
        std::string department;
        DoublyLinkedList<int> *advisees = new DoublyLinkedList<int>();
};
#endif