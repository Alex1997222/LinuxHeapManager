#include <iostream>
#include <algorithm>
#include <vector>

class Node{
public:
    int value;
    Node* next;
    Node(int val){
        value = val;
        next = nullptr;
    }
};
//Implement Queue using Linked List
class Queue{
private:
    Node* rear;
    Node* front;
public:
    Queue(){
        rear = nullptr;
        front = nullptr;
    }

    bool isEmpty(){
        return front == nullptr;
    }

    void enQueue(int value){
    
    }

    int dequeue(int value){
        
    }
};