/* operators within c++ are used as short-hand to signify logic of comparison. Consider the following bitwise opreators: 
&& - and
|| - or
! - not
!= not equal
& - bitwise and
| - bitwise or
^ - bitwise XOR
&= - and equal
|= or equal
^= XOR equal
*/
#include<iostream>

int main(){
    bool t = true;
    bool f = false;
    printf("true: %d\n", t);
    printf("false: %d\n",f);
    printf("not true: %d\n", !t);
    printf("not false: %d\n", !f);
    printf("true && false: %d\n", t && f);
    printf("true or false: %d\n", t || f);
    printf("true && not false: %d\n", t && !f);
    printf("not true && false: %d\n", !t && f);
    printf("Not true and not false: %d\n", !t && !f);
    printf("false or false: %d\n", f || f);

}