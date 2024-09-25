#include <stdio.h>

long long int power(int a, int b, int mod) {
    long long int t;
    if (b == 0) return 1; // a^0 = 1
    if (b == 1) return a % mod; // a^1 = a
    t = power(a, b / 2, mod);
    if (b % 2 == 0)
        return (t * t) % mod; // Even exponent
    else
        return (((t * t) % mod) * a) % mod; // Odd exponent
}

int main() {
    int n, g, x, a, y, b;

    printf("Enter the value of n and g: ");
    scanf("%d %d", &n, &g);

    printf("Enter the value of x for the first person: ");
    scanf("%d", &x);
    a = power(g, x, n); // Public key for person 1

    printf("Enter the value of y for the second person: ");
    scanf("%d", &y);
    b = power(g, y, n); // Public key for person 2

    // Compute the shared secret keys
    long long int key1 = power(b, x, n); // Key for person 1
    long long int key2 = power(a, y, n); // Key for person 2

    printf("Key for the first person is: %lld\n", key1);
    printf("Key for the second person is: %lld\n", key2);

    return 0;
}

/*Enter the value of n and g: 23 5
Enter the value of x for the first person: 6
Enter the value of y for the second person: 15
	Key for the first person is: 2
Key for the second person is: 2
*/
