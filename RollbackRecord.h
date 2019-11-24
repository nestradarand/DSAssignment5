#ifndef ROLLBACKRECORD_H
#define ROLLBACKRECORD_H
#include <string>



class RollbackRecord 
{
    public:
        RollbackRecord();
        RollbackRecord(bool isStud,std::string newData,char newAction);
        ~RollbackRecord();
        bool isStudent;
        char action;
        std::string data;
};
#endif