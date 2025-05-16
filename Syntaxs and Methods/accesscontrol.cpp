/* Access control are way to create functions that defines what member function, if any at all can access the the variable of funciton that is declared
within the declared function. Consider that there are three type of access control declarations -  public, private and  protected.
Public function - any function inside or outside the class can access the content within this class. Private - the data and function within this class is only
accessible to the member functions of the same class. Protected - only accessible to the function itself and its derieved class, such is known as inheritence.
*/
#include<iostream>

struct dividarr{ // consider that since there is no declaration of what can access this function, it default to a public struct
    void div(){
        mid = left + (right - left)/2;
    }
    float left, mid, right;
    
};//any functions insides and  outside the class can have access to it

struct addyear{
private:
    void addcurrentyear(){
        year++;
    }
    int year;
    
    void friend addyearderieved(addyear& increval, int result){// the addyear pvt struct is now referenced by the increval declaration
        increval.year = result; //the alias increval will now be call the year value which is cremented by 1;
        increval.addcurrentyear(); // call the addcurrentyear function from the pvt function
        printf("The new year is: %d\n", increval.year); //print funcion for the result
    }
};

struct findmidpoint{
protected:
    void compute(){
        y = (m*x) + b;
    }
    float y,m,x,b;
    //on the other hand instead of using inheritence, we can use friend function in this scenario too
    void friend friend_compute(findmidpoint& obj){
        obj.m = 2.0f;
        obj.x = 3.0f;
        obj.b = 5.0f;
        obj.compute();
        printf("The result from friendly function for mid-point is: %f\n", obj.y);
    }
};

struct protected_f:public findmidpoint{
public: 
    void calc(float slope, float x_v, float intercpt){
        m = slope;
        x = x_v;
        b = intercpt;
        compute();
        std::cout << "Computer y is: " << y << std::endl;
    }
};

/* Access control also pertains to class. Class are like structs within the above example; however, the method of inheritence
may be different. 
*/

int main(){
    dividarr arropt;
    arropt.right = 3;
    arropt.left = 4;
    arropt.div();
    printf("The mid of the operation is: %f\n",arropt.mid);
    /*Analysis the private method*/
    addyear findnextyr;
    // findnextyr.year = 10; this declaration will not work for the fact that it is declared within the scope of private.
    //In this case, refer to the friend funciton above within line 23 for creating an implementation of a friend function 
    addyearderieved(findnextyr, 2023); //call the friend function, and declare the input value. Bomb.
   
    protected_f printprotect; // call the inherited function assign an alias
    printprotect.calc(2.0f,3.0f,5.0f); //call the calculate function through the alias with the correct parameter

    findmidpoint fm;
    // fm.friend_compute(fm); cannot call a friend function this way. Friend functions are stand alone.
    friend_compute(fm); // assigned the parent function with an alias and using that alias as the parameter for the friend function
    return 0;
}

