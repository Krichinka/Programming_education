#include "task5.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void xor_encrypt(char *text, char *key, char *output, int text_len) {
    int key_len = strlen(key);

    for (int i = 0; i < text_len; i++) {
        output[i] = text[i] ^ key[i % key_len];
    }
}

void caesar_cipher(char *text, int shift, char *output) {
    int len = strlen(text);

    for (int i = 0; i < len; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            output[i] = ((text[i] - 'a' + shift + 26) % 26) + 'a';
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            output[i] = ((text[i] - 'A' + shift + 26) % 26) + 'A';
        } else {
            output[i] = text[i];
        }
    }

    output[len] = '\0';
}

void vigenere_encrypt(char *text, char *keyword, char *output) {
    int text_len = strlen(text);
    int key_len = strlen(keyword);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            int shift = keyword[key_index % key_len] - 'A';
            output[i] = ((text[i] - 'A' + shift) % 26) + 'A';
            key_index++;
        } else {
            output[i] = text[i];
        }
    }

    output[text_len] = '\0';
}

void simple_rc4(char *key, int key_len, char *data, int data_len) {
    unsigned char S[256];
    unsigned char temp;
    int i, j = 0;

    for (i = 0; i < 256; i++) {
        S[i] = i;
    }

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_len]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = 0;
    j = 0;

    for (int k = 0; k < data_len; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        data[k] = data[k] ^ S[(S[i] + S[j]) % 256];
    }
}

unsigned int simple_hash(char *str) {
    unsigned int hash = 0;

    for (long unsigned int i = 0; i < strlen(str); i++) {
        hash += str[i] * (i + 1) + 50;
    }

    return hash;
}

void generate_key(char *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = 'a' + (rand() % 26);
    }

    key[length] = '\0';
}