/* The goal of a pointer is to store the address of a declared variable, given this implementation, the pointer
doesn't make a copy of the data itself, but rather points or references the data instead of making a copies - limiting the amount of resource used. 
Furthermore, pointers can be used to dynamically allocate memory, and in some instances - pointers can also be reassigned to another
address. There are two type of pointers - thee void pointer and the std::byte pointers. 

Things to note:
& - operan operator which can be used to initialize a pointer that is pointing to a variable
* - dereference of operator
*/

#include<iostream>
#include<vector>
using namespace std;

struct car{ //creating a struct to store the name of the car intialize it to 256 byte
    char name[256];

};

void print_name(car *c_ptr){ //constructor to print the name, takes in the paramter of a pointer to the car obj, call it c_ptr
    printf("%s car \n",c_ptr->name); //print the string of the car's name, paramter is c_ptr initilized to the name variable
}
//using loops to pass iterate through all the car's name
void i_print(car* cars, size_t n_cars){
    for(size_t i = 0; i < n_cars; i++){
        printf("%s car \n", cars[i].name);
    }
}



int main(){
    int v = 20; 
    int* ptr = &v; //& denotes the retrieval of the memeory address of the variable
                  //* denotes the dereference of the address and access the value stored within the variable  
    cout << &v << endl; // printing the address of the variable
    cout <<  ptr << endl; // printing the address of the variable
    cout << *ptr << endl; // using the dereference in order to print the value store within the memory location

    cout << "------------------------------" << endl;
    //Lets use pointers to reference an arry;
    int numarr [] = {1,2,4};
    int* ptrarr = numarr; //creating a pointer that refernces the memeory address of the numarr arr.
    cout << ptrarr << endl; //calling the memeory address of the arr - this will only print out the memory address of the array.
    cout << *ptrarr << endl; //printing out the accessed value of memory of the arr by using the dereference - this method will print out the first value.
    ptrarr++; //post increment the value by one - access the second elemnt of the array from memory;
    cout << *ptrarr << endl; // print out the second values of the access memory from the arr. 
    ptrarr++; // post increment to find the third value;
    cout << *ptrarr << endl; // print the third value
    int a = 10;
    int* pt{&a};
    *pt = 700; // overloading variable a after dereferencing it
    cout <<*pt << endl;
    int myvar{};
    printf("My myvar value is: %d\n", myvar);
    int *myvar_add = &myvar;
    printf("&myvar value is %p\n",myvar_add);
    printf("dereference of &myvar value is %p\n",*myvar_add);
    cout << "----------------------------------------- "<< endl;
    int myage = 0;
    int * myage_add = &myage;
    printf("Value at my age dddress is: %p\n",myage_add);
    printf("Value at my age dddress is: %d\n",*myage_add);
    //reassigned the value of my age as so
    *myage_add = 10; // declare the pointer and override the information of the value within the address
    printf("My value of the address is: %d\n", *myage_add); //use %d to print the number
    printf("My age's address is: %p\n", myage_add); //use %p to print the pointer value
    cout <<"--------------------------------------------" << endl;
    // int num;
    // cin>>num;
    // vector<int> vec(num);
    // for(int i = 0; i < num; i++){
    //     cin >> vec[i];
    // }
    // int* vecptr = vec.data(); // we can access the value within the vector by calling the .operator with data
    // for(int i = 0; i < vec.size(); i++){
    //     printf("outputting values of the vector: %d\n, the address of each is %p\n",*vecptr,vecptr);
    //     vecptr++;
    // }
    cout << "------------Implementation of the struct and print function------------" << endl;
    car mycar[] = {"Mercedes", "Benz", "Toyota", "Honda", "VW"};
    print_name(mycar);
    i_print(mycar,5);
    cout <<"Or using this function will yeild the same difference: " << endl;
    //implement using the for loop to iterate through all the elements of the string arr
    i_print(mycar, sizeof(mycar)/sizeof(car)); //consider that size of care is 5 (5 element * 256)/ car's declare char which is 256
                                               //This would work even if the size of the array changes later instead of hardcoding which
                                               //may break the code
    cout <<"----------------------------------Null Pointer----------------------------------" << endl;
    int* p = nullptr; // avoid dangling pointer
    printf("%p\n",p);
    int c = 45;
    p = &c;
    cout << p << endl;
    cout << *p << endl;

    cout << "-------------------------------Pointer Arthmetic-------------------------------" << endl;
    int ar[]{1,2,3,4,5};
    int *pa = ar;
    cout << "Print pointer adress: " << pa << endl;
    cout << "Print pointer value: " << *pa << endl;
    cout << "1. *pa = 11 changes ar[0]" << endl;
    *pa = 11;
    cout << "2. pa = 13 changes ar[3]" << endl;
    pa[2] = 13;
    cout << "1. *(pa+3) = 14 changes ar[3]" << endl;
    *(pa + 3) = 14;
    for(auto val : ar){
        cout <<"This is the mod the pervious value without loop: "  << val << endl;
    }
    cout << "------------------" << endl;
    //Using a loop to increment the value within the arr by 3, one can use any arthmetics
    for(int i = 0; i < 5; i++){
        *pa++ -=3;
    }
    for(auto val : ar){
        cout <<  "Usinng loop: " << val << endl;
    }
    cout << endl;
    cout <<"---------smart pointers and void----------" << endl;
    char i_c[]{"Hello"};
    *i_c = 'H';
    const char *ptc{i_c};
    cout << ptc << endl;
    //*ptc = 'v'; // cannot write to the const function, this implementation will break
    printf("i_c address value is: %p\n" ,*i_c);
    printf("Valye of *ptc is: %s \n",ptc);
    char *const cpyptr{i_c}; // recall that when declaring a value as a const - the data is a read only.
    cout << "Value of copy pointer is: " << cpyptr << endl;
    //--------------------------------------------------------//
    char strarr[]{"Hello"};
    char *const cptr{strarr};
    *cptr = 'H';
    cout << "*ccptr : \n" << *cptr <<endl;
    const char *ncp = const_cast<const char *>(cptr);
    ncp++;
    cout << "ncp++: \n" << ncp << endl;
    char *const ncp2 = const_cast<char *const>(ncp); // const cast will allow a new variable to be allocated to const ncp
    cout << "ncp2: \n" << ncp2;
    return 0;

}