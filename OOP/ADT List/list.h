#ifndef LIST_H
#define LIST_H

class list{
private:
    int *myitem;
    int mycount;
public:
    list();
    ~list();
    int get(int index);
    void insert(int index, int val);
    int search(int val);
    void remove(int index);
    int count();

};


#endif