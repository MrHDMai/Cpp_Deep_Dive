#include<iostream>
using namespace std;

struct node{
    int key;
    node* left;
    node* right;
    node(int value) : key(value), left(nullptr), right(nullptr){}
};

node* insert(node* root, int key){
    if(root == nullptr) return new node(key);
    if(key < root->key)
        root->left = insert(root->left, key);
    else if(key > root->key)
        root->right = insert(root->right, key);

    return root;
}

bool search(node* root, int key){
    if(root = nullptr) return false;
    if(key = root->right) return true;
    if(key = root->left) return search(root->left,key);
    return search(root->right,key);
}

void inorder(node* root){
    if(root == nullptr) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right); 
}

node* findmin(node* root){
    while(root->left != nullptr)
        root = root->left;
    return root;
}

node* remove(node* root, int key){
    if(root == nullptr) return nullptr;
    if(key < root->key) {
        root -> left = remove(root->left,key);
    } else if(key > root->key){
        root->right = remove(root->right,key);
    } else{
        if(root->left == nullptr){
            node* temp = root->left;
            delete root;
            return temp;
        }
        node* temp = findmin(root->right);
        root->key = temp->key;
        root->right = remove(root->right,temp->key);
    }
    return root;
}

int main(){
    node* root = nullptr;
    root = insert(root,50);
    root = insert(root,30);
    root = insert(root,20);
    root = insert(root,40);
    root = insert(root,70);
    root = insert(root,60);
    root = insert(root,80);

    cout <<"In order traversal: ";
    inorder(root);
    cout<<endl;

    cout << "search 40: " << (search(root,40)? "Found" : "Not Found") << endl;

    root = remove(root, 30);
    cout << "Inorder after deleting 30: ";
    inorder(root);
    cout<<endl;
    return 0;
}