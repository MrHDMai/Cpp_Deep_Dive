#include<iostream>
#include<algorithm>
#include<cassert>

using namespace std;

template<typename T> // create a template class with typename T
class AddElements{
    T element; // create a private variable
public:
    AddElements(T arg){ //create a constructor for initialization takes the parameter of T type call arg
        element = arg; //set the public variable to the parameter within the main function, if this is call then the value placed within the parater will be the element
    }
    T add(T other){ // create a function call add with the return type of T
        return element + other; // add the value that is inputted to the another value that is inputed
    }
};

template<> // create another template version, consider that this template is different for we know the fixed return time - template specialization
class AddElements<string>{ //create class of initialize to string type
    string element; //create private elemnt of type string
public:
    AddElements(string arg){ // create an addelement function with string parameter, and string inputed as the parameter called within the main function will be the first element
        element = arg; // set element = to the parameter
    }
    string concatenate(string other){ // create a function that returns a string that takes the parameter of a string - return the first string element concatenate with the second element
        return element + other;
    }
};

int main () {
  int n,i;
  cin >> n; // size of quer
  for(i=0;i<n;i++) {
    string type; //declare in type of query
    cin >> type; //take in the type of query in order to check
    if(type=="float") { // if input value is specified as a float
        double element1,element2; // create two float variable
        cin >> element1 >> element2; // take in the two float variable
        AddElements<double> myfloat (element1); // invoke the first addelement class as an object with an alias reparameterized the arg to the first element
        cout << myfloat.add(element2) << endl; // cout by invoking the the add function by adding the two element
    }
    else if(type == "int") {
        int element1, element2;
        cin >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        cin >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}