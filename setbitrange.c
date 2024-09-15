#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

unsigned int setbit(unsigned int x, unsigned int n){
    return x | (1 << n);
}

uint32_t setBitRange(uint32_t num, int start,int end){
    // create a bitmask
    uint32_t bitmask = (((1U << end+1)-1) >> start) << start;
    printf("Original number: 0x%08X\n", bitmask);
    // for(int i = start; i <= end; ++i){
    //     bitmask |= (1 << i);
    //     
    // }
    // // or the bit mask
    /*
        0x0000 0000 0000 0000 1111 1111 0000 0000
        0x0000 0000 0000 0001 000 0000 0000 0000   (-1)
        0x0000 0000 0000 0000 1111 1111 1111 1111
        
    */
    return num | bitmask;
}

int main(){
    uint32_t num = 0x12345678;  // Example 32-bit number
    int start = 8;  // Start bit position
    int end = 15;   // End bit position

    printf("Original number: 0x%08X\n", num);
    num = setBitRange(num,start,end);
    printf("Modified number: 0x%08X\n", num);

    return 0;
}