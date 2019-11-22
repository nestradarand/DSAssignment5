#include "TextChecker.h"
#include <string>
#include <iostream>

using namespace std;

TextChecker::TextChecker()
{

}
TextChecker::~TextChecker()
{

}
bool TextChecker::isNumeric(string str)
{
    int stringLength = str.length();
    int decimalCount = 0;
    for(int i =0; i<stringLength;++i)
    {
        if (!isdigit(str[i]))
            return false;
        else if (str[i] == '.')
            decimalCount++;
        if(decimalCount >1)
            return false;
    }
     
    return true;
}
bool TextChecker::isPureText(string str)
{
    int stringLength = str.length();
    for (int i = 0; i < stringLength; ++i)
        if (isdigit(str[i]))
            return false;
    return true;
}
bool TextChecker::isInteger(string str)
{
    int stringLength = str.length();
    for (int i = 0; i < stringLength; ++i)
    {
        if (!isdigit(str[i]))
            return false;
        else if (str[i] == '.')
            return false;        
    }

    return true;
}
