#include<iostream>

/*
More on namespace - this section is an extension on namespace and how to nest namespace function
for a more robust and clean code structure. This will decrease verboseness of the code and address
naming convention by declaring the scope of each function
*/

namespace domathfunction{ // main namespace function
    inline namespace v1 {
        int numManipulate(int x){
        return x * x;
    }
    }
    int divNum(int x, int y){
        if(y == 0){
            std::cerr << "Error: Division by 0";
            return 0;
        }
        return x/y;
    }

    inline namespace v2{
        int numManipulate(int x){
            return x * x * x;
        }
    }

    namespace util{ // nested namespace to establish a function of the same name with different operation
        int numManipulate(int x,int y){
            return (x * x)/y;
        }
    }
}

using namespace domathfunction;
int main(){
    int n = 5;
    //we can change the scope from v1 to v2, depending on which inline function we want to call. This will
    //allow the programmer to be able to keep the same code structure and implement new functionality to
    //creating different version of the implementation.
    int sqr =  domathfunction::v2::numManipulate(n); // call the numManipulate of the main namespace
    std::cout << "Square of " << n << " is :" << sqr << std::endl;

    int x = 10, y = 2;
    int result = domathfunction::util::numManipulate(x,y); //call the nested namespace function
    std:: cout << "x^2/y is: " << result << std::endl;

    int quotient = domathfunction::divNum(x,y); // calling the division operation
    std::cout<<"Division is : " << quotient << std::endl;

    domathfunction::divNum(5,0); // check for zero division
}