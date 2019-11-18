#ifndef PERSON_H
#define PERSON_H
#include <string>


class Person
{
    public:
        Person();
        Person(int newId);
        Person(int newId,std::string newName);
        Person(int newId,std::string newName,std::string newLevel);
        std::string getName();
        void setName(std::string newName);
        std::string getLevel();
        void setLevel(std::string newLevel);
        int getId();
        void setId(int newId);
        std::string toString();


        // friend bool operator==(const Person &firstPerson,const Person &secondPerson);

 
        int id;
        std::string level;
        std::string name;      
        bool isvalidString(std::string str); 
};

#endif