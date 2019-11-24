#include "DataParser.h"
#include <string>


using namespace std;

DataParser::DataParser(){}
DataParser::~DataParser(){}

Student* DataParser::getStudentFromDataQueue(DLQueue<string> *queue)
{
    try
    {
        int id, advisorId;
        double gpa;
        string name, level, major;
        id = std::stoi(queue->dequeue());
        name = queue->dequeue();
        level = queue->dequeue();
        major = queue->dequeue();
        gpa = std::stod(queue->dequeue());
        advisorId = std::stoi(queue->dequeue());
        Student *newStud = new Student(id, name, level, major, gpa, advisorId);
        return newStud;
    }
    catch (std::exception e)
    {
        return NULL;
    }
}
Faculty* DataParser::getFacultyFromDataQueue(DLQueue<string> *queue)
{
    try
    {
        int id, numAdvisees;
        string name, level, department;
        id = std::stoi(queue->dequeue());
        name = queue->dequeue();
        level = queue->dequeue();
        department = queue->dequeue();
        numAdvisees = std::stoi(queue->dequeue());
        Faculty *newFac = new Faculty(id, name, level, department);
        for (int i = 0; i < numAdvisees; ++i)
        {
            newFac->addAdvisee(std::stoi(queue->dequeue()));
        }
        return newFac;
    }
    catch (std::exception e)
    {
        return NULL;
    }
}

void DataParser::putDataInQueue(string str, DLQueue<string> *queue)
{
    string delimiter = ",";
    ////from reference stack overflow
    int pos = 0;
    string newData;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        newData = str.substr(0, pos);
        queue->enqueue(newData);
        str.erase(0, pos + delimiter.length());
    }
}