#include "final.h"
#include "customErrorClass.h"
#include <fstream>
#include <string.h>
#include <exception>

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Initializes variable for the EmployeeRecord class
**    Return Value: None
**    Side Effects: None
*/
C_EmployeeRecord::C_EmployeeRecord()
{
    this->fileSize = 0;
    this->entryByte = 38;
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Destructor of the EmployeeRecord class
**    Return Value: None
**    Side Effects: None
*/
C_EmployeeRecord::~C_EmployeeRecord()
{
    cout<<"Destructing..."<<endl;
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_timSort function if the file is not empty
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::sort(recordStruct array[], int fileSize)
{
    if (fileSize != 0)
        this->p_timSort(array, fileSize);
    else
        throw MyException("ERROR: Empty file to sort!");
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_index function 
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::index(recordStruct array[], int indexArray[])
{
    this->p_index(array, indexArray);
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Searches for a single record in a binary file and returns its status
**    Return Value: bool
**    Side Effects: None
*/
bool C_EmployeeRecord::searchRecord(int dept, int offset, char* fileStr)
{
    fstream binaryFile;
    recordStruct rec;

    string str(fileStr);

    binaryFile.open(str, ios::in|ios::binary);
    binaryFile.seekg(ios::beg + (dept*38) + (offset*38));

    binaryFile.read((char*)&rec, sizeof(recordStruct));

    if(rec.dept == -1){
        return false;
    }
    else{
        return true;
    }

}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_displayName function if the record exists using the searchRecord function
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::displayName(int dept, int offset, char* fileStr)
{
    bool checkRecord;

    checkRecord = this->searchRecord(dept, offset, fileStr);

    if(checkRecord){
        this->p_displayName(dept, offset, fileStr);
    }else{
        cout<<"MSG: Employee Record doesn't exist! Can't display name."<<endl;
    }
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_updateName function and displays if record doesn't exist
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::updateName(int dept, int offset, char* newName, char* fileStr)
{
    bool checkRecord;
    checkRecord = this->searchRecord(dept, offset, fileStr);

    if(checkRecord){
        this->p_updateName(dept, offset, newName, fileStr);
    }else{
        cout<<"MSG: Employee Record to be updated doesn't exist!"<<endl;
        this->p_updateName(dept, offset, newName, fileStr);
    }
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_deleteRecord function is the record exists using the searchRecord function
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::deleteRecord(int dept, int offset, char* fileStr)
{

    bool checkRecord;
    checkRecord = this->searchRecord(dept, offset, fileStr);

    if(checkRecord){
        this->p_deleteRecord(dept, offset, fileStr);
    }else{
        cout<<"MSG: Employee Record doesn't exist! Nothing to delete."<<endl;
    }
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Calls the p_printRange function for valid parameter values
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::printRange(int dept, int startIndex, int endIndex, char* fileStr)
{
    if(startIndex >= endIndex)
        throw MyException("ERROR: start index is larger than end index!");
    else
        this->p_printRange(dept, startIndex, endIndex, fileStr);
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ PRIVATE  FUNCTIONS ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Sorts a large array by using p_insertionSort for subarrays and merging by calling p_merge
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_timSort(recordStruct array[], int fileSize)
{
    int RUN = 32;
    for (int i = 0; i < fileSize; i+=RUN)   
        this->p_insertionSort(array, i, min((i+RUN-1),(fileSize-1)));
    for (int size = RUN; size < fileSize; size = 2*size)
    {
        for (int left = 0; left < fileSize; left += 2*size)
        {
            int mid = left + size - 1;
            int right = min((left + 2*size - 1),
                                            (fileSize-1));
 
              if(mid < right)
                this->p_merge(array, left, mid, right);
        }
    }

}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Sorts a struct array using insertion sort algorithm
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_insertionSort(recordStruct array[], int beg, int end)
{
    for (int i = beg + 1; i <= end; i++)
    {
		recordStruct temp;
		temp = array[i];
        int j = i - 1;
        while (j >= beg && array[j].dept > temp.dept)
        {
            array[j+1] = array[j];
            j--;
        }
		array[j+1]=temp;
    }
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Merges struct arrays
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_merge(recordStruct array[], int beg, int mid, int end)
{
    int len1 = mid - beg + 1, len2 = end - mid;
	int *left= new int[len1];
	int *right= new int[len2];
	
    for (int i = 0; i < len1; i++){
        left[i] = array[beg + i].dept;
	}
    for (int i = 0; i < len2; i++){
        right[i] = array[mid + 1 + i].dept;
	}
 
    int i = 0;
    int j = 0;
    int k = beg;

    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            array[k].dept = left[i];
            i++;
        }
        else
        {
            array[k].dept = right[j];
            j++;
        }
        k++;
    }
    while (i < len1)
    {
		array[k].dept = left[i];
        k++;
        i++;
    }
    while (j < len2)
    {
        array[k].dept = right[j];
        k++;
        j++;
    }

}


/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Creates index values based on sorted department numbers
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_index(recordStruct array[], int indexArray[])
{
    indexArray[0] = 0;
    int changeLoc = 1;
    for (int j = 1; j < 5; j++)
    {
        int swap = 0, index = 0;
        do{
            if(array[index].dept == changeLoc){
                swap = 2;
            }else{
                index++;
            }
        }while(swap == 0);
        indexArray[j] = index;
        changeLoc += 1;
    }
}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Prints the record of a given department and offset location
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_displayName(int dept, int offset, char* fileStr)
{
    fstream binaryFile;
    recordStruct rec;
    string department;

    string str(fileStr);

    binaryFile.open(str, ios::in|ios::binary);
    binaryFile.seekg(ios::beg + (dept*38) + (offset*38));

    binaryFile.read((char*)&rec, sizeof(recordStruct));
    if(rec.dept == 0){
        department = "Accounting";
    }else if(rec.dept == 1){
        department = "Business";
    }else if(rec.dept == 2){
        department = "Human Resources";
    }else if(rec.dept == 3){
        department = "Sales";
    }else{
        department = "Production";
    }
    cout<<"Dept: "<<rec.dept<<" ID: "<<rec.ID<<" Name: "<<rec.name<<endl;

    binaryFile.close();

}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Updates a record's name of a given department and offset location
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_updateName(int dept, int offset, char* newName, char* fileStr)
{
    fstream binaryFile;

    string str(fileStr);

    binaryFile.open(str, ios::out|ios::binary|ios::in);
    binaryFile.seekg(ios::beg + (dept*38) + (offset*38) + 8);

    binaryFile.write(&*newName, sizeof(char[30]));

    binaryFile.close();

}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Deletes a record of a given department and offset location
**    Return Value: None
**    Side Effects: None
*/
void C_EmployeeRecord::p_deleteRecord(int dept, int offset, char* fileStr)
{
    fstream binaryFile;
    int emptyNum = -1;
    char emptyChar = '\0';

    string str(fileStr);

    binaryFile.open(str, ios::out|ios::binary|ios::in);
    binaryFile.seekg(ios::beg + (dept*38) + (offset*38));

    binaryFile.write((char*)&emptyNum, sizeof(emptyNum));
    binaryFile.write((char*)&emptyNum, sizeof(emptyNum));
    binaryFile.write((char*)&emptyChar, sizeof(emptyChar));

    binaryFile.close();

}

/*
**    Author: Christina Mulu
**    Function Purpose: 
**        Prints a range of employee records given a department, start and end offset location
**    Return Value: 
**    Side Effects: 
*/
void C_EmployeeRecord::p_printRange(int dept, int startIndex, int endIndex, char* fileStr)
{
    fstream binaryFile;
    recordStruct rec;

    string str(fileStr);

    binaryFile.open(str, ios::out|ios::binary|ios::in);
    
    for(int i = startIndex; i <= endIndex; i++)
    {
        binaryFile.seekg(ios::beg + (dept*38) + (i*38) );
        binaryFile.read((char*)&rec, sizeof(recordStruct));
        cout<<"Dept: "<<rec.dept<<" ID: "<<rec.ID<<" Name: "<<rec.name<<endl;
    }

    binaryFile.close();
}
