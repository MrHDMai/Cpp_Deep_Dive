/*Consider STL are standard templated classes and functions within c++ that programmers can employ to hold data. For data
containers, these are arrays or vectors. Additionally, algorithms and iterators are common which saves the programmer
time increasing efficency while coding.
Examples of containers: Vector, list deque, set, map, unordered_set, stack, queue and priority_queue\
Algorithms templates: .begin(), , .sort(), .rbegin(), .rend()
*/
#include<array>
#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<memory>

using namespace std;

int main(){
    //arr implementation
    printf("---------------------Print the arr---------------------\n");
    array<int,4> arr{1,2,3,4};
    for(int i : arr){
        cout << i<< endl;
    }
    cout <<"Using dynamic memory allocation with pointers: " << endl;
    //we can use raw memeory management to access and modify the element within the arr
    int* arrptr = new int[5]{10,40,50,60,90};
    arrptr[2] = 90;
    for(int i = 0; i < 5; i++){
        cout << "The array values are: " << arrptr[i] << endl;
    }
    delete[] arrptr;
    cout <<"Using smart memory allocator: " << endl;
    std::unique_ptr<int[]> smararr(new int[3]{9,7,4});
    cout << "Smart pointer: " << endl;
    cout << smararr[1] << endl;


    printf("---------------------Print the vector and use sort from algo---------------------\n");
    //vector with sort from algorithm
    vector<int> v{5,43,1,3,7}; 
    sort(v.begin(),v.end());
    for(auto num : v){
        cout <<  num << endl;
    }
    //we can also apply dyamic memeory management to this code: 
    v.push_back(2);
    sort(v.begin(),v.end());
    for(auto i : v){
        printf("Push back for vector: %d\n",i);
    }
    //we can sort backwards
    sort(v.begin(),v.end(),greater<int>());
    for(auto i : v){
        cout << "The rever sort is: " <<  i << endl;
    }
    //then we can find specific element by specifying the index:
    printf("Print the second index after sorting: %d\n",v[2]);

    printf("---------------------Print deque with examples---------------------\n");
    //double ended queue, one can push into the vector at the first or push back to the last index
    deque<int>dq{5,6,72,9};
    dq.push_front(1);
    for(auto val : dq){
        printf("push_front: %d\n", val);
    }
    dq.push_back(100);
    for(auto val : dq){
        printf("push_back: %d\n", val);
    }
    printf("---------------------Print the Max-Heap via priority queue------------------\n");
    priority_queue<int> pq;
    pq.push(4);
    pq.push(1);
    pq.push(100);
    printf("Prioirty queue top: %d\n", pq.top());
    pq.pop(); //always pop the values
    printf("Prioirty queue top after pop: %d\n", pq.top());
    priority_queue <int, vector<int>, greater<>> pqmin;
    pqmin.push(100);
    pqmin.push(200);
    printf("Min heap of pq: %d\n", pqmin.top()); 

    printf("---------------------Applying stacks---------------------\n");
    //consider that this a stack is last tin first out
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << "The top of the stack is: " << stk.top() << endl;

    printf("---------------------Maps---------------------\n");
    //consider that maps are used to store relations between data
    map<string, int>m;
    m["player 1"] = 25;
    m["player 2"] = 45;
    m["player 3"] = 65;
    m.insert({"player 4", 85});
    for(auto i = m.begin(); i != m.end(); i++){
        cout << i->first << ":" << i-> second << "\n";
    }
    printf("---------------------Finding the key in maps---------------------\n");
    auto i = m.find("player 1");
    if(i!=m.end()){
        cout << "Found player one, key is: " << i->second << "\n";
    }

    printf("---------------------Iterators---------------------\n");
    vector<int>vec{1,5,7,9,10};
    //normal output of values in order
    for(auto i = vec.begin(); i!=vec.end();i++){
        cout << "Printing in normal order: "<< *i << "\n"<< endl;
    }
    //return value in reverse, append  the r in front of begin and end key
    for(auto i = vec.rbegin(); i!=vec.rend();i++){
        cout<< "Printing in reverse order: " << *i << "\n" <<endl;
    }
}