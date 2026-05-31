#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class solution{
public: 
    ListNode* addTwoNumber(ListNode* l1, ListNode* l2){
        ListNode* temphead = new ListNode(0);
        ListNode* current = temphead;
        int carry = 0;

        while(l1!=nullptr || l2!=nullptr || carry!= 0){
            int val1 = (l1!=nullptr) ? l1-> val : 0;
            int val2 = (l2!=nullptr) ? l2-> val : 0;
            
            int sum = val1 + val2 + carry;
            carry = sum/10;
            int digit = sum % 10;

            current -> next = new ListNode(digit);
            current = current->next;

            if(l1!=nullptr) l1 = l1->next;
            if(l2!=nullptr) l2 = l2->next;
        }
        ListNode* result = temphead->next;
        delete temphead;
        return result;
    }
};

int main(){

}