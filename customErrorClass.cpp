#include <iostream>
#include "customErrorClass.h"

using namespace std;


/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(void){
    this->errString = "Error: Something went wrong.";
}

/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(const string &err){
    this->errString = err;
}

/**************************** PUBLIC: Constructor ****************************/
MyException::MyException(const char *err){
    this->errString = err;
}

/**************************** PUBLIC: retrieveError ****************************/
string MyException::retrieveError(void){
    this->errString = "\033[1;31m" + this->errString + "\033[0m";

    return this->errString;
}