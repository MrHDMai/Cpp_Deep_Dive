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
        cout <<"The number is positive" << endl; 
    } else {
        cout <<"The number is not positive" << endl;
    }
    int num;
    cout << "Enter the number of input elements: " << endl;
    cin >> num;
    vector<int> v(num);//data structure that we will use to store element
    for(int i = 0; i < num; i++){
        cin >> v[i];
    } // condition recursively run to input all the number that is less the declare size input into the vector
    int* ptr = &v[3]; // creating a pointer variable to access specific element within the vector, recall using a refernce
    if(*ptr >=3){
        cout << "The number is greater than 3";
    } else {
        cout << "The number is not greater than three";
    }
}