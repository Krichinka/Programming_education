#ifndef BRAINFUCK_H
#define BRAINFUCK_H

#include "config.h"

typedef enum {
    BF_OK = 0,
    BF_ERROR_FILE,
    BF_ERROR_MEMORY,
    BF_ERROR_BRACKETS,
    BF_ERROR_POINTER_LEFT,
    BF_ERROR_MAX_STEPS
} BrainfuckStatus;

typedef struct {
    unsigned char *tape;
    int tape_size;
    int pointer;
    int steps;
    char *output;
} BrainfuckState;

int bf_run_file(const char *filename, const Config *config);
int bf_run_code(const char *code, const Config *config, char **output_result);
const char *bf_status_to_string(int status);

#endif