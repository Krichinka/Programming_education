#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdlib.h>
#include <string.h>

#include "brainfuck.h"
#include "config.h"
#include "logger.h"

static void make_test_config(Config *config) {
    config_set_defaults(config);
    config->tape_size = 10;
    config->max_steps = 10000;
    config->debug = 0;
    config->silent = 1;

    strcpy(config->log_file, "test_brainfuck.log");
    strcpy(config->tape_dump_file, "test_tape_dump.txt");
}

static void test_simple_output_A(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.", &config, &output);

    assert_int_equal(status, BF_OK);
    assert_non_null(output);
    assert_string_equal(output, "A");

    free(output);
    logger_close();
}

static void test_loop_output_A(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("++++++++[>++++++++<-]>+.", &config, &output);

    assert_int_equal(status, BF_OK);
    assert_non_null(output);
    assert_string_equal(output, "A");

    free(output);
    logger_close();
}

static void test_hello_world(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code(
        "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++."
        "<<+++++++++++++++.>.+++.------.--------.>+.>.",
        &config,
        &output
    );

    assert_int_equal(status, BF_OK);
    assert_non_null(output);
    assert_string_equal(output, "Hello World!\n");

    free(output);
    logger_close();
}

static void test_unmatched_open_bracket(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("++[>++<-", &config, &output);

    assert_int_equal(status, BF_ERROR_BRACKETS);
    assert_null(output);

    logger_close();
}

static void test_unmatched_close_bracket(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("++>++<-]", &config, &output);

    assert_int_equal(status, BF_ERROR_BRACKETS);
    assert_null(output);

    logger_close();
}

static void test_pointer_left_error(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("<", &config, &output);

    assert_int_equal(status, BF_ERROR_POINTER_LEFT);
    assert_null(output);

    logger_close();
}

static void test_tape_grows_to_right(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);
    config.tape_size = 2;

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code(">>+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.", &config, &output);

    assert_int_equal(status, BF_OK);
    assert_non_null(output);
    assert_string_equal(output, "A");

    free(output);
    logger_close();
}

static void test_max_steps_error(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);
    config.max_steps = 5;

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("++++++++++", &config, &output);

    assert_int_equal(status, BF_ERROR_MAX_STEPS);
    assert_null(output);

    logger_close();
}

static void test_empty_code_error(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("", &config, &output);

    assert_int_equal(status, BF_ERROR_FILE);
    assert_null(output);

    logger_close();
}

static void test_non_brainfuck_symbols_are_ignored(void **state) {
    (void) state;

    Config config;
    make_test_config(&config);

    logger_open(config.log_file);

    char *output = NULL;
    int status = bf_run_code("text +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.", &config, &output);

    assert_int_equal(status, BF_OK);
    assert_non_null(output);
    assert_string_equal(output, "A");

    free(output);
    logger_close();
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_simple_output_A),
        cmocka_unit_test(test_loop_output_A),
        cmocka_unit_test(test_hello_world),
        cmocka_unit_test(test_unmatched_open_bracket),
        cmocka_unit_test(test_unmatched_close_bracket),
        cmocka_unit_test(test_pointer_left_error),
        cmocka_unit_test(test_tape_grows_to_right),
        cmocka_unit_test(test_max_steps_error),
        cmocka_unit_test(test_empty_code_error),
        cmocka_unit_test(test_non_brainfuck_symbols_are_ignored),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
