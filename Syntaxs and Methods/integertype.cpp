/*
Consider that there are a few tpye of integers
short int - 2 byte
unsigned short int - 2 bytes
int - 4byte
unsigned int - 4 byte
long int - 4 byte
unsigned long int - 4 byte
long long int - 8 byte
unsigned long long int - 8 byte

when coding consider these syntax conventions for printing base integer conversion: 
Binary - prefix 0b
Octal - prefix 0
decimal - Default
headecimal - use prefix 0

Floating point numbers
----------------------
These numbers are considered to be approximation number, in other words, these numbers are
of decimals and arbitary numbers that has hundredth of thousandth place decimal point. The more a percison a point has
the more precise the calculation is within C++. Consider that the language allows for multiple level of floating points
foat - single precision(4 byte), double - double percision(8 bytes), and long double has extended precision(8 bytes)

floating point literals
-----------------------
Consider that these declaration are double by default.
float a = 0.1F
double b = 0.2;
long double c = 0.3L;

char type
---------------------
This type is also represented by 1 byte signed or unsigned. However it can be modified by declaration method consider:
Programmer can leverage the ASCII system to further specify the number of byte in memory that the data type can holdd.
char16_t - 2 byte - use u
chat32_t - 4 byte specified when implementing by using uppercase U
siggned and  unsiged may also be leverage when creating char character type. - specified by ''
wchar_t - declaring for the compiler to know that the data type will require the largest char storage, UNICODE.abort
narrow chars are considered to be char, signed char, and unsigned char variable types
wides chars are categorized as char_16, char_32 and wchar_t
*/

#include<stdio.h>
#include<iostream>

int main(){
    unsigned short a = 0b10101010; //binary
    printf("%hu\n",a);

    int b = 0123;//octal decimal
    printf("%d\n",b);

    unsigned long long c = 0xFFFFFFFFFF; //hexadecimal
    printf("%llu\n",c);
    /*----------Floating Point Literals------------*/
    float d = 0.1F;
    double e = 0.2;
    long double f = 0.3L;
    long double g = 109.756372e-19L;
    //consider that when dealing with decimal digits
    //programmers may leverage the printf function to format the output for float or double 
    //%lf %le %lg
    //On the other hand if the variable is of long double leverage %Lf %Le or %Lg
    printf("%lf \n", d);//for flat
    printf("%le \n", e);
    printf("%.35Lf \n", g);//for long double consider using Lf we can prefix the format input by specify it to print 35 siign floating number
    
    //print avogadro number
    double avcnum = 6.0221409e23;
    printf("Avogadro number is: %le %lf %lg\n",avcnum, avcnum, avcnum);
    //printing the nunmber with float
    float num = 45.2356;
    printf("Print of float number: %le %lf %lg: ", num, num, num);

    /*Chars inmplementation
    tab \t
    tab verticl \v
    backspace is \b
    carriage return is \r
    fom feed is \f
    alert \a 
    backlash is \\
    single quote is \' 
    double quote \*
    the null char is \0
    
    A CHAR = '\u0041'
    */
   char x = 'M';
   wchar_t y = L'Z';
   printf("Print char character: %c%lc \n", x,y);

}