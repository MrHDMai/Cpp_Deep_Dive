/* Consider that within the loop, it is initialized as (initialilzation, the condition, and the iteration)
once those basis are establilshed the initial value will check the condition and perform the specified iteration
*/
#include<iostream>

using namespace std;

int main(){
    for(int i = 0; i <= 100; i++){
        cout << "Value of i is: " << i << endl;
    }
    //lets make an infinite loop and break the loop after the 1000th iteration
    for(int i = 0; ;i++){
        cout << "Iteration i is: " << i << endl;
        if(i == 1000){
            break;
        }
    }
    //loop manipulation with continue
    for(int i = -10; i < 10; i++){
        if(i == 0){
            continue;// studying the output since we specified that if i is equal to 0, it will then skip 0 and continue with the loop
        }
        cout << "The iteration frorm negative to positive is: " << i << endl;
    }
    return 0;
}