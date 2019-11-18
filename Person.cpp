#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

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
void Person::setId(int i)
{
    id = i;
}
int Person::getId()
{
    return id;
}
void Person::setName(string newName)
{
    name = newName;
}
string Person::getName()
{
    return name;
}
void Person::setLevel(string str)
{
    level = str;
}
string Person::getLevel()
{
    return name;
}
string Person::toString()
{
    string returner = ("Name: " + name + 
                        "\nId number: " + to_string(id) +
                        "\nLevel: " + level);
    return returner;
}
// bool Person::operator < (const Person &otherPerson) 
// {
//     return this->id < otherPerson.id;
// }
// bool Person::operator > (const Person &otherPerson)
// {
//     return this->id > otherPerson.id;
// }
// bool Person::operator==(const Person &secondPerson)
// {
//     return (this->id == secondPerson.id);
// }
// bool Person::operator!=(const Person &secondPerson)
// {
//     return (this->id != secondPerson.id);
// }
// bool operator==(const Person &firstPerson,const Person &secondPerson)
// {
//     return firstPerson.id == secondPerson.id;
// }
