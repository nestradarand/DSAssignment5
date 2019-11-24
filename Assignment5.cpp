#include <iostream>
#include <string>
#include "Person.h"
#include "Student.h"
#include "Faculty.h"
#include "ExtendedTree.h"
#include "TextChecker.h"
#include "DLQueue.h"
#include "RollbackRecord.h"
#include "DataParser.h"
#include "GenStack.h"

using namespace std;



int main(int argc, char** argv)
{
    TextChecker textHelper;
    ExtendedTree<Faculty*> *facultyTree = new ExtendedTree<Faculty*>();
    ExtendedTree<Student*> *studentTree = new ExtendedTree<Student*>();
    DataParser *parser = new DataParser();
    

    //Reading in existing data
    ifstream inStudentfile,inFacultyFile;
    inStudentfile.open("studentTable.txt");
    inFacultyFile.open("facultyTable.txt");
    if(!inStudentfile)
        cout << "**Error finding saved data for students, new file will be created to store database**\n**New database created**"<<endl;
    if(!inFacultyFile)
        cout << "**Error finding saved data for faculty members, new file will be created to store database**\n**New database created**"<<endl;
    ///reading in all serialized data`
    
    string fileInput;

    DLQueue<string> *fileQueue = new DLQueue<string>();
    //read in student data
    while(getline(inStudentfile,fileInput))
    {
        parser -> putDataInQueue(fileInput,fileQueue);
        Student *newStud = parser -> getStudentFromDataQueue(fileQueue);
        if(newStud)
            studentTree ->insert(newStud);
        else 
            cout << "**Error reading in student data**"<<endl;
    }
    while (getline(inFacultyFile, fileInput))
    {
        parser->putDataInQueue(fileInput, fileQueue);
        Faculty *newFac = parser->getFacultyFromDataQueue(fileQueue);
        if(newFac)
            facultyTree ->insert(newFac);
        else 
            cout <<"**Error reading in faculty data**"<<endl;
    }
    
    delete fileQueue;
    inStudentfile.close();
    inFacultyFile.close();
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
                      "\n12. Remove an advisee from a faculty member given their id"
                      "\n13. Rollback"
                      "\n14. Exit");
    cout << theMenu <<endl;
    string holder;
    int inNum;
    double inDub;
    GenStack<RollbackRecord*> *rollbackStack = new GenStack<RollbackRecord*>();
    while(true)
    {
        cout << "----Enter new command----\nEnter '0' to display options" << endl;
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
                            cout << facResult->toString()<<endl;;
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
                            cout <<"---Advisees---"<<endl;
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
                                                RollbackRecord *newRec = new RollbackRecord(true, to_string(tempNewStud->getId()), 'd');
                                                rollbackStack->push(newRec);
                                                cout << "Student successfully saved to system" << endl;
                                                cout << "---New Student Profile---\n"
                                                     << tempNewStud->toString() << endl;
                                                
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
                            string oldInfo = tempStud ->getSerializable();
                            if (studentTree->deleteNode(tempStud))
                            {
                                if (found->removeAdvisee(studId))
                                    cout << "Student removed from " << found->getName() << "'s advisee list" << endl;
                                else
                                    cout << "***Error removing student from advisor's advisee list***" << endl;
                                RollbackRecord *newRecord = new RollbackRecord(true,oldInfo,'a');
                                rollbackStack ->push(newRecord);
                                cout << "--Student successfully deleted--" << endl;
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
                                    RollbackRecord *newRec = new RollbackRecord(false,to_string(newFac->getId()),'d');
                                    rollbackStack ->push(newRec);
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
                            delete finder;
                            if (success)
                                cout << "*Advisees re-assigned to next available faculty member*" << endl;
                        }
                        if (success)
                        {
                            string facInfo = tempFac ->getSerializable();
                            if (facultyTree->deleteNode(searcher))
                            {
                                RollbackRecord *afterInfo = new RollbackRecord(false,facInfo,'a');
                                rollbackStack ->push(afterInfo);
                                cout << "--Faculty member effectively deleted--" << endl;
                            }
                            else
                                cout << "***Error deleting faculty member***" << endl;
                        }
                        else
                            cout << "***Unable to delete faculty member***" << endl;
                    }
                    else
                        cout << "***Faculty member with that ID number not found***" << endl;
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
                                        cout << "Advisee successfully removed from list and reassigned to next available faculty." << endl;
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
            else if (inNum == 13)
            {
                //gets the most recent action
                if(!rollbackStack ->isEmpty())
                {
                    RollbackRecord *lastAction = rollbackStack->pop();
                    ///if the last alteration concerns a student record
                    DLQueue<string> *helperQueue = new DLQueue<string>();
                    string serialized = lastAction->data;
                    parser->putDataInQueue(serialized, helperQueue);
                    if (lastAction->action == 'a')
                    {
                        if (lastAction->isStudent == true)
                        {
                            Student *redo = parser->getStudentFromDataQueue(helperQueue);
                            if (redo)
                            {
                                studentTree->insert(redo);
                                Faculty *finder = new Faculty(redo->getAdvisorId());
                                Faculty *priorAdvisor = facultyTree->search(finder);
                                priorAdvisor->addAdvisee(redo->getId());
                                cout << "--Student successfully readded to the database--" << endl;
                                delete finder;
                            }
                            else
                                cout << "**Error attempting to undo student deletion**" << endl;
                        }
                        else
                        {
                            Faculty *redo = parser->getFacultyFromDataQueue(helperQueue);
                            if (redo)
                            {
                                facultyTree->insert(redo);
                                cout << "--Faculty effectively re-added to the database--" << endl;
                            }
                            else
                                cout << "**Error attempting to undo faculty deletion**" << endl;
                        }
                    }
                    else if (lastAction->action == 'd')
                    {
                        if (lastAction->isStudent == true)
                        {
                            int redoId = std::stoi(lastAction ->data);
                            if (redoId)
                            {
                                Student *temp = new Student(redoId);
                                Student *found = studentTree ->search(temp);
                                Faculty *finder = new Faculty(found ->getAdvisorId());
                                Faculty *priorAdvisor = facultyTree->search(finder);
                                priorAdvisor->removeAdvisee(redoId);
                                studentTree->deleteNode(temp);  
                                delete temp;
                                delete finder;
                                cout << "--Student successfully un-added to the database--" << endl;
                            }
                            else
                                cout << "**Error attempting to undo student addition**" << endl;
                        }
                        else
                        {
                            Faculty *redo = new Faculty(std::stoi(lastAction->data));
                            Faculty *found = facultyTree ->search(redo);
                            delete redo;
                            if (found)
                            {
                                int numAdvisees = found ->getAdviseeNumber();
                                int *advisees = found ->returnAllAdvisees();
                                Student *temp,*finder;
                                Faculty *replacement = facultyTree->getEntryOtherThan(found);
                                if(replacement)
                                {
                                    for (int i = 0; i < numAdvisees; ++i)
                                    {
                                        finder = new Student(advisees[i]);
                                        temp = studentTree -> search(finder); 
                                        if (replacement)
                                        {
                                            temp->setAdvisorId(replacement->getId());
                                            replacement->addAdvisee(temp->getId());
                                            found->removeAdvisee(advisees[i]);
                                        }
                                        delete finder;
                                    }
                                    facultyTree->deleteNode(found);
                                    cout << "--Faculty effectively un-added to the database--" << endl;
                                }
                                else
                                {
                                    cout << "***No suitable advisors available to take on remaining students, operation aborted***" << endl;
                                }                                
                            }
                            else
                                cout << "**Error attempting to undo faculty addition**" << endl;
                        }
                    }
                    else
                        cout << "**Unknown error in attempting to undo last alteration to database**" << endl;

                    delete lastAction;
                    cout << "---Previous database alteration undone---" << endl;
                }
                else 
                    cout <<"**No changes in current session left to undo**"<<endl;
                
            }
            else if (inNum == 14)
            {
                ofstream facultyFile,studentFile;
                facultyFile.open("facultyTable.txt");
                studentFile.open("studentTable.txt");
                if(!facultyFile && !studentFile)
                {
                    cout << "Error saving to files" << endl;
                    break;
                }
                else 
                {
                    facultyTree->write(facultyFile);
                    studentTree->write(studentFile);
                    facultyFile.close();
                    studentFile.close();
                    cout << "Program closed and data saved." << endl;
                    break;
                }
            
                
               
            }
            else if (inNum == 0)
                cout << theMenu << endl;
        }        
        else 
            cout << "*Invalid command entered*"<<endl;
    }

    
    delete rollbackStack;
    delete facultyTree;
    delete studentTree;
    delete parser;
    return 0;
}
