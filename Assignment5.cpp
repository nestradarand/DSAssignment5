#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"

using namespace std;

int main(int argc, char** argv)
{
    Student *thestud = new Student(34,"Noah Estrada-Rand","Senior",
                                    "Data Analytics",3.49,334);
    string x;
    cin >>x;
    thestud -> setMajor(x);
    cout << thestud -> toString() <<endl;
    delete thestud;
    return 0;
}