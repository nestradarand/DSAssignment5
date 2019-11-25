/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
#include "TextChecker.h"
#include <string>
#include <iostream>

using namespace std;
//constructor
TextChecker::TextChecker()
{

}
//desctructor
TextChecker::~TextChecker()
{

}
//checks if string is numerical or decimal number
bool TextChecker::isNumeric(string str)
{
    int stringLength = str.length();
    int decimalCount = 0;
    //iterates over all characters and returns false if character was not a digit or decimal point
    for(int i =0; i<stringLength;++i)
    {
        if (!isdigit(str[i]) && str[i] != '.')
            return false;
        else if (str[i] == '.')
            decimalCount++;
        if(decimalCount >1)
            return false;
    }
     //asssuming no non numerical characters wer foudn we return true
    return true;
}
//checks if a string has no numeric characters in it
bool TextChecker::isPureText(string str)
{
    int stringLength = str.length();
    for (int i = 0; i < stringLength; ++i)
        if (isdigit(str[i]))//if any character is a number, we return false
            return false;
    return true;
}
//checks to see that the input is a positive integer number
bool TextChecker::isPositiveInteger(string str)
{
    int stringLength = str.length();
    for (int i = 0; i < stringLength; ++i)
    {
        if (!isdigit(str[i]))
            return false;
        else if (str[i] == '.')//if a decimal is found we return false
            return false;        
    }

    return true;
}
