/*
The goal of an enum is to create a set of defined properties that can be calls within the main functions.
The main function can output the indecies of the object by calling the name name of that property and assinging it an alias.
*/
#include<iostream>
using namespace std;

enum shapes { //declaring the list of shapes and specifying the type of shape
    square,
    circle, 
    triangle,
    rectangle,
    pentagon,
    heart
};

enum executionMethod{
    codeExpploit = 1,
    acctHack = 2,
    passwordCrack = 3

};

/* Implementing switch statement with enuam
Switch statement will access the validity of the condition and will output the appropriate funciton
if all falses, it will default to the mentioned default operation within the switch statement
*/
enum class mycarmodels{
    BMW,
    Mercedes,
    Jeep,
    Honda,
    Vw,
    Ford
};

int main(){
    shapes callindex = square; // calling the enum object and assigning ana alias to call a specifsic location of an object. 
    cout << "Index of shape:" << callindex << endl;
    executionMethod callAttck = acctHack;
    cout << acctHack << endl;
    /* Creating char with enum*/
    enum suits {clubs, diamonds, heart, spades};
    /* Consider that enum itself can also be a class*/
    enum class player: int {player1, player2, player3, player4};
    enum suitschar : char{myClubs, myDidamonds, myHearts, mySpades};
    suits card1 = diamonds;
    suits card2 = suits::spades;
    player contestent1 = player::player1;
    char g = static_cast<int>(contestent1) + 2;
    printf("%c \n",g);
    //Implementing switch
    
    mycarmodels mycar = mycarmodels::Honda;
    switch(mycar){
        case mycarmodels::BMW:
        cout <<"You have a BMW" << endl;
        break;
        case mycarmodels::Mercedes:
        cout << "You have a Merceds" << endl;
        break;
        case mycarmodels::Jeep:
        cout << "You have a Jeep" << endl;
        break;
        case mycarmodels::Honda:
        cout << "You have a Honda" << endl;
        break;
        case mycarmodels::Vw:
        cout <<"You have a VW" << endl;
        break;
        case mycarmodels::Ford:
        cout << "You have a ford" << endl;
        break;
    default:
    cout << "Your car model is not on the list" << endl;
    }
}