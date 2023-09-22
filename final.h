#ifndef __FINAL_PROJECT__
#define __FINAL_PROJECT__

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

struct recordStruct
{
    int dept;
    int ID;
    char name[30];
};

class C_EmployeeRecord{
    public:

        C_EmployeeRecord();  
        ~C_EmployeeRecord(); 

        void sort(recordStruct array[], int fileSize);
        
        void index(recordStruct array[], int indexArray[]);

        void displayName(int dept, int offset, char* fileStr);

        bool searchRecord(int dept, int offset, char* fileStr);
        
        void updateName(int dept, int offset, char* newName, char* fileStr);
        void deleteRecord(int dept, int offset, char* fileStr);
        void printRange(int dept, int startIndex, int endIndex, char* fileStr);

        int fileSize;
        int entryByte;

    private:

        void p_timSort(recordStruct array[], int fileSize);

        void p_insertionSort(recordStruct array[], int beg, int end);
        void p_merge(recordStruct array[], int beg, int mid, int end);
        
    
        void p_index(recordStruct array[], int indexArray[]);

        void p_displayName(int dept, int offset, char* fileStr);
        void p_updateName(int dept, int offset, char* newName, char* fileStr);
        void p_deleteRecord(int dept, int offset, char* fileStr);
        void p_printRange(int dept, int startIndex, int endIndex, char* fileStr);

        

};

#endif