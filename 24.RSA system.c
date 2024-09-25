#include<stdio.h>
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        exp = exp >> 1;   
        base = (base * base) % mod; 
    }
    return result;
}
int main(){
    int p = 11, q = 3;
    int n, x, e, d;
    n = p * q;
    x = (p - 1) * (q - 1);
    for (int i = 2; i < 10; i++) {
        if (x % i != 0) {
            e = i;
            break;
        }
    }
    printf("Public key is (%d, %d)\n", e, n);
    for (int i = 2; i < 10; i++) {
        if ((e * i) % x == 1) {
            d = i;
            break;
        }
    }
    printf("Private key is (%d, %d)\n", d, n);
    int pt = 7;  
    int en, de;
    en = modExp(pt, e, n);
    printf("Encrypted message: %d\n", en);
    de = modExp(en, d, n);
    printf("Decrypted message: %d\n", de);
    return 0;
}
