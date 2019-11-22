#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "ExtendedTree.h"
#include "TextChecker.h"

using namespace std;


int main(int argc, char** argv)
{
    TextChecker textHelper;
    ExtendedTree<Faculty*> *facultyTree = new ExtendedTree<Faculty*>();
    ExtendedTree<Student*> *studentTree = new ExtendedTree<Student*>();
    Student *thestud = new Student(45,"Noah","Senior","Data Analytics",4.0,555);
    Student *newStud = new Student(44,"Isabel","junior","PR and AD",4.0,445);
    studentTree -> insert(newStud);
    studentTree -> insert(thestud);

    Faculty *teacher2 = new Faculty(555,"Jerry Seinfeld","professor","Schmid");
    teacher2 ->addAdvisee(thestud ->getId());
    Faculty *teacher = new Faculty(445,"Larry","Crean");
    teacher->addAdvisee(newStud->getId());
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
                      "\n13. Rollback"
                      "\n14. Exit");
    cout << theMenu <<endl;
    string holder;
    int inNum;
    double inDub;
    while(true)
    {
        cout << "Enter new command.\nEnter '0' to display options" << endl;
        getline(cin>>ws,holder);
        if(textHelper.isPositiveInteger(holder))
        {
            inNum = std::stoi(holder);
            if (inNum == 1)
            {
                cout << "-----All Students-----" << endl;
                studentTree->printToStrings();
            }
            else if (inNum == 2)
            {
                cout << "-----All Faculty-----" << endl;
                facultyTree->printToStrings();
            }
            else if (inNum == 3)
            {
                cout << "Please enter the id number of the student you wish to view." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Student *tempStudent = new Student(inNum);
                    Student *result;
                    result = studentTree->search(tempStudent);
                    if (result)
                        cout << result->toString() << endl;
                    else
                        cout << "***Student with that ID was not found***" << endl;
                    delete tempStudent;
                }
                else 
                    cout << "***Invalid input entered***"<<endl;
                
            }
            else if (inNum == 4)
            {
                cout << "Please enter the id number of the faculty member you wish to view." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Faculty *tempFac = new Faculty(inNum);
                    Faculty *tempResult;
                    tempResult = facultyTree->search(tempFac);
                    if (tempResult)
                        cout << tempResult->toString() << endl;
                    else
                        cout << "***Faculty member with that ID was not found***" << endl;
                    delete tempFac;
                }
                else 
                    cout<<"***Invalid ID entered***"<<endl;
                
            }
            else if (inNum == 5)
            {
                cout << "Enter the id number of the student to view all of their advisor information" << endl;
                getline(cin>>ws,holder);
                if (textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Student *tempStud = new Student(inNum);
                    Student *result;
                    result = studentTree->search(tempStud);
                    if (result)
                    {
                        Faculty *facResult;
                        int advisorId = result->getAdvisorId();
                        Faculty *searcher = new Faculty(advisorId);
                        facResult = facultyTree->search(searcher);
                        if (facResult)
                        {
                            cout << "-----Advisor Information:-----" << endl;
                            cout << facResult->toString();
                        }
                        else
                            cout << "***Advisor number stored for student not found***" << endl;
                    }
                    else
                        cout << "***No student with that ID was found***" << endl;
                }
                else 
                    cout << "***Invalid ID entered***"<<endl;                
            }
            else if (inNum == 6)
            {
                cout << "Enter the id of the faculty member you want to see the advisees for" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Faculty *searchFac = new Faculty(inNum);
                    Faculty *tempFac = facultyTree->search(searchFac);
                    if (tempFac)
                    {
                        if (tempFac->hasAdvisees())
                        {
                            int numAdvisees = tempFac->getAdviseeNumber();
                            int *theAdvisees = tempFac->returnAllAdvisees();
                            Student *finder;
                            for (int i = 0; i < numAdvisees; ++i)
                            {
                                finder = new Student(theAdvisees[i]);
                                cout << studentTree->search(finder)->toString() << endl;
                            }
                            delete finder;
                        }
                        else
                            cout << "***This advisor has no advisees***" << endl;
                    }
                    else
                        cout << "***Faculty with that id not found***" << endl;
                }
                else    
                    cout << "***Invalid ID entered***"<<endl;
                
            }
            else if (inNum == 7)
            {
                int newId, newAdvisorId;
                double newGpa;
                string newName, newLevel, newMajor;
                cout << "---New Student Entry---" << endl;
                cout << "Enter the id number of the new student:" << endl;
                getline(cin >> ws, holder);
                if (textHelper.isPositiveInteger(holder))
                {
                    newId = std::stoi(holder);
                    Student *finder = new Student(newId);
                    if (studentTree->search(finder))
                        cout << "***Student with that ID number already exists, command failed***" << endl;
                    else
                    {
                        cout << "Enter the name of the student" << endl;
                        getline(cin >> ws, holder);
                        if (textHelper.isPureText(holder) && holder.size() > 0)
                        {
                            newName = holder;
                            cout << "Enter the level/year for the student" << endl;
                            getline(cin >> ws, holder);
                            if (textHelper.isPureText(holder) && holder.size() > 0)
                            {
                                newLevel = holder;
                                cout << "Enter the student's major" << endl;
                                getline(cin >> ws, holder);
                                if (textHelper.isPureText(holder))
                                {
                                    newMajor = holder;
                                    cout << "Enter the GPA for the student" << endl;
                                    getline(cin >> ws, holder);
                                    if (textHelper.isNumeric(holder) && std::stod(holder) <= 4.5)
                                    {
                                        newGpa = std::stod(holder);
                                        cout << "Enter the id of the student's advisor" << endl;
                                        getline(cin >> ws, holder);
                                        if (textHelper.isPositiveInteger(holder))
                                        {
                                            newAdvisorId = std::stoi(holder);
                                            Faculty *searcher = new Faculty(newAdvisorId);
                                            Faculty *theAdvisor = facultyTree->search(searcher);
                                            if (theAdvisor)
                                            {
                                                Student *tempNewStud = new Student(newId, newName, newLevel, newMajor, newGpa, newAdvisorId);
                                                studentTree->insert(tempNewStud);
                                                theAdvisor->addAdvisee(tempNewStud->getId());
                                                cout << "Student successfully saved to system" << endl;
                                                cout << "---New Student Profile---\n"
                                                     << tempNewStud->toString() << endl;
                                                ////rollback functionality goes here
                                            }
                                            else
                                                cout << "***Advisor with that ID was not found, command aborted***" << endl;
                                            delete searcher;
                                        }
                                        else
                                            cout << "***Invalid advisor id entered, command aborted***" << endl;
                                    }
                                    else
                                        cout << "***Invalid gpa entered***" << endl;
                                }
                                else
                                    cout << "***Invalid major entered***" << endl;
                            }
                            else
                                cout << "***Invalid level/year entered, command aborted***" << endl;
                        }
                        else
                            cout << "***Invalid name entered, command aborted***" << endl;
                    }
                }
                else
                    cout << "***Invalid Id number entered, command aborted***" << endl;
            }
            else if (inNum == 8)
            {
                cout << "Enter the id number of the student you want to delete" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Student *searcher = new Student(inNum);
                    Student *tempStud = studentTree->search(searcher);
                    if (tempStud)
                    {
                        int studId = tempStud->getId();
                        int advisorId = tempStud->getAdvisorId();
                        Faculty *finder = new Faculty(advisorId);
                        Faculty *found = facultyTree->search(finder);
                        if (found)
                        {
                            if (studentTree->deleteNode(tempStud))
                            {
                                cout << "--Student successfully deleted--" << endl;
                                if (found->removeAdvisee(studId))
                                    cout << "Student removed from " << found->getName() << "'s advisee list" << endl;
                                else
                                    cout << "***Error removing student from advisor's advisee list***" << endl;
                                ////need to store the rollback call here
                            }
                        }
                        else
                            cout << "***Error in removing the student from advisor list, command aborted***" << endl;
                        delete finder;
                    }
                    else
                        cout << "***Student with that Id not found***" << endl;
                    delete searcher;
                }
                else 
                    cout <<"***Invalid ID entered***"<<endl;
                
            }
            else if (inNum == 9)
            {
                int newId;
                string newName, newLevel, newMajor, newDepartment;
                cout << "Enter the ID number for the new faculty member" << endl;
                getline(cin >> ws, holder);
                if (textHelper.isPositiveInteger(holder))
                {
                    newId = std::stoi(holder);
                    Faculty *searcher = new Faculty(newId);
                    if (!(facultyTree->search(searcher)))
                    {
                        cout << "Enter the name of the faculty member" << endl;
                        getline(cin >> ws, holder);
                        if (textHelper.isPureText(holder))
                        {
                            newName = holder;
                            cout << "Enter the new faculty member's position/title" << endl;
                            getline(cin >> ws, holder);
                            if (textHelper.isPureText(holder))
                            {
                                newLevel = holder;
                                cout << "Enter the department the faculty member is in" << endl;
                                getline(cin >> ws, holder);
                                if (textHelper.isPureText(holder))
                                {
                                    newDepartment = holder;
                                    Faculty *newFac = new Faculty(newId, newName, newLevel, newDepartment);
                                    facultyTree->insert(newFac);
                                    cout << "New faculty member successfully added to the database" << endl;
                                    cout << "---New Faculty Profile Info---\n"
                                         << newFac->toString() << endl;
                                }
                                else
                                    cout << "***Invalid department entered, command aborted***" << endl;
                            }
                            else
                                cout << "***Invalid position entered, command aborted***" << endl;
                        }
                        else
                            cout << "***Invalid name entered, command aborted***" << endl;
                    }
                    else
                        cout << "***Faculty member with that ID number already exists, command aborted***" << endl;
                }
                else
                    cout << "***Invalid ID number entered, command aborted***" << endl;
            }
            else if (inNum == 10)
            {
                cout << "Enter the id number of the faculty member you wish to delete" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Faculty *searcher = new Faculty(inNum);
                    Faculty *tempFac = facultyTree->search(searcher), *replacement;
                    Student *finder, *temp;
                    bool success = true;
                    if (tempFac)
                    {
                        int adviseeCount = tempFac->getAdviseeNumber();
                        int *adviseeArray;
                        if (adviseeCount > 0)
                        {
                            adviseeArray = tempFac->returnAllAdvisees();
                            for (int i = 0; i < adviseeCount; ++i)
                            {
                                finder = new Student(adviseeArray[i]);
                                temp = studentTree->search(finder);
                                replacement = facultyTree->getEntryOtherThan(tempFac);
                                if (replacement)
                                {
                                    temp->setAdvisorId(replacement->getId());
                                    replacement->addAdvisee(temp->getId());
                                    tempFac->removeAdvisee(adviseeArray[i]);
                                }
                                else
                                {
                                    cout << "***No suitable advisors available to take on remaining students, operation aborted***" << endl;
                                    success = false;
                                    break;
                                }
                            }
                            if (success)
                                cout << "Advisees passed on to next available faculty member" << endl;
                        }
                        if (success)
                        {
                            if (facultyTree->deleteNode(searcher))
                                cout << "--Faculty member effectively deleted--" << endl;
                            else
                                cout << "***Error deleting faculty member***" << endl;
                        }
                        else
                            cout << "***Unable to delete faculty member***" << endl;
                    }
                    else
                        cout << "***Faculty member with that ID number not found***" << endl;
                    delete finder;
                    delete searcher;
                }
                else 
                    cout << "***Invalid ID entered***"<<endl;                
            }
            else if (inNum == 11)
            {
                cout << "Enter the id number of the student you wish to edit." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Student *temp = new Student(inNum);
                    Student *studentToEdit = studentTree->search(temp);
                    if (studentToEdit)
                    {
                        cout << "Enter the id number of the new advisor for the student" << endl;
                        getline(cin>>ws,holder);
                        if(textHelper.isPositiveInteger(holder))
                        {
                            inNum = std::stoi(holder);
                            Faculty *finder = new Faculty(inNum);
                            Faculty *result = facultyTree->search(finder);
                            if (result)
                            {
                                int previousAdvisorId = studentToEdit->getAdvisorId();
                                studentToEdit->setAdvisorId(result->getId());
                                result->addAdvisee(studentToEdit->getId());

                                Faculty *previousAdvisor = new Faculty(previousAdvisorId);
                                facultyTree->search(previousAdvisor)->removeAdvisee(studentToEdit->getId());
                                cout << "Student advisor id sucessfully updated" << endl;
                                cout << "Updated entry" << endl;
                                cout << studentToEdit->toString() << endl;
                            }
                            else
                                cout << "***Faculty with that id number does not exist***" << endl;
                            delete finder;
                        }
                        else
                            cout << "***Invalid ID entered***"<<endl;
                    }
                    else
                        cout << "***Student with that ID not found***" << endl;
                    delete temp;
                }
                else 
                    cout << "***Invalid ID entered***"<<endl;                
            }
            else if (inNum == 12)
            {
                cout << "Enter the ID number of the advisor you wish to edit" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))
                {
                    inNum = std::stoi(holder);
                    Faculty *temp = new Faculty(inNum);
                    Faculty *facToEdit = facultyTree->search(temp);
                    if (facToEdit)
                    {
                        cout << "Enter the id number of the student you wish to remove from the faculty's advisee list" << endl;
                        getline(cin>>ws,holder);
                        if(textHelper.isPositiveInteger(holder))
                        {
                            inNum = std::stoi(holder);
                            Student *tempStud = new Student(inNum);
                            Student *result = studentTree->search(tempStud);
                            if (result) //student exists
                            {
                                bool answer = facToEdit->removeAdvisee(tempStud->getId());
                                if (answer)
                                {
                                    Faculty *tempFac;
                                    tempFac = facultyTree->getEntryOtherThan(facToEdit);
                                    if (tempFac)
                                    {
                                        result->setAdvisorId(tempFac->getId());
                                        tempFac->addAdvisee(tempStud->getId());
                                        cout << "Advissee successfully removed from list and reassigned to next available faculty." << endl;
                                        cout << "New assigned advisor: \n"
                                             << facultyTree->search(tempFac)->toString() << endl;
                                    }
                                    else
                                    {
                                        facToEdit->addAdvisee(result->getId());
                                        cout << "***No other faculty members are available to take this student. Command cancelled***" << endl;
                                    }
                                }
                                else
                                    cout << "***Advisee was not contained on this faculty member's list***" << endl;
                            }
                            else
                                cout << "***Student with that ID number not found***" << endl;
                            delete tempStud;
                        }  
                        else 
                            cout << "***Invalid ID entered***"<<endl;                      
                    }
                    else
                        cout << "***Faculty member with that ID number not found***" << endl;
                    delete temp;
                }
                else 
                    cout <<"***Invalid Id entered***"<<endl;                
            }
            else if (inNum == 14)
            {
                cout << "Program closed and data saved." << endl;
                break;
            }
            else if (inNum == 0)
                cout << theMenu << endl;
        }        
        else 
            cout << "*Invalid command entered*"<<endl;
    }

    

    delete facultyTree;
    delete studentTree;
    return 0;
}