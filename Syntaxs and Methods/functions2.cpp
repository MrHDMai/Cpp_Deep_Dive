#include<iostream>
#include<string>
#include<queue>
#include<initializer_list>  
#include<cstdarg> // specified to the compiler when employed that there will be more than one paramters
using namespace std;
queue<string> message;

void clear_message_queue(){
    while(!message.empty()){
        message.pop();
    }
}

extern void funcmsg(const string& msg, bool clear_msg = false){
    if(clear_msg){
        clear_message_queue();
    }
    message.push(msg);
    cout << msg << endl;
}

int summation(initializer_list<int> v){
    int sum = 0;
    v.size();
    for(int i : v){
        sum += i;
    }
    return sum;
}

int sum(int first, ...){
    int sum = 0;
    va_list args;
    va_start(args,first);
        int i = first;
        while(i!=-1){
            sum +=i;
        }
        va_end(args);
        return sum;
}

int main(){
    funcmsg("First message", true);
    funcmsg("Second message");
    bool decision = true;
    funcmsg("Third message", decision);
    /*-------------------------------*/
    printf("sum with so value: %d\n",summation({}));
    printf("sum with so value: %d\n",summation({1,2,3,4,5}));
    printf("sum with so value: %d\n",summation({-1,-2,-3,-4,-5}));
    /*-----------------------------*/
    cout << sum(-1) << endl;
    cout << sum(-1,0,1,2,3,-1)<< endl;
    cout << sum(-3,-4,-5,-6,-1) << endl;
    

    return 0;
}

