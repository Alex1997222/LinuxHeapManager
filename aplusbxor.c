
int apbxor(int a,int b){
    while(b != 0){
        int carry = (a & b) << 1;
        a = a ^ b;
    } 
    return a;
}
