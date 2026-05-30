#include <iostream>

using namespace std;


	// CREATE NODE CLASS HERE //
	//                        //
	//                        //
	//                        //
	//                        //
	////////////////////////////


class LinkedList {
    private:
		// CREATE MEMBER VARIABLES HERE //
		//                              //
		//                              //
		//                              //
		//                              //
		//////////////////////////////////

    public:
		// CREATE LL CONSTRUCTOR HERE //
		//                            //
		//                            //
		//                            //
		//                            //
		////////////////////////////////

        ~LinkedList() {
            Node* temp = head;
            while (head) {
                head = head->next;
                delete temp;
                temp = head;
            }
        }

        void printList() {
            Node* temp = head;
            while (temp != nullptr) {
                cout << temp->value << endl;
                temp = temp->next;
            }
        }

        void getHead() {
            if (head == nullptr) {
                cout << "Head: nullptr" << endl;
            } else {
                cout << "Head: " << head->value << endl;
            }
        }

        void getTail() {
            if (tail == nullptr) {
                cout << "Tail: nullptr" << endl;
            } else { 
                cout << "Tail: " << tail->value << endl;
            }  
        }

        void getLength() {
            cout << "Length: " << length << endl;
        }

};



int main() {
        
    LinkedList* myLinkedList = new LinkedList(4);

    myLinkedList->getHead();
    myLinkedList->getTail();
    myLinkedList->getLength();
    
    cout << "\nLinked List:\n";
    myLinkedList->printList();

    /*  
        EXPECTED OUTPUT:
    	----------------
        Head: 4
        Tail: 4
        Length: 1

        Linked List:
        4

    */
       
}

