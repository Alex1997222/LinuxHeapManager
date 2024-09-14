#include <iostream>
#include <algorithm>
#include <vector>
//Implement Stack (FIFO) using Arrays
#define MAX 1000

class MyStack{
private:
    int top;
    int arr[MAX];
public:
    MyStack(){
        top = -1;
    }

    bool push(int x){
        if(top >= MAX-1) return false;
        arr[++top] = x;
        return true;
    }

    int pop(){
        if(top < 0) return 0;
        int res = arr[top--];
        return res;
    }

    bool isEmpty(){
        return top < 0;
    }
};


int main(){
    
}