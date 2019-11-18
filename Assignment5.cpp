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
    Student *thestud = new Student(45,"Noah","Senior","Data Analytics",4.0,555);
    Student *newStud = new Student(44,"Isabel","junior","PR and AD",4.0,445);
    studentTree -> insert(newStud);
    studentTree -> insert(thestud);

    Faculty *teacher2 = new Faculty(555,"Jerry Seinfeld","professor","Schmid");
    teacher2 ->addAdvisee(thestud ->getId());
    teacher2 ->addAdvisee(newStud->getId());
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
    else if (inNum == 5)
    {
        cout << "Enter the id number of the student to view all of their advisor information"<<endl;
        cin >> inNum;
        Student *tempStud = new Student(inNum);
        Student *result;
        result = studentTree ->search(tempStud);
        if(result)
        {
            Faculty *facResult;
            int advisorId = result ->getAdvisorId();
            Faculty *searcher = new Faculty(advisorId);
            facResult = facultyTree->search(searcher);
            if(facResult)
            {
                cout << "Advisor Information:\n";
                cout << facResult->toString();
            }
            else 
                cout <<"Advisor number stored for student not found"<<endl;
            
        }
        else 
            cout << "No student with that ID was found" <<endl;
    }
    else if(inNum == 6)
    {
        cout <<"Enter the id of the faculty member you want to see the advisees for"<<endl;
        cin >>inNum;

    }
    else if(inNum == 11)
    {
        cout << "Enter the id number of the student you wish to edit."<<endl;
        cin >>inNum;
        Student *temp = new Student(inNum);
        Student* studentToEdit = studentTree ->search(temp);
        if(studentToEdit)
        {
            cout << "Enter the id number of the new advisor for the student" << endl;
            cin >>inNum;
            Faculty *finder = new Faculty(inNum);
            Faculty *result = facultyTree ->search(finder);
            if(result)
            {
                studentToEdit ->setAdvisorId(result ->getId());
                cout <<"Student advisor id sucessfully updated"<<endl;
                cout <<"Updated entry"<<endl;
                cout << studentToEdit ->toString()<<endl;
            }
            else 
                cout <<"Faculty with that id number does not exist"<<endl;
            delete finder;
        }
        else 
            cout <<"Student with that ID not found"<<endl;
        delete temp;
      
    }
    else if(inNum == 12)
    {
        cout <<"Enter the ID number of the advisor you wish to edit"<<endl;
        cin >>inNum;
        Faculty *temp = new Faculty(inNum);
        Faculty *facToEdit = facultyTree ->search(temp);
        if(facToEdit)
        {
            cout <<"Enter the id number of the student you wish to remove from the faculty's advisee list"<<endl;
            cin >> inNum;
            Student *tempStud = new Student(inNum);
            Student *result = studentTree ->search(tempStud);
            if(result)//student exists
            {
                bool answer = facToEdit ->removeAdvisee(tempStud ->getId());
                if(answer)
                {
                    cout << "Advissee successfully removed from list" << endl;
                    //need to reassign the student here
                }
                else 
                    cout <<"Advisee was not contained in the list"<<endl;
            }
            else 
                cout << "Student with that ID number not found"<<endl;
        }
        else 
            cout << "Faculty member with that ID number not found"<<endl;
    }


    delete facultyTree;
    delete studentTree;
    return 0;
}