/*
Class and struct are simliar - the only diffrence is there their control access parameter are different.
Consider that when declaring a class, it is declare as private be default. When private only memeber function
and friend function can access the value of these variable. In this manner, when declaring a derived class,
that class is private unlike to that of a struct. Note that structs are for simple data objects, while class are
for complex data objects.
*/

#include<iostream>
#include<vector>
using namespace std;

class checkv{
    bool isnegative;//create a bool expression to store the negative value for input check
public:
    //create a constructor logic to determine if the input is a negative number
    checkv(int n = 0) : isnegative(n < 0){
        if(isnegative){
            cout <<"You cannot enter a negative number.\n";
        }
    }
    ~checkv(){
        printf("Object is destructed");
    }
    //since the bool expression to store the negative check is declare and defaulted as a pvt function, create helper funciton to access value
    bool isNegative() const{
        return isnegative;
    }
    bool empty(const vector<int>& v){
        return v.empty();
    }
private:
    int insrtelmt(int n, vector<int>& vec){
        vec.push_back(n);
        return n;
    }
    friend int from_pvt(checkv& obj, int n, vector<int>& v); // for classses if one wants to use friend funciton, first declare the friend function inside the class
};
//then one must declare the function outside the class
int from_pvt(checkv& obj, int n, vector<int>& v){
    return obj.insrtelmt(n,v);
}


int main(){
    int n; 
    cout << "Enter the the number of input into the vector: \n" << endl;
    cin >> n; 
    checkv negcheck(n);
    if(negcheck.isNegative()){
        return 0;
    }
    vector<int>v(n);
    for(int i = 0; i < v.size(); i++){
        cin >> v[i];
    }
    checkv checkvector;
    bool is_empty = checkvector.empty(v);
    if(is_empty){
        cout << "Empty Vector \n";
    } else{
        cout <<"Not empty \n";
        checkv checkvectorpvt;
        int val;
        cout <<"Enter another element in order to push into the vector: \n";
        cin >> val;
        int insertednum = from_pvt(checkvectorpvt, val,v);
        cout << "Inserted: " << insertednum << endl;
        for(auto num : v){
            printf("The total element within the vector are: %d\n", num);
        }
        cout <<"The total number of element within the vector is: " << v.size() << endl;
    }
    return 0;

}