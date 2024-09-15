#include <stdio.h>
#include <ctype.h>
#include <string.h>

void increment_hex_string(char *hex_str){
    int idx = strlen(hex_str)-1;
    while(idx >= 0){
        char cur = toupper(hex_str[idx]); 
        if(cur >= '0' && cur <= '9'){
            if(cur == '9'){
                hex_str[idx] = '0';
            }else{
                hex_str[idx] = cur + 1;
                return;
            }

        }else if(cur >= 'A' && cur <= 'F'){
            if(cur == 'F'){
                hex_str[idx] = '0';
            }else{
                hex_str[idx] = cur + 1;
                return;
            }         
        }
        idx--;
    }
}

int main(){
    
    char hexTech[] = "1F9A";  // 1F9B  FFFF->0000
 
    return 0;
}