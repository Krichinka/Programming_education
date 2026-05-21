#ifndef TASK5_H
#define TASK5_H

void xor_encrypt(char *text, char *key, char *output, int text_len);
void caesar_cipher(char *text, int shift, char *output);
void vigenere_encrypt(char *text, char *keyword, char *output);
void simple_rc4(char *key, int key_len, char *data, int data_len);
unsigned int simple_hash(char *str);
void generate_key(char *key, int length);

#endif