#include "RollbackRecord.h"
#include <iostream>
#include <string>

using namespace std;

RollbackRecord::RollbackRecord()
{
    this ->isStudent = false;
}
RollbackRecord::RollbackRecord(bool isStud, string newData,char newAction)
{
    this ->isStudent = isStud;
    this ->data = newData;
    this ->action = newAction;
}
RollbackRecord::~RollbackRecord(){}

