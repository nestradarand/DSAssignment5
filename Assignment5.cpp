#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "BST.h"

using namespace std;

int main(int argc, char** argv)
{

    Faculty * per1 = new Faculty(34,"Noah","Senior","Crean");
    Faculty *per2 = new Faculty(69,"Isabel","Senior","Dodge");
    BST<Faculty*> *theTree = new BST<Faculty*>();
    theTree ->insert(per1);
    theTree -> insert(per2);
    theTree -> printInOrder();
    delete theTree;
    return 0;
}