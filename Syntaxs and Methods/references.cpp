#include<cstdio>
/*Both pointers and references are used to indirectly access the memeory location of data types, they can be used to 
modify the data type, and for references, they can pass in data type arguments. 
Declaration of pointers: int *var = &ref
Declaration of references: int& ref = var
Distinction: -Pointer can point to multiple address, references cannot be reassigned to which it is pointing to
             -Pointers can be pointed to a null value - use with caution. References cannot have null, and must always have a valid object 
             that it is pointing to
             - Pointers stores the address which takes 4/8 byte while reference requires to additoinal meemory and store it via alias.
             - Pointers suppoerts athmetics while refernces doesn't. 
Context of usage
poitner - used to dynamically allocate memory. 
        - used to depoly optional null arguments.
        - used pointer arithmetics to compute arrays and linked list.
references - safer than  pointers when allocating the alias to veriable and overloading it
           - reference used to make a copy of a large object to further modify
           - operator overloading
*/
#include<iostream>
using namespace std;

struct yearcompute{
    int year;
    int get_year(){
        return year;
    } 
    void set_year(int nyear){
        year = nyear;
    }
};

struct aexp{
    int result = 0;
    int num{2};
    int num2{4};
    int compute(int signed b, int a){
        return result = -b + (num2*b*a)/(num*a);
    }
    void setval(int new_num, int new_num2, int signed b, int a){
        num = new_num;
        num2 = new_num2;
        result = compute(a,b);
    }

};

struct simpleaexp{
    const int num1{2};
    const int num2{4};
    int result{0};
    int simplecompute(int b, int a){
        return result = -b + (num2 * b * a)/(num1*a);
    }
};

int simple_set(simpleaexp &srt, int b, int a){
    return srt.simplecompute(b,a);
}

void returnresult(aexp &rtd,int num, int num2, int signed b, int a){
    rtd.setval(num, num2, b, a);
}
void add_year(yearcompute &wyear){
    wyear.set_year(wyear.get_year() + 1);
}

int main(){
    yearcompute yc;
    yc.set_year(20225);
    printf("The year is: %d\n",yc.get_year());
    add_year(yc);
    printf("The yeat is: %d\n", yc.get_year());

    aexp obj;
    returnresult(obj,2,4,3,5);
    cout << obj.result << endl;

    simpleaexp sae;
    simple_set(sae,6,7);
    cout << sae.result << endl;
}