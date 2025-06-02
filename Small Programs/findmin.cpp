#include<iostream>

using namespace std;


int main(){
    int arr[5] = {0};
    for(int i = 0; i < 5; i++){
        cout << "Ennter the number: " << i << endl;
        cin >> arr[i];
    }
    int min = arr[0]; // min is the first number
    for(int i = 1; i < 5; i++){ // if the first numebr is greatter than the input inserted within the arr
        if(min > arr[i]){
            min = arr[i];// then the minimuum is the first of the arr
        }
    }
    cout << "Min is: " << min << endl;
fi