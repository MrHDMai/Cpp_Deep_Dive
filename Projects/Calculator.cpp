#include<iostream>
#include<vector>
#include<string>
#include<cmath>

using namespace std;



int main(int argc, char* argv[]){ //main function takes in the argument count and argument vector
    if(argc !=4 ){
        //will check if the argurment count is 3 then it will return that the number of argumrnt and operation and the 1 and second number
        cout << "Usage : Calculator.exe <num1> <operator> <num2>" << endl;
        return 1; // exit
    }
    string opt = argv[2];
    if(opt.length() != 1){
        cout << "Operator must be single character (+,-,x,/)" << endl;
        return 1;
    }
    char options = opt[0]; // takes in the first character
    if(options != '+' && options != '-' && options != '/' && options != 'x'){
        cout << "Error: unsupported operator! Please only use (+,-,x,/)";
        return 1;
    }
    //when taking in the char arg of the input, we have to convert the input into number, use atof
    double num1 = atof(argv[1]); //consider that atof is the stl from c++ to convert string to floating point number
    double num2 = atof(argv[3]);

    double result = 0; 
    switch(options){
        case '+': result = num1 + num2;
        cout << num1 << " " << options << " " << num2<< " = " << result << endl;
        break;
        case '-': result = num1 - num2;
        cout << num1 << " " << options << " " << num2<< " = " << result << endl;
        break;
        case 'x': result = num1 * num2;
        cout << num1 << " " << options << " " << num2<< " = " << result << endl;
        break;
        case '/': 
            if (num2 == 0) {
                cout << "Error: Division by zero!" << endl;
                return 1;
            }
            result = num1 / num2;
            cout << num1 << " " << options << " " << num2<< " = " << result << endl;
            cout << "Show remainder? (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                double remainder = fmod(num1, num2);
                cout << "Remainder: " << remainder << endl;
            }
            break;
        default: 
        cout <<"Please try again" << endl;
    }
    return 0;
}