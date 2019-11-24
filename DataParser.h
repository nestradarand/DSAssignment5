#ifndef DATAPARSER_H
#define DATAPARSER_H
#include "DLQueue.h"
#include "Student.h"
#include "Faculty.h"
#include <string>

class DataParser
{
    public:
        DataParser();
        ~DataParser();
        void putDataInQueue(std::string str, DLQueue<std::string> *queue);
        Student *getStudentFromDataQueue(DLQueue<std::string> *queue);
        Faculty *getFacultyFromDataQueue(DLQueue<std::string> *queue);
};
#endif