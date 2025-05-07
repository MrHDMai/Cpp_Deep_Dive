/*The idea of namespace is to avoid the naming conflict in large - saclable projects. As the project grows, names of function and variables
may be conflicted. In this scenerio, namespace is used to confine the name of the variable or function within it's own scope - namescope.
All namespace when created are global by default. Consider that there are two classes with the log function - when programmer employs "using namespace std",
this will create conflict in the code when the log function is called. If the log functions in each of the classes are meant to 
*/

#include <iostream>
#include <string>

namespace createUsername {
    // Return the username as a std::string
    std::string intro() { // Changed return type from void to std::string
        std::string uname;
        std::cout << "Hello User, please enter your username: ";
        std::cin >> uname;
        return uname; // Return the captured username
    }
}

namespace createPass {
    // Return the password as a std::string
    std::string intro() { // Changed return type from void to std::string
        std::string pass;
        std::cout << "Hi User, please enter a chosen password: ";
        std::cin >> pass;
        return pass; // Return the captured password
    }
}

namespace math {
    const double pi = 3.14;
    const double squaredOPT(double num) {return num * num;}
}


int main() {
    // Capture the returned values
    std::string username = createUsername::intro();
    std::string password = createPass::intro();

    // Use the captured values
    std::cout << "Hi there, " << username 
              << "! Your password is set." << std::endl;

    std::cout<<"The number of PI is: " << math::pi << "\n" << std::endl;
    std::cout <<"The squared result of 5 is :" << math::squaredOPT(5) << std::endl;
    //the above implementation can be repetitve, consider the operation of using namespace math to tell compiler that we are
    //calling for the namespace within the namespace function of math and std lib of c++
    using namespace math;
    using namespace std;
    cout << "name of PI is " << pi << "\n" <<endl;
    cout << "The squared value of 26 is : " << squaredOPT(26) << endl; 
    return 0;
}
