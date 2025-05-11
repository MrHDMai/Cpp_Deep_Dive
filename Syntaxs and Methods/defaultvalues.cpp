/*The conceptp of default values is to understand where within the code are the values assigned. In other words,
by the declared scope of the value, how are the value initialized and the interaction that it will have on the
operation of the program.
*/

#include<iostream>

using namespace std;

int global; // will be defaulted as 0
string global_s;

int counter(){
    static int mycount;// static will signify that this variable will only be used within the scope eof the counter function
    return ++mycount;//mycount will not be abled to be modified
}

int main(){
    int local;
    printf("Local value: %d\n",local);
    static float static_float;
    printf("Local value: %d\n",static_float);
    string local_string;
    printf("Local string: %s\n",local_string);
    int arr[3] = {};
    for(auto num : arr){
        cout << "elements within the arr are: "<< num << endl;
    }
    printf("global value: %d\n", ++global);
    printf("Local string: %s\n",global_s);
    cout << counter() << endl;
    int a{2}; // another way that we can initalized variable
    cout << a << endl;

}