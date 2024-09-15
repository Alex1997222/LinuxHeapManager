#include <stdio.h>
#include <cstdint>

// endianness swap
uint32_t swap_endianness(uint32_t input){
    
    uint8_t byte1 = (input & 0x000000FF) << 24;
    uint8_t byte2 = (input & 0x0000FF00) << 8;
    uint8_t byte3 = (input & 0x00FF0000) >> 8;
    uint8_t byte4 = (input & 0xFF000000) >> 24;

    uint32_t result = byte1 | byte2 | byte3 | byte4;
    return result;
}


// 2's complement
/*
01111111 = +127
01111110 = +126
01111101 = +125
...
00000001 = +1
00000000 =  0
11111111 = -1
...
10000010 = -126
10000001 = -127
10000000 = -128
*/