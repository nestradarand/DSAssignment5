#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"

using namespace std;

int main(int argc, char** argv)
{
    Student *thestud = new Student();
    cout << thestud ->getName() <<endl;
    delete thestud;
    return 0;
}