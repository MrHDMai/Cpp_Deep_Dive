/*Functions are defined operations that can be called and used for different code implementations within the software.
When a function is compile, the compiler will put each of the function call within a stack frame.
These expression may contain parameters with logic which when called within the main functions, will computer the logic
once the parameters are specified. Functions can be decalred with extern, inline and constexpt before each funcitons name.

extern - tells the compilter that the function being used is else where within the file structure, often seen with
    implementation with header files. 
    Consider that with this implementation, without defintion, this will create linking errors
inline - used to insert the function directly where it is called, often used for small functions such as getters, and simple
    calculations.
    Consider that inline are just hints and doesn't guarantee inlining.
constexpr - indicate to the compiler that the function variable and return type are assessed during compiled time.
    Consider that for these implementation, there is no memeory allocation and input or output

*/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;
auto multip(int a, int b){
    return a * b;
}

auto fsqrt(double n){
    return sqrt(n);
}

auto power(int n){
    return n * n;
}

struct point{int a; int b;}; // create a blueprint that declares int a and b

void set_point(const point& pt){ //create a function that has the parameter the point's struct, passed in a reference
    printf("Points values: a=%d, b=%d\n", pt.a,pt.b); //the copied function now has access to int a and b
}
//the point is the initialize the value within a struct function, and then use a member function
//to pass in the initialize struct's value for additional computation
struct setval{
    int c;
    int d;
};

void addval(const setval& sf){
    printf("the sum is: %d\n",sf.c + sf.d);
}

struct setvalue{
    int a;
};

void pushvalue(const setvalue& svalue){
    vector<int> v;
    int n;
    cout << "enter num: " << endl;
    cin>>n;
    cout << "struc value is: " << svalue.a<<endl;
    for(int i = 0; i < n; ++i){
        int temp;
        cout<<"Enter value: " <<i << endl;
        cin>>temp;
        v.push_back(temp);
    }
    for(auto num: v){
        cout << num << endl;
    }
}

auto findpoly(int a, int b){
    const int num = 2;
    const int num1 = 4;
    float result = (-b + fsqrt(power(b) - (num1*a*b)))/(num*a);
    return result;   
}

int main(){
    printf("The product is: %d\n",multip(2,3));
    printf("The root is: %f\n",fsqrt(6));
    printf("The second power is: %d\n",power(6));
    printf("The polynomial result is: %f\n",findpoly(7,-1));
    point p; //calls the struct and create an object with name p
    p.a = 1; //append a = 1 to the struct's layout
    p.b = 2;// append b = 2 to the struct's layout
    set_point(p); //calls the set point which stores the struct's blueprint by references
    set_point({1,2});//pass in the temp structs
    setval sv;
    sv.c = 1;
    sv.d = 1;
    addval(sv);
    setvalue svl;
    svl.a = 2;
    pushvalue(svl);

    return 0;
}