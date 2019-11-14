#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

int main(int argc, char** argv)
{
    Person *person = new Person(20,"Noah Estrada-Rand","Sophomore");
    person -> setId(3);
    person -> setName("Herbert");
    person -> setLevel("Freshmen");
    cout << person -> toString()<< endl;
    delete person;
    return 0;
}