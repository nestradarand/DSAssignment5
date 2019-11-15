#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"

using namespace std;

int main(int argc, char** argv)
{
    Faculty * per1 = new Faculty(34,"Noah","Senior","Crean");
    Faculty *per2 = new Faculty(69,"Isabel","Senior","Dodge");
    cout << (per1 > per2)<<endl;
    delete per1, per2;
    return 0;
}