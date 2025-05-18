/*This lession is dedicated to defined data type within the code that the compiler can determined by on the
data that is assigned to it. Such includes auto and tuple
*/
#include<iostream>
#include<vector>
#include<tuple>
using namespace std;

int main(){
    auto a = 10;
    auto b = 20;
    auto c = 4234553;
    auto d = 1.0f;
    auto e = 10.12;
    auto f = 'a';
    auto g = true;
    //consider that there is no type define for any of of those variable, but it is not
    //wrong since the auto will tell the compiler to infer these types 

    vector<tuple<int,int>> values;
    values.push_back(make_tuple(1,2));
    //one can print using the get method get<0>num be sure to use the reference when decare the value use to traverse loop
    for(auto& num : values){
        cout << get<0>(num) << get<1>(num) <<endl;
    }
    //one can print via structure biniding
    for(auto& [first,second]:values){
        cout << first << second <<endl;
    }

    //tumple example using string and int
    vector<tuple<string,int>> mycar;
    mycar.push_back(make_tuple("BMW",2009));
    mycar.push_back(make_tuple("Merced",2026));
    mycar.push_back(make_tuple("Honda", 2021));
    //printing usinig tuple expression
    for(tuple<string,int> cars: mycar){
        cout << get<0>(cars) <<" "<< get<1>(cars) <<endl;
    }
    //printing using structure binding
    for(auto &[brand,year] :mycar){
        cout << brand << " " << year << endl;
    }

}