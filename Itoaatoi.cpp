#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>

//Implement atoi and itoa
int myAtoi(char* s){
    if(s == nullptr) return 0;
    int sign = 1, num = 0;
    while(*s != '\0' && *s == ' ') s++;
    if(*s != '\0'){
        if(*s == '+') sign = 1;
        else if(*s == '-') sign = -1;
        s++;
    }
    while(*s != '\0' && isdigit(*s - '0')){
        num = num*10 + (*s - '0');
        if(num > (INTMAX_MAX - (*s - '0')) / 10){
            return sign == 1?INTMAX_MAX:INTMAX_MIN;
        }
        s++;
    }
    return num*sign;
}


char* myItoa(int num){
    if(num == 0){
        char* s = (char*)malloc(2);
        s[0] = '0';
        s[1] = '\0';
        return s;
    }
    int isNegative = 0;
    if(num < 0){
        isNegative = 1;
        num = -num;
    }
    int temp = num;
    int tsize = 0;
    while (temp > 0) {
        tsize++;
        temp /= 10;
    }
    char* s = (char*)malloc(tsize+isNegative+1);  // 1 for the '\0'
    int idx = tsize+isNegative;
    while(num){
        s[idx--] = (num%10) + '0';
        num /= 10;
    }
    if (isNegative == 1) {
        s[idx] = '-';
    }
    return s;
}


int main(){

    
}