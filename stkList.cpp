#include <iostream>
#include <algorithm>
#include <vector>

//Implement Stack using Linked List
class Node{
public:
    int value;
    Node* next;
    Node(int val){
        value = val;
        next = nullptr;
    }
};

class MyStack{
private:
    Node* topNode;
public:
    MyStack(){
        topNode = nullptr;
    }

    void push(int val){
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop(){
        if(topNode == nullptr) return;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    int top(){
        if(topNode == nullptr) return -1;
        return topNode->value;
    }

    bool isEmpty(){
        return topNode == nullptr;
    }
};