/*
The goal of the header file is to declare functions or variables that are globally established and
can be accessed by any operations within the program.Consider that while a .cpp file is the implementation
of the code logic, the header file are to declared existence of variable of functions and variables. Headers files will prevent 
double inclusion within the code. In other words this rhetoric of code will reduce the code collison of name conflict within
other header files, for the compiler will not know which function of the same name that the programmer is trying to
call. To create a header, create a file name with the desired name with ".h" extension. Within the file,
input: #ifndf UNTITLED2_VERSION_H
       #DEFINE UNTITLED2_VERSION_H ~~ the name of the file is up to the programmer of course.
It is important that all header files ends in a #endif

*/

#ifndef HEADER_H
#define HEADER_H
#include<string>
extern std::string g_header; /*
The declaration of a translation unit allow this variable declared as extern, tells the compilere that
the definition of this code exists or in another scenario, this exists somewhere else within the program's
file structure. It allows other files to always call this variable defintion. In other words, there is an
external linkages if this header file is included with other .cpp file and the variable header is called.
*/
class Header{};

#endif