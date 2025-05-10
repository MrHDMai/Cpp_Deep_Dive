#include<iostream>
#include "header.h"
#include"main.h"

// header = 1; if this global variable is created here, it will invoke an error since the header
//file already has this variable defined; however, within the scope of the main function, the version
//can be reassigned
//if wish to compiled the program via vscode - employ the command to compile by linking all the neccessary files:
//g++ main.cpp headerPrint.cpp -o main.exe -std=c++11
//./main
std::string objective = "Header file implementation from main file";// declared at the file scope

void print_header(){
    printf("header = %s\n", ::g_header.c_str()/*Consider that :: (scope resolution operator) before the variable refers to the header file*/);
}

void usage(){
    std::cout << objective << " ";
    print_header();
}

int main(){
    usage();
    return 0;
}
