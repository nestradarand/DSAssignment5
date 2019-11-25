/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#ifndef TEXTCHECKER_H
#define TEXTCHECKER_H
#include <string>


//class to see if a string contains numeric, integer or text without numeric characters
class TextChecker
{

    public:
        //default constructor
        TextChecker();
        //destructor
        ~TextChecker();
        //returns if a string is numeric(incling decimal numbers)
        bool isNumeric(std::string str);
        //returns if a string only contains non numeric characters
        bool isPureText(std::string str);
        //returns if a string is a postiive integer value
        bool isPositiveInteger(std::string str);
};




#endif