#include "final.h"
#include "customErrorClass.h"
#include <exception>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]){

    C_EmployeeRecord myRecord;

    fstream inputBinary;
    fstream sortedBinary;

    int entryByte = 38, fileSize = 0;
    int choice = 1, deptNo, offset, rangeStart, rangeEnd;
    recordStruct* rec;
    recordStruct temp;
    int indexArray[5];
    char newName[30];
    char fileStr[25];
    MyException excp("ERROR!!");
    

    if (argc != 2)
    {
        cout<<"ERROR!!"<<endl;
        cout<<"Usage: ./a.out fileName"<<endl;
        exit(0);
    }

    //check if file exists
    struct stat buf;
    bool fileExists = stat(argv[1], &buf) == 0;

    if (!fileExists)
         cout<<"File does not exist!"<<endl;

    //get the file size
    inputBinary.open(argv[1], ios::in|ios::binary);
    inputBinary.seekg(0, ios::end);
    fileSize = inputBinary.tellg()/entryByte;

    rec = new recordStruct[fileSize];

    inputBinary.seekg(ios::beg);  

    //Reading a binary file into a struct array
    
    for (int i = 0; i < fileSize; ++i)
    {
        inputBinary.read((char*)&rec[i], sizeof(recordStruct));
       
        inputBinary.seekg(ios::beg+(entryByte * (i+1) ));
    }

    inputBinary.close();


    //Sorting the struct array
    //myRecord.quickSort(rec, 0, fileSize-1);
    myRecord.sort(rec, fileSize-1);

    //Writing sorted file to a new binary file
    string str1 = "Sorted_", str2 = argv[1];
    string str = str1+str2;
    strcpy(fileStr, str.c_str());

    sortedBinary.open(str, ios::out|ios::binary);
    
    for (int i = 0; i < fileSize; ++i)
    {
        sortedBinary.write((char*)&rec[i], sizeof(recordStruct));
        sortedBinary.seekg(ios::beg+(entryByte * (i+1) ));
    }

    sortedBinary.close();

    //Indexing a file
    myRecord.index(rec, indexArray);


//Find the size in each department
int size0, size1, size2, size3, size4;
size0 = indexArray[1];
size1 = indexArray[2] - indexArray[1];
size2 = indexArray[3] - indexArray[2];
size3 = indexArray[4] - indexArray[3];
size4 = (fileSize-1) - indexArray[4];


//-----printing some outputs---------

    //printing the 53rd employee from each department
    cout<<"-----------Printing the 53rd employee from each department"<<endl;
    myRecord.displayName(indexArray[0], 53, fileStr);
    myRecord.displayName(indexArray[1], 53, fileStr);
    myRecord.displayName(indexArray[2], 53, fileStr);
    myRecord.displayName(indexArray[3], 53, fileStr);
    myRecord.displayName(indexArray[4], 53, fileStr);
cout<<endl;
    //printing the 102nd employee from each department
    cout<<"-----------Printing the 102nd employee from each department"<<endl;
    myRecord.displayName(indexArray[0], 102, fileStr);
    myRecord.displayName(indexArray[1], 102, fileStr);
    myRecord.displayName(indexArray[2], 102, fileStr);
    myRecord.displayName(indexArray[3], 102, fileStr);
    myRecord.displayName(indexArray[4], 102, fileStr);
cout<<endl;
        //printing each record with the name updated to "Carol"
        cout<<"----------------------Printing each record with the name updated to 'Carol'"<<endl;
        char newName1[30] = "Carol";
        myRecord.updateName(indexArray[0], 102, newName1, fileStr);
        myRecord.updateName(indexArray[1], 102, newName1, fileStr);
        myRecord.updateName(indexArray[2], 102, newName1, fileStr);
        myRecord.updateName(indexArray[3], 102, newName1, fileStr);
        myRecord.updateName(indexArray[4], 102, newName1, fileStr);

        myRecord.displayName(indexArray[0], 102, fileStr);
        myRecord.displayName(indexArray[1], 102, fileStr);
        myRecord.displayName(indexArray[2], 102, fileStr);
        myRecord.displayName(indexArray[3], 102, fileStr);
        myRecord.displayName(indexArray[4], 102, fileStr);

cout<<endl;    
    //printing the 13th employee from each department
    cout<<"-----------Printing the 13th employee from each department"<<endl;
    myRecord.displayName(indexArray[0], 13, fileStr);
    myRecord.displayName(indexArray[1], 13, fileStr);
    myRecord.displayName(indexArray[2], 13, fileStr);
    myRecord.displayName(indexArray[3], 13, fileStr);
    myRecord.displayName(indexArray[4], 13, fileStr);
cout<<endl;
        //printing after deletion
        cout<<"----------------------Printing after deletion"<<endl;
        myRecord.deleteRecord(indexArray[0], 13, fileStr);
        myRecord.deleteRecord(indexArray[1], 13, fileStr);
        myRecord.deleteRecord(indexArray[2], 13, fileStr);
        myRecord.deleteRecord(indexArray[3], 13, fileStr);
        myRecord.deleteRecord(indexArray[4], 13, fileStr);

        myRecord.displayName(indexArray[0], 13, fileStr);
        myRecord.displayName(indexArray[1], 13, fileStr);
        myRecord.displayName(indexArray[2], 13, fileStr);
        myRecord.displayName(indexArray[3], 13, fileStr);
        myRecord.displayName(indexArray[4], 13, fileStr);
