#ifndef TEXTCHECKER_H
#define TEXTCHECKER_H
#include <string>

class TextChecker
{

    public:
        TextChecker();
        ~TextChecker();
        bool isNumeric(std::string str);
        bool isPureText(std::string str);
        bool isPositiveInteger(std::string str);
};




#endif