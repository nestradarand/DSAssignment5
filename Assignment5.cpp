#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "ExtendedTree.h"

using namespace std;


int main(int argc, char** argv)
{    
    
    ExtendedTree<Faculty*> *facultyTree = new ExtendedTree<Faculty*>();
    ExtendedTree<Student*> *studentTree = new ExtendedTree<Student*>();
    Student *thestud = new Student(45,"Noah","Senior");
    Student *newStud = new Student(44,"Isabel","junior");
    studentTree -> insert(newStud);
    studentTree -> insert(thestud);

    Faculty *teacher2 = new Faculty(555,"Jerry Seinfeld","professor","Schmid");
    Faculty *teacher = new Faculty(445,"Larry","Crean");
    facultyTree -> insert(teacher);
    facultyTree -> insert(teacher2);

    cout <<"Welcome to the student and faculty cataloging system"<< endl;
    string theMenu = ("Available Commands:\n1. Print all students and their information"
                      "\n2. Print all faculty and their information"
                      "\n3. Find and display student information using student id"
                      "\n4. Find and display faculty information using faculty id" 
                      "\n5. Find a students faculty advisor"
                      "\n6. Print all advisees of an advisor"
                      "\n7. Add a new student"
                      "\n8. Delete a student given their id number"
                      "\n9. Add a new faculty member"
                      "\n10. Delete a faculty member using their faculty id"
                      "\n11. Change students advisor given their student id and new faculty id"
                      "\n12. Remove an advisee froma faculty member given their id"
                      "\n12. Rollback"
                      "\n13. Exit");
    cout << theMenu <<endl;
    string inStr;
    int inNum;
    double inDub;
    cin >> inNum;
    if(inNum == 1)
    {
        cout << "All Students:" << endl;
        studentTree->printToStrings();
    }
    else if (inNum == 2)
    {
        cout << "All Faculty:" <<endl;
        facultyTree->printToStrings();
    }
    else if(inNum == 3)
    {
        cout << "Please enter the id number of the student you wish to view." <<endl;
        cin >> inNum;
        Student* tempStudent = new Student(inNum);
        Student *result;
        result = studentTree -> search(tempStudent);
        if (result)
            cout << result->toString();
        else
            cout << "Student with that ID was not found." << endl;
        delete tempStudent;
    }
    else if (inNum == 4)
    {
        cout << "Please enter the id number of the faculty member you wish to view." << endl;
        cin >> inNum;
        Faculty *tempFac = new Faculty(inNum);
        Faculty *tempResult;
        tempResult = facultyTree->search(tempFac);
        if(tempResult)
            cout << tempResult -> toString();
        else 
            cout << "Faculty member with that ID was not found."<<endl;
        delete tempFac;
    }

    delete facultyTree;
    delete studentTree;
    return 0;
}