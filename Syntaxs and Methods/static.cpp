/*
Static values remains constant through the program, and even when shared across funcitons.
If the static values has no declaration, the value will be defaulted to 0.
*/
#include<iostream>

int inc (int i){
    static int value; 
    value += i;
    return value;
}
int main(){
    printf("increment %d \n", inc(5));
    printf("increment %d \n", inc(9));
    printf("increment %d \n", inc(19));
    printf("increment %d \n", inc(999));
    printf("increment %d \n", inc(1000));
    return 0;
}