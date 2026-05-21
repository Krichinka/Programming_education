#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <string.h>
#include <stdlib.h>

#include "../src/task5.h"

static void test_xor_encrypt_and_decrypt(void **state) {
    (void) state;

    char text[] = "Hello World";
    char key[] = "secret";
    char encrypted[50];
    char decrypted[50];

    int text_len = strlen(text);

    xor_encrypt(text, key, encrypted, text_len);
    xor_encrypt(encrypted, key, decrypted, text_len);

    decrypted[text_len] = '\0';

    assert_string_equal(decrypted, text);
}

static void test_xor_encrypted_differs_from_original(void **state) {
    (void) state;

    char text[] = "Hello World";
    char key[] = "secret";
    char encrypted[50];

    int text_len = strlen(text);

    xor_encrypt(text, key, encrypted, text_len);

    assert_memory_not_equal(encrypted, text, text_len);
}

static void test_caesar_cipher_encrypt_shift_3(void **state) {
    (void) state;

    char text[] = "The quick brown fox jumps over the lazy dog";
    char output[100];

    caesar_cipher(text, 3, output);

    assert_string_equal(output, "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj");
}

static void test_caesar_cipher_decrypt_shift_minus_3(void **state) {
    (void) state;

    char encrypted[] = "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj";
    char output[100];

    caesar_cipher(encrypted, -3, output);

    assert_string_equal(output, "The quick brown fox jumps over the lazy dog");
}

static void test_caesar_cipher_keeps_spaces_and_symbols(void **state) {
    (void) state;

    char text[] = "Hello, World! 123";
    char output[100];

    caesar_cipher(text, 3, output);

    assert_string_equal(output, "Khoor, Zruog! 123");
}

static void test_caesar_cipher_wraps_alphabet(void **state) {
    (void) state;

    char text[] = "xyz XYZ";
    char output[100];

    caesar_cipher(text, 3, output);

    assert_string_equal(output, "abc ABC");
}

static void test_vigenere_encrypt_classic_example(void **state) {
    (void) state;

    char text[] = "ATTACKATDAWN";
    char keyword[] = "LEMON";
    char output[100];

    vigenere_encrypt(text, keyword, output);

    assert_string_equal(output, "LXFOPVEFRNHR");
}

static void test_vigenere_encrypt_keeps_non_letters(void **state) {
    (void) state;

    char text[] = "ATTACK AT DAWN!";
    char keyword[] = "LEMON";
    char output[100];

    vigenere_encrypt(text, keyword, output);

    assert_string_equal(output, "LXFOPV EF RNHR!");
}

static void test_rc4_encrypt_and_decrypt(void **state) {
    (void) state;

    char key[] = "Key";
    char data[] = "Secret message";
    char original[] = "Secret message";

    int data_len = strlen(data);

    simple_rc4(key, strlen(key), data, data_len);
    simple_rc4(key, strlen(key), data, data_len);

    assert_string_equal(data, original);
}

static void test_rc4_encrypted_differs_from_original(void **state) {
    (void) state;

    char key[] = "Key";
    char data[] = "Secret message";
    char original[] = "Secret message";

    int data_len = strlen(data);

    simple_rc4(key, strlen(key), data, data_len);

    assert_memory_not_equal(data, original, data_len);
}

static void test_simple_hash_hello(void **state) {
    (void) state;

    assert_int_equal(simple_hash("Hello"), 1835);
}

static void test_simple_hash_world(void **state) {
    (void) state;

    assert_int_equal(simple_hash("World"), 1833);
}

static void test_simple_hash_hello_world(void **state) {
    (void) state;

    assert_int_equal(simple_hash("HelloWorld"), 6268);
}

static void test_simple_hash_test(void **state) {
    (void) state;

    assert_int_equal(simple_hash("Test"), 1295);
}

static void test_simple_hash_empty_string(void **state) {
    (void) state;

    assert_int_equal(simple_hash(""), 0);
}

static void test_generate_key_length(void **state) {
    (void) state;

    char key[11];

    srand(1);
    generate_key(key, 10);

    assert_int_equal(strlen(key), 10);
}

static void test_generate_key_contains_only_lowercase_letters(void **state) {
    (void) state;

    char key[11];

    srand(1);
    generate_key(key, 10);

    for (int i = 0; i < 10; i++) {
        assert_true(key[i] >= 'a' && key[i] <= 'z');
    }
}

static void test_generate_key_ends_with_null_terminator(void **state) {
    (void) state;

    char key[11];

    srand(1);
    generate_key(key, 10);

    assert_int_equal(key[10], '\0');
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_xor_encrypt_and_decrypt),
        cmocka_unit_test(test_xor_encrypted_differs_from_original),

        cmocka_unit_test(test_caesar_cipher_encrypt_shift_3),
        cmocka_unit_test(test_caesar_cipher_decrypt_shift_minus_3),
        cmocka_unit_test(test_caesar_cipher_keeps_spaces_and_symbols),
        cmocka_unit_test(test_caesar_cipher_wraps_alphabet),

        cmocka_unit_test(test_vigenere_encrypt_classic_example),
        cmocka_unit_test(test_vigenere_encrypt_keeps_non_letters),

        cmocka_unit_test(test_rc4_encrypt_and_decrypt),
        cmocka_unit_test(test_rc4_encrypted_differs_from_original),

        cmocka_unit_test(test_simple_hash_hello),
        cmocka_unit_test(test_simple_hash_world),
        cmocka_unit_test(test_simple_hash_hello_world),
        cmocka_unit_test(test_simple_hash_test),
        cmocka_unit_test(test_simple_hash_empty_string),

        cmocka_unit_test(test_generate_key_length),
        cmocka_unit_test(test_generate_key_contains_only_lowercase_letters),
        cmocka_unit_test(test_generate_key_ends_with_null_terminator),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}