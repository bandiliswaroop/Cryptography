#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 2 
int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int key[SIZE][SIZE];
    int i, j, k;
    printf("Enter plaintext (only uppercase letters, max 98 characters): ");
    scanf("%s", plaintext);
    printf("Enter key matrix (%d x %d):\n", SIZE, SIZE);
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }
    int len = strlen(plaintext);
    for (i = 0; i < len; i += SIZE) {
        int matrix[SIZE][1];
        for (j = 0; j < SIZE; j++) {
            matrix[j][0] = plaintext[i + j] - 'A';
        }

        for (j = 0; j < SIZE; j++) {
            int sum = 0;
            for (k = 0; k < SIZE; k++) {
                sum += key[j][k] * matrix[k][0];
            }
            ciphertext[i + j] = (sum % 26) + 'A';
        }
    }
    ciphertext[len] = '\0'; 
    printf("Encrypted Ciphertext: %s\n", ciphertext);
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    int detInv = -1;
    for (int x = 1; x < 26; x++) {
        if ((det * x) % 26 == 1) {
            detInv = x;
            break;
        }
    }
    if (detInv == -1) {
        printf("Matrix is not invertible; decryption cannot proceed.\n");
        return 1;
    }
    int adj[SIZE][SIZE];
    adj[0][0] = key[1][1];
    adj[0][1] = -key[0][1];
    adj[1][0] = -key[1][0];
    adj[1][1] = key[0][0];

    int inverseKey[SIZE][SIZE];
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            inverseKey[i][j] = (adj[i][j] * detInv) % 26;
            if (inverseKey[i][j] < 0) {
                inverseKey[i][j] += 26;
            }
        }
    }
    for (i = 0; i < len; i += SIZE) {
        int matrix[SIZE][1];
        for (j = 0; j < SIZE; j++) {
            matrix[j][0] = ciphertext[i + j] - 'A';
        }

        for (j = 0; j < SIZE; j++) {
            int sum = 0;
            for (k = 0; k < SIZE; k++) {
                sum += inverseKey[j][k] * matrix[k][0];
            }
            decrypted[i + j] = (sum % 26 + 26) % 26 + 'A'; 
        }
    }
    decrypted[len] = '\0'; 
    printf("Decrypted Plaintext: %s\n", decrypted);

    return 0;
}

/*OUTPUT:
Enter plaintext (only uppercase letters, max 98 characters): MEETME
Enter key matrix (2 x 2):
9 4
5 7
Encrypted Ciphertext: UKIXUK
Decrypted Plaintext: MEETME*/
