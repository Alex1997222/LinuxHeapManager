#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
string decimalToBinary(float num,int k){
    string res = "";
    int Integral = (int)num;
    float decimal = num - Integral;
    while(Integral){
        res += (Integral % 2) + '0';
        Integral /= 2;
    }
    reverse(res.begin(),res.end());
    res.push_back('.');
    while(k--){
        decimal *= 2;
        int fract_bit = ((int)decimal % 2);
        if (fract_bit == 1) 
        { 
            decimal -= fract_bit; 
            res.push_back(1 + '0'); 
        } 
        else
            res.push_back(0 + '0'); 
    }
}

