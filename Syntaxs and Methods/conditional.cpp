/*If condition access the validity of the parameter and performs an operation if the parameter is valid.
*/
#include<iostream>
#include<vector>
using namespace std;

int main(){
    //simple example which can be expanded
    int n; 
    cin >> n;
    if(n >= 0){
        cout <<"The number is positive\n" << endl; 
    } else {
        cout <<"The number is not positive\n" << endl;
    }
    int num;
    cout << "Enter the number of input elements: \n" << endl;
    cin >> num;
    vector<int> v(num);//data structure that we will use to store element
    for(int i = 0; i < num; i++){
        cin >> v[i];
    } // condition recursively run to input all the number that is less the declare size input into the vector
    int* ptr = &v[3]; // creating a pointer variable to access specific element within the vector, recall using a refernce
    if(*ptr >=3){
        cout << "The number is greater than 3 \n";
    } else {
        cout << "The number is not greater than three \n";
    }
    //using boolean expression to access the validity of a condition to trigger a if condition
    bool a = 45 ==45;
    if(a){
        cout << "45 == 45 \n" << endl;
    } else {
        cout << "Not true\n";
    }

    //using the go to method within c++
    for(int i = 0; i < 10; i++){
        if(i == 9){
            goto end;
        }
    }
    end:
    cout << "You have reached 9\n" << endl;
}