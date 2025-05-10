/*
Bool within c++ is a state in which the declaration or result is either true of false, if it is false.
Consider that the convention of a boolean in binary is represented as 1 (true) and 0(false), 
*/
#include<iostream>
int main(){
    constexpr bool b1 = true;
    constexpr bool b2 = false;
    printf("%d %d\n",b1,b2);
    printf("7 == 7: %d\n", 7 == 7); 
    printf("7 != 7 %d\n:", 7 != 7);
    printf("10 >= 20 %d\n:", 10 >= 20);
    printf("10 < 20 %d\n:", 10 < 20);


}