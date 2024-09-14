#include <iostream>
#include <algorithm>
using namespace std;
struct Node{
    int data;
    Node* prev;
    Node* next;
};

//write a function: Reverse Doubly Linked List
Node* reverse(Node* head){
    Node* temp = nullptr;
    Node* current = head;
    while(current != nullptr){
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    if(temp != nullptr){
        head = temp->prev;
    }
    return head;
}

int main(){
    
}