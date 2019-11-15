#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "BST.h"

using namespace std;

int main(int argc, char** argv)
{    
    BST<Faculty*> *facultyTree = new BST<Faculty*>();
    BST<Student*> *studentTree = new BST<Student*>();
    Student *thestud = new Student(343,"Noah","Sophomore");
    studentTree -> insert(thestud);
    Faculty *teacher = new Faculty(445,"Larry","Crean");
    facultyTree -> insert(teacher);

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
        cout <<"Feature coming soon"<<endl;            
    }



    delete facultyTree;
    delete studentTree;
    return 0;
}