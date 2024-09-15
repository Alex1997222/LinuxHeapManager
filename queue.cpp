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
        Node* newNode = new Node(value);
        if(rear == nullptr){
            front = rear = newNode;
        }else{
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue(){
        if(front == nullptr) return -1;
        Node* temp = front;
        front = front->next;
        int val = temp->value;
        if(front == nullptr){
            rear = nullptr;
        }
        delete temp;
        return val;
    }

    bool isEmpty(){
        return front == nullptr;
    }
};