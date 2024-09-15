#include <stdio.h>

// Function to convert a binary number to Gray code
unsigned int binaryToGray(unsigned int num){
    return num ^ (num >> 1);
}

// Function to display the binary to form a number
void displayGrayCode(unsigned int num, int bits){
    for(int i = bits-1; i >= 0; i--){
        printf("%d",(num >> i) & 1);
    }
    printf("\n");
}

// Simple Version
// vector<int> grayCode(int n) {
//     vector<int> res;
//     for(int i = 0; i < (1 << n); ++i){
//         int gc = (i ^ (i >> 1));
//         res.push_back(gc);
//     }
//     return res;
// }

int main(){
    int n = 8;  // number of graycodes to be generate
    int bits = 3;
    for(int i = 0; i < (1 << bits); i++){
        unsigned int t = binaryToGray(i);
        displayGrayCode(t,bits);
    }
    return 0;
}