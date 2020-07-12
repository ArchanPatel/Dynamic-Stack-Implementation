#include "dynamic-stack.h"
#include <iostream>
using namespace std;

DynamicStack::DynamicStack() {
    items_ = new StackItem [16];
    init_capacity_ = 16;
    capacity_ = 16;
    size_ = 0;
}

DynamicStack::DynamicStack(unsigned int capacity){
    items_ = new StackItem [capacity];
    init_capacity_ = capacity;
    capacity_ = capacity;
    size_ = 0;
}

DynamicStack::~DynamicStack() {
    delete items_;
    items_= nullptr;
    init_capacity_ = 0;
    capacity_ = 0;
    size_ = 0;
}

bool DynamicStack::empty() const {
    return size_ == 0;
}

int DynamicStack::size() const {
    return size_;
}

void DynamicStack::push(StackItem value) {
    if (size() == capacity_){ //determine whether capacity needs changing
        capacity_*=2;
        StackItem *newItems_ = new StackItem [capacity_]; //make new stack with twice the capacity
        for(int i = 0; i < size(); i++) //copy over the elements in the old stack
            newItems_[i] = items_[i];

        //transfer newItems_ to items_
        StackItem *temp = items_;
        items_ = newItems_;
        delete [] temp;
        cout<<"Stack capacity reached, capacity has been doubled" << endl;
    }
    items_[size()] = value; //insert the value to the top
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    StackItem value; //holds the top of the stack
    if (size() == 0){ //check if the stack is empty
        cout<<"The Stack is empty, cannot pop" << endl;
        return EMPTY_STACK; //Empty stack constant
    }
    else{
        value = items_[size()-1]; //set to the top of the stack
        size_--;
    }
    if ((size() <= (capacity_/4)) && ((capacity_/2) >= init_capacity_)){ //determine whether capacity needs changing
        capacity_/=2;
        StackItem *newItems_ = new StackItem [capacity_]; //make new stack with 1/2 the capacity
        for(int i = 0; i < size(); i++) //copy over the elements in the old stack
            newItems_[i] = items_[i];

        //transfer newItems_ to items_
        StackItem *temp = items_;
        items_ = newItems_;
        delete [] temp;
        cout<<"Stack size is less than or equal to 1/4 capacity, capacity has been halved" << endl;
        cout<<"New capacity is still greater than initial capacity" << endl;
    }
    return value;
}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size() == 0){ //check if the stack is empty
        cout<<"Stack is empty, cannot peek" << endl;
        return EMPTY_STACK; //Empty Stack Constant
    }
    else
        return items_[size()-1]; //return the top of the stack
}

void DynamicStack::print() const {
    if (size() == 0) //check if the stack is empty
        cout<<"Stack is empty, cannot print" << endl;
    else{
        for (int i = size()-1; i >= 0; i--) //print the stack from top to bottom
            cout<<items_[i] << endl;
        cout<<"Stack printed";
    }
}