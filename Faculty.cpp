#include "Faculty.h"
#include <string>
#include <iostream>

using namespace std;


Faculty::Faculty() : Person(){}
Faculty::Faculty(int newId) : Person (newId){}
Faculty::Faculty(int newId,string newName) : Person(newId,newName){}
Faculty::Faculty(int newId,string newName,string newLevel) : Person(newId,newName,newLevel){}