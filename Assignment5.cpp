/*
Name: Noah Estrada-Rand
Student ID#: 2272490
Chapman email: estra146@mail.chapman.edu
Course Number and Section: CPSC-350-01
Assignment: Assignment 5 Advisor/Student Database
*/
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


/*This main method contains all functionality for managing and interacting with 
the database containing students and faculty members.
*/

//declared in this class as they did not make sense to do so in other classes
Student* searchByStudentId(int i,ExtendedTree<Student*> *tree);
Faculty* searchByFacultyId(int i,ExtendedTree<Faculty*> *tree);


int main(int argc, char** argv)
{
    //initialization of classes to help with reading in and storing data
    TextChecker textHelper;//checks the contents of input from the user
    ExtendedTree<Faculty*> *facultyTree = new ExtendedTree<Faculty*>();//used to store faculty instances
    ExtendedTree<Student*> *studentTree = new ExtendedTree<Student*>();//stores student instances
    DataParser *parser = new DataParser();//to parse through serialized csv data from students/faculty
    

    //Reading in existing data
    ifstream inStudentfile,inFacultyFile;
    inStudentfile.open("studentTable.txt");
    inFacultyFile.open("facultyTable.txt");
    //used to see if the files existed or not and if not to create them
    if(!inStudentfile)
        cout << "**Error finding saved data for students, new file will be created to store database**\n**New database created**"<<endl;
    if(!inFacultyFile)
        cout << "**Error finding saved data for faculty members, new file will be created to store database**\n**New database created**"<<endl;
    ///reading in all serialized data`
    
    string fileInput;//used to store input from the files

    DLQueue<string> *fileQueue = new DLQueue<string>();//will store pieces of serialized data from files
    //read in student data
    while(getline(inStudentfile,fileInput))
    {
        parser -> putDataInQueue(fileInput,fileQueue);
        Student *newStud = parser -> getStudentFromDataQueue(fileQueue);
        if(newStud)//if student effectively read in, put into tree
            studentTree ->insert(newStud);
        else 
            cout << "**Error reading in student data**"<<endl;
    }
    while (getline(inFacultyFile, fileInput))
    {
        parser->putDataInQueue(fileInput, fileQueue);
        Faculty *newFac = parser->getFacultyFromDataQueue(fileQueue);
        if(newFac)// if faculty effectively read in from file, put into tree
            facultyTree ->insert(newFac);
        else 
            cout <<"**Error reading in faculty data**"<<endl;
    }
    
    delete fileQueue;//delete file queue object since it will not be used again
    //close file streams
    inStudentfile.close();
    inFacultyFile.close();
    cout <<"Welcome to the student and faculty cataloging system"<< endl;
    //stores the main menu options
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
    //variables to help with user input
    string holder;
    int inNum;
    GenStack<RollbackRecord*> *rollbackStack = new GenStack<RollbackRecord*>();
    while(true)
    {
        cout << theMenu << endl;
        cout << "----Enter new command----\nEnter '0' to display options" << endl;
        getline(cin>>ws,holder);
        if(textHelper.isPositiveInteger(holder))//checks to ensure that an option from menu is chosen
        {
            inNum = std::stoi(holder);//stores input as an int
            if (inNum == 1)//option one prints all students
            {
                cout << "-----All Students-----" << endl;
                studentTree->printToStrings();
            }
            else if (inNum == 2)//option 2 prints all faculty info
            {
                cout << "-----All Faculty-----" << endl;
                facultyTree->printToStrings();
            }
            else if (inNum == 3)//option 3 prints advisor for a given student
            {
                cout << "Please enter the id number of the student you wish to view." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures that id entered is a valid integer
                {
                    inNum = std::stoi(holder);//case string to integer
                    Student *result = searchByStudentId(inNum,studentTree);//searches the tree by id to find student
                    if (result)
                        cout << result->toString() << endl;//if found then print out the result
                    else
                        cout << "***Student with that ID was not found***" << endl;
                }
                else 
                    cout << "***Invalid input entered***"<<endl;
                
            }
            else if (inNum == 4)//option 4 prints all info of a given faculty member
            {
                cout << "Please enter the id number of the faculty member you wish to view." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures valid integer id input
                {
                    inNum = std::stoi(holder);
                    Faculty *tempResult = searchByFacultyId(inNum, facultyTree);
                    if (tempResult)//if faculty is found after searching tree print information
                        cout << tempResult->toString() << endl;
                    else
                        cout << "***Faculty member with that ID was not found***" << endl;
                }
                else 
                    cout<<"***Invalid ID entered***"<<endl;
                
            }
            else if (inNum == 5)//option 5 serves to view advisor info of a student given their id
            {
                cout << "Enter the id number of the student to view all of their advisor information" << endl;
                getline(cin>>ws,holder);
                if (textHelper.isPositiveInteger(holder))//ensures valid id input
                {
                    inNum = std::stoi(holder);
                    Student *result = searchByStudentId(inNum,studentTree);//search for given student
                    if (result)//if they exist then find their faculty advisor and print their info
                    {
                        Faculty *facResult = searchByFacultyId(result ->getAdvisorId(),facultyTree);
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
            else if (inNum == 6)//option 6 serves to see all advisees for an advisor
            {
                cout << "Enter the id of the faculty member you want to see the advisees for" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensure valid id input
                {
                    inNum = std::stoi(holder);
                    Faculty *searchFac = searchByFacultyId(inNum,facultyTree);//look for the faculty instance
                    if (searchFac)
                    {
                        if (searchFac->hasAdvisees())//if the faculty has advisees get the ids of advisees
                        {
                            int numAdvisees = searchFac->getAdviseeNumber();
                            int *theAdvisees = searchFac->returnAllAdvisees();
                            cout <<"---Advisees---"<<endl;
                            for (int i = 0; i < numAdvisees; ++i)// for all instances in the id array print their info
                            {
                                cout <<searchByStudentId(theAdvisees[i],studentTree)->toString() << endl;
                                cout << "-"<<endl;
                            }
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
            else if (inNum == 7)//option 7 allows you to create a new student instance to the database
            {
                int newId, newAdvisorId;
                double newGpa;
                string newName, newLevel, newMajor;
                cout << "---New Student Entry---" << endl;
                cout << "Enter the id number of the new student:" << endl;
                getline(cin >> ws, holder);
                if (textHelper.isPositiveInteger(holder))//ensures valid id number
                {
                    newId = std::stoi(holder);
                    if (searchByStudentId(inNum,studentTree))//checks to ensure unique id number
                        cout << "***Student with that ID number already exists, command failed***" << endl;
                    else
                    {
                        cout << "Enter the name of the student" << endl;
                        getline(cin >> ws, holder);
                        if (textHelper.isPureText(holder) && holder.size() > 0)//validates the name of the student
                        {
                            newName = holder;
                            cout << "Enter the level/year for the student" << endl;
                            getline(cin >> ws, holder);
                            if (textHelper.isPureText(holder) && holder.size() > 0)//validats the level of the student
                            {
                                newLevel = holder;
                                cout << "Enter the student's major" << endl;
                                getline(cin >> ws, holder);
                                if (textHelper.isPureText(holder))//ensures the students major is valid string
                                {
                                    newMajor = holder;
                                    cout << "Enter the GPA for the student" << endl;
                                    getline(cin >> ws, holder);
                                    if (textHelper.isNumeric(holder) && std::stod(holder) <= 4.5)//ensures that gpa is valid value
                                    {
                                        newGpa = std::stod(holder);
                                        cout << "Enter the id of the student's advisor" << endl;
                                        getline(cin >> ws, holder);
                                        if (textHelper.isPositiveInteger(holder))//ensures valid faculty id entered
                                        {
                                            newAdvisorId = std::stoi(holder);
                                            Faculty *searcher = searchByFacultyId(newAdvisorId,facultyTree);//searches for given faculty given their id
                                            if (searcher)//if the faculty member exists
                                            {
                                                //create new instance of the student and add to tree
                                                Student *tempNewStud = new Student(newId, newName, newLevel, newMajor, newGpa, newAdvisorId);
                                                studentTree->insert(tempNewStud);
                                                //add student to advisee list of specified faculty
                                                searcher->addAdvisee(tempNewStud->getId());
                                                //store rollback record in case we want to undo the addition
                                                //'d' indicates delete
                                                RollbackRecord *newRec = new RollbackRecord(true, to_string(tempNewStud->getId()), 'd');
                                                //add record to the stack
                                                rollbackStack->push(newRec);
                                                cout << "Student successfully saved to system" << endl;
                                                cout << "---New Student Profile---\n"
                                                     << tempNewStud->toString() << endl;
                                                
                                            }
                                            else
                                                cout << "***Advisor with that ID was not found, command aborted***" << endl;
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
            else if (inNum == 8)//used to delete a student given their id
            {
                cout << "Enter the id number of the student you want to delete" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures correct/valid id was entered
                {
                    inNum = std::stoi(holder);
                    Student *tempStud = searchByStudentId(inNum,studentTree);//ensures student exists
                    if (tempStud)//if student exists
                    {
                        int studId = tempStud->getId();
                        int advisorId = tempStud->getAdvisorId();
                        Faculty *found = searchByFacultyId(advisorId,facultyTree);//find instance of their advisor
                        if (found)
                        {
                            string oldInfo = tempStud ->getSerializable();//get serializable info
                            if (studentTree->deleteNode(tempStud))//remove student from tree
                            {
                                if (found->removeAdvisee(studId))//remove student from advissee list
                                    cout << "Student removed from " << found->getName() << "'s advisee list" << endl;
                                else
                                    cout << "***Error removing student from advisor's advisee list***" << endl;
                                RollbackRecord *newRecord = new RollbackRecord(true,oldInfo,'a');//add rollback record to stack to undo this delete
                                rollbackStack ->push(newRecord);
                                cout << "--Student successfully deleted--" << endl;
                            }
                        }
                        else
                            cout << "***Error in removing the student from advisor list, command aborted***" << endl;
                    }
                    else
                        cout << "***Student with that Id not found***" << endl;
                }
                else 
                    cout <<"***Invalid ID entered***"<<endl;
                
            }
            else if (inNum == 9)//create a new faculty member instance
            {
                int newId;
                string newName, newLevel, newMajor, newDepartment;
                cout << "Enter the ID number for the new faculty member" << endl;
                getline(cin >> ws, holder);
                if (textHelper.isPositiveInteger(holder))//ensure valid id number
                {
                    newId = std::stoi(holder);
                    if (!(searchByFacultyId(newId,facultyTree)))//ensure the id is not already used
                    {
                        cout << "Enter the name of the faculty member" << endl;
                        getline(cin >> ws, holder);
                        if (textHelper.isPureText(holder) && holder.size() > 0) //ensure valid name string entered
                        {
                            newName = holder;
                            cout << "Enter the new faculty member's position/title" << endl;
                            getline(cin >> ws, holder);
                            if (textHelper.isPureText(holder))//ensure that position is correctly entered
                            {
                                newLevel = holder;
                                cout << "Enter the department the faculty member is in" << endl;
                                getline(cin >> ws, holder);
                                if (textHelper.isPureText(holder))//ensures valid string is entered
                                {
                                    newDepartment = holder;
                                    //creates new faculty instance and inserts to treee
                                    Faculty *newFac = new Faculty(newId, newName, newLevel, newDepartment);
                                    facultyTree->insert(newFac);
                                    //creates new rollback record to delete later if needed
                                    RollbackRecord *newRec = new RollbackRecord(false,to_string(newFac->getId()),'d');
                                    //push rollback record to the stack
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
            else if (inNum == 10) //used to delete faculty member based on their id
            {
                cout << "Enter the id number of the faculty member you wish to delete" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures correct id entered
                {
                    inNum = std::stoi(holder);
                    //finds the faculty to be deleted
                    Faculty *tempFac = searchByFacultyId(inNum,facultyTree), *replacement;
                    Student *temp;
                    bool success = true;
                    if (tempFac)//if faculty member found
                    {
                        int adviseeCount = tempFac->getAdviseeNumber();//gets how many advisees they ahve
                        int *adviseeArray;
                        if (adviseeCount > 0)//if the faculty has advisees
                        {
                            adviseeArray = tempFac->returnAllAdvisees();//get all advisee ids
                            for (int i = 0; i < adviseeCount; ++i)//iterate over all advisees
                            {
                                temp = searchByStudentId(adviseeArray[i],studentTree);
                                //assign each student a new advisor other than their current advisor
                                replacement = facultyTree->getEntryOtherThan(tempFac);
                                if (replacement)//if replacement found
                                {
                                    //add advisee to advisor list and set advisor id for student
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
                                cout << "*Advisees re-assigned to next available faculty member*" << endl;
                        }
                        if (success)//if students  effectively reallocated to new advisor 
                        {
                            string facInfo = tempFac ->getSerializable();//get faculty csv data
                            Faculty *searcher = new Faculty(inNum);
                            if (facultyTree->deleteNode(searcher))//delete the specified faculty
                            {
                                //push new rollback record in case we wish to under
                                //WILL NOT REASSIGN ADVISEES PREVIOUSLY HELD
                                RollbackRecord *afterInfo = new RollbackRecord(false,facInfo,'a');
                                rollbackStack ->push(afterInfo);
                                cout << "--Faculty member effectively deleted--" << endl;
                            }
                            else
                                cout << "***Error deleting faculty member***" << endl;
                            delete searcher;
                        }
                        else
                            cout << "***Unable to delete faculty member***" << endl;
                    }
                    else
                        cout << "***Faculty member with that ID number not found***" << endl;
                }
                else 
                    cout << "***Invalid ID entered***"<<endl;                
            }
            else if (inNum == 11)//used to change the advisor for a student
            {
                cout << "Enter the id number of the student you wish to edit." << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures avlid id is entered
                {
                    inNum = std::stoi(holder);
                    Student *studentToEdit = searchByStudentId(inNum,studentTree);//finds student by id
                    if (studentToEdit)//if student found
                    {
                        cout << "Enter the id number of the new advisor for the student" << endl;
                        getline(cin>>ws,holder);
                        if(textHelper.isPositiveInteger(holder))//ensure that new advisor id is valid
                        {
                            inNum = std::stoi(holder);
                            Faculty *result = searchByFacultyId(inNum,facultyTree);//find faculty by id
                            if (result)//if faculty exists
                            {
                                //resassign student to new advisor and add them to advisee list
                                int previousAdvisorId = studentToEdit->getAdvisorId();
                                studentToEdit->setAdvisorId(result->getId());
                                result->addAdvisee(studentToEdit->getId());
                                //remove the student from the previously allocated advisor
                                searchByFacultyId(previousAdvisorId,facultyTree)->removeAdvisee(studentToEdit->getId());
                                cout << "-Student advisor id sucessfully updated-" << endl;
                                cout << "--Updated entry--" << endl;
                                cout << studentToEdit->toString() << endl;
                            }
                            else
                                cout << "***Faculty with that id number does not exist***" << endl;
                        }
                        else
                            cout << "***Invalid ID entered***"<<endl;
                    }
                    else
                        cout << "***Student with that ID not found***" << endl;
                }
                else 
                    cout << "***Invalid ID entered***"<<endl;                
            }
            else if (inNum == 12)//used to remove an advisee from an advisor
            {
                cout << "Enter the ID number of the advisor you wish to edit" << endl;
                getline(cin>>ws,holder);
                if(textHelper.isPositiveInteger(holder))//ensures valid id entered
                {
                    inNum = std::stoi(holder);
                    Faculty *facToEdit = searchByFacultyId(inNum,facultyTree);//searches for faculty member
                    if (facToEdit)//if faculty member exists
                    {
                        cout << "Enter the id number of the student you wish to remove from the faculty's advisee list" << endl;
                        getline(cin>>ws,holder);
                        if(textHelper.isPositiveInteger(holder))//ensures valid student id entered
                        {
                            inNum = std::stoi(holder);
                            Student *result = searchByStudentId(inNum,studentTree);//serach for student
                            if (result) //student exists
                            {
                                bool answer = facToEdit->removeAdvisee(result->getId());//remove student from list
                                if (answer)
                                {
                                    Faculty *tempFac = facultyTree->getEntryOtherThan(facToEdit);//gets replacement for student advisor
                                    if (tempFac)
                                    {
                                        //set new advisor for student and add student to the advisor's list
                                        result->setAdvisorId(tempFac->getId());
                                        tempFac->addAdvisee(result->getId());
                                        cout << "--Advisee successfully removed from list and reassigned to next available faculty--" << endl;
                                        cout << "---New assigned advisor--- \n"
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
                        }  
                        else 
                            cout << "***Invalid ID entered***"<<endl;                      
                    }
                    else
                        cout << "***Faculty member with that ID number not found***" << endl;
                }
                else 
                    cout <<"***Invalid Id entered***"<<endl;                
            }
            else if (inNum == 13)//undo the most recent augmentation to either tree IN CURRENT SESSION
            {
                //gets the most recent action
                if(!rollbackStack ->isEmpty())// if there is something to undo in current session
                {
                    RollbackRecord *lastAction = rollbackStack->pop();
                    ///if the last alteration concerns a student record
                    DLQueue<string> *helperQueue = new DLQueue<string>();
                    string serialized = lastAction->data;//gets serialized data from most recent record
                    parser->putDataInQueue(serialized, helperQueue);//puts all data into a queue
                    if (lastAction->action == 'a')//if undoing is involves adding an instance
                    {
                        if (lastAction->isStudent == true)//if action involves a student
                        {
                            Student *redo = parser->getStudentFromDataQueue(helperQueue);//creates new student instance
                            if (redo)
                            {
                                studentTree->insert(redo);//re inserts to tree
                                //re adds student to previous adivsors advisee list
                                Faculty *priorAdvisor = searchByFacultyId(redo->getAdvisorId(),facultyTree);
                                priorAdvisor->addAdvisee(redo->getId());
                                cout << "--Student successfully readded to the database--" << endl;
                            }
                            else
                                cout << "**Error attempting to undo student deletion**" << endl;
                        }
                        else
                        {
                            //same funcitonality for faculty to be readded but does not reassign students to their list
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
                    else if (lastAction->action == 'd')//if undoing involves deleting an instance
                    {
                        if (lastAction->isStudent == true)//if action involves a student
                        {
                            int redoId = std::stoi(lastAction ->data);//only needs id that was stored
                            if (redoId)
                            {
                                //find student and their advisor
                                Student *found = searchByStudentId(redoId,studentTree);
                                Faculty *priorAdvisor = searchByFacultyId(found->getAdvisorId(),facultyTree);
                                //removes student from their advisee list and deletes student 
                                priorAdvisor->removeAdvisee(redoId);
                                studentTree->deleteNode(found);  
                                cout << "--Student successfully un-added to the database--" << endl;
                            }
                            else
                                cout << "**Error attempting to undo student addition**" << endl;
                        }
                        else//if the record concerns a faculty member
                        {
                            //finds the faculty member by the id stored in the rollback record
                            Faculty *found = searchByFacultyId(std::stoi(lastAction->data),facultyTree);
                            if (found)
                            {
                                //get all their advisees
                                int numAdvisees = found ->getAdviseeNumber();
                                if(numAdvisees >0)//if the faculty to be deleted has advisees
                                {
                                    int *advisees = found->returnAllAdvisees();
                                    Student *temp;
                                    //new advisor for all advisees
                                    Faculty *replacement = facultyTree->getEntryOtherThan(found);
                                    //reallocates all students to a new advisor since we will delete theirs
                                    if (replacement)
                                    {
                                        for (int i = 0; i < numAdvisees; ++i)
                                        {
                                            temp = searchByStudentId(advisees[i], studentTree);
                                            if (replacement)
                                            {
                                                temp->setAdvisorId(replacement->getId());
                                                replacement->addAdvisee(temp->getId());
                                                found->removeAdvisee(advisees[i]);
                                            }
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
                                {
                                    facultyTree->deleteNode(found);
                                    cout << "--Faculty member un-added to the database--"<<endl;
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
            else if (inNum == 14)//stops the program and saves all data
            {
                //open files to write to to serialize data
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
                    //writes all instances stored in both trees then closes the streams
                    facultyTree->write(facultyFile);
                    studentTree->write(studentFile);
                    facultyFile.close();
                    studentFile.close();
                    cout << "Program closed and data saved." << endl;
                    break;
                }
            
                
               
            }
        }        
        else //used if no valid commands entered
            cout << "*Invalid command entered*"<<endl;
    }

    
    delete rollbackStack;
    delete facultyTree;
    delete studentTree;
    delete parser;
    return 0;
}


//seraches by id by creating a dummy instance to simply store id in instance of student
Student* searchByStudentId(int i,ExtendedTree<Student*> *tree)
{
    Student *searcher = new Student(i);
    Student *returner = tree ->search(searcher);
    delete searcher;
    return returner;

}
//seraches by id by creating a dummy instance to simply store id in instance of faculty

Faculty* searchByFacultyId(int i, ExtendedTree<Faculty*> *tree)
{
    Faculty *searcher = new Faculty(i);
    Faculty *returner = tree->search(searcher);
    delete searcher;
    return returner;
}