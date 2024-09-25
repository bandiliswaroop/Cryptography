#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to create the cipher alphabet from the keyword
void createCipherAlphabet(const char *keyword, char *cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0};
    int k = 0;

    // Add unique characters from the keyword to the cipher alphabet
    for (int i = 0; keyword[i] != '\0'; i++) {
        char c = tolower(keyword[i]);
        if (isalpha(c) && !used[c - 'a']) {
            used[c - 'a'] = 1;
            cipherAlphabet[k++] = c;
        }
    }

    // Fill in the rest of the alphabet
    for (char c = 'a'; c <= 'z'; c++) {
        if (!used[c - 'a']) {
            cipherAlphabet[k++] = c;
        }
    }
    cipherAlphabet[k] = '\0'; // Null-terminate the string
}

// Function to encrypt the plaintext
void encrypt(const char *plaintext, const char *cipherAlphabet, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = tolower(plaintext[i]);
        if (isalpha(c)) {
            ciphertext[i] = cipherAlphabet[c - 'a'];
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabet characters remain unchanged
        }
    }
}

// Function to decrypt the ciphertext
void decrypt(const char *ciphertext, const char *cipherAlphabet, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = tolower(ciphertext[i]);
        if (isalpha(c)) {
            // Find the index of the character in the cipherAlphabet
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (cipherAlphabet[j] == c) {
                    plaintext[i] = 'a' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabet characters remain unchanged
        }
    }
}

int main() {
    char keyword[100], plaintext[100], ciphertext[100], decryptedtext[100];
    char cipherAlphabet[ALPHABET_SIZE + 1]; // +1 for null terminator

    // Get keyword from user
    printf("Enter keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    // Create cipher alphabet
    createCipherAlphabet(keyword, cipherAlphabet);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);

    // Get plaintext from user
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Encrypt the plaintext
    encrypt(plaintext, cipherAlphabet, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, cipherAlphabet, decryptedtext);
    decryptedtext[strlen(plaintext)] = '\0'; // Ensure null-termination
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

/* Enter keyword: secret
Cipher Alphabet: secretabdfghijklmnopquvwxyz
Enter plaintext: hello world
Ciphertext: htrrm wosrd
Decrypted text: hello world */