cout<<endl;
    //printing the last 20 records from each department
    cout<<"-----------Printing the last 20 records from each department"<<endl;
    myRecord.printRange(indexArray[0], size0-20, size0-1, fileStr);
    cout<<endl;
    myRecord.printRange(indexArray[1], size1-20, size1-1, fileStr);
    cout<<endl;
    myRecord.printRange(indexArray[2], size2-20, size2-1, fileStr);
    cout<<endl;
    myRecord.printRange(indexArray[3], size3-20, size3-1, fileStr);
    cout<<endl;
    myRecord.printRange(indexArray[4], size4-20, size4-1, fileStr);
//-----------------------------------
cout<<endl<<endl;

try{

    while(choice != 0)
    {
        //Display choice options
        cout<<endl<<endl;
        cout<<"---------------- Please choose from 1 - 4 for Employee Records ---------------- "<<endl;
        cout<<"1: Print Employee Name"<<endl;
        cout<<"2. Update Employee Name"<<endl;
        cout<<"3. Delete Employee Record"<<endl;
        cout<<"4. Print certain range of Employees"<<endl;
        cout<<"0. Exit"<<endl;

        cin>>choice;

      if(choice == 1|| choice == 2 | choice == 3)
      {
        cout<<"Accounting dept(0) offset range is: 0-"<<size0-1<<endl;
        cout<<"Business dept(1) offset range is: 0-"<<size1-1<<endl;
        cout<<"Human Resources dept(2) offset range is: 0-"<<size2-1<<endl;
        cout<<"Sales dept(3) offset range is: 0-"<<size3-1<<endl;
        cout<<"Production dept(4) offset range is: 0-"<<size4-1<<endl<<endl<<endl;

        cout<<"Enter Employee's department number (0, 1, 2, 3 or 4): ";
        cin>>deptNo;

            if(deptNo >=0 &&  deptNo <= 4)
            {
                if(deptNo == 0)
                {
                    cout<<"Enter the offset: ";
                    cin>>offset;
                    if(offset < 0 || offset > size0-1)
                        throw MyException("ERROR: Invalid offset");

                } else if(deptNo == 1){
                    cout<<"Enter the offset: ";
                    cin>>offset;
                    if(offset < 0 || offset > size1-1)
                        throw MyException("ERROR: Invalid offset");

                }else if(deptNo == 2){
                    cout<<"Enter the offset: ";
                    cin>>offset;
                    if(offset < 0 || offset > size2-1)
                        throw MyException("ERROR: Invalid offset");

                }else if(deptNo == 3){
                    cout<<"Enter the offset: ";
                    cin>>offset;
                    if(offset < 0 || offset > size3-1)
                        throw MyException("ERROR: Invalid offset");

                }else{
                    cout<<"Enter the offset: ";
                    cin>>offset;
                    if(offset < 0 || offset > size4-1)
                        throw MyException("ERROR: Invalid offset");
                }

            } else{
                cout<<"ERROR: Invalid department number"<<endl;
                throw MyException("Error: Invalid dept No!");
            }
      }
      if(choice == 4)
      {
        cout<<"Accounting dept(0) offset range is: 0-"<<size0-1<<endl;
        cout<<"Business dept(1) offset range is: 0-"<<size1-1<<endl;
        cout<<"Human Resources dept(2) offset range is: 0-"<<size2-1<<endl;
        cout<<"Sales dept(3) offset range is: 0-"<<size3-1<<endl;
        cout<<"Production dept(4) offset range is: 0-"<<size4-1<<endl<<endl<<endl;

        cout<<"Enter Employee's department number (0, 1, 2, 3 or 4): ";
        cin>>deptNo;

        if(deptNo >= 0 && deptNo <= 4)
        {
            cout<<"Enter the start of range: ";
            cin>>rangeStart;
            cout<<"Enter the end of range: ";
            cin>>rangeEnd;
            while (rangeStart < 0 || rangeEnd > size4-1) 
            {
                cout<<"Please re-enter a valid range"<<endl;
                cout<<"Enter the start of range: ";
                cin>>rangeStart;
                cout<<"Enter the end of range: ";
                cin>>rangeEnd;
            }
        }else{
            cout<<"ERROR: Invalid department number"<<endl;
            throw MyException("Error: Invalid dept No!");
        }
        
      }
    
        //options to choose from
        switch(choice)
        {
            case 1: 
                myRecord.displayName(indexArray[deptNo], offset, fileStr);
                break;
            case 2:
                cout<<"Enter a 30 char name to update record: ";
                cin>>newName;
                myRecord.updateName(indexArray[deptNo], offset, newName, fileStr);
                break;
            case 3:
                myRecord.deleteRecord(indexArray[deptNo], offset, fileStr);
                break;
            case 4:
                myRecord.printRange(indexArray[deptNo], rangeStart, rangeEnd, fileStr);
                break;
            case 0: 
                return 0;
                break;
            default:
                cout<<"Invalid choice!"<<endl;

        };

    }

}catch(MyException &e){
    cout<<e.what()<<endl;
}catch(exception &e){
    cout<<e.what()<<endl;
}
    return 0;
}