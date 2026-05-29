#include "brainfuck.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *read_file_content(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        logger_log(LOG_ERROR, "Cannot open Brainfuck source file");
        return NULL;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        logger_log(LOG_ERROR, "Cannot seek source file");
        return NULL;
    }

    long size = ftell(file);

    if (size < 0) {
        fclose(file);
        logger_log(LOG_ERROR, "Cannot determine source file size");
        return NULL;
    }

    rewind(file);

    char *content = malloc((size_t)size + 1);

    if (content == NULL) {
        fclose(file);
        logger_log(LOG_ERROR, "Memory allocation error while reading source file");
        return NULL;
    }

    size_t read_size = fread(content, 1, (size_t)size, file);
    content[read_size] = '\0';

    fclose(file);
    return content;
}

static int check_brackets(const char *code) {
    int balance = 0;

    for (int i = 0; code[i] != '\0'; i++) {
        if (code[i] == '[') {
            balance++;
        } else if (code[i] == ']') {
            balance--;

            if (balance < 0) {
                return 0;
            }
        }
    }

    return balance == 0;
}

static int find_matching_forward(const char *code, int position) {
    int depth = 1;

    for (int i = position + 1; code[i] != '\0'; i++) {
        if (code[i] == '[') {
            depth++;
        } else if (code[i] == ']') {
            depth--;

            if (depth == 0) {
                return i;
            }
        }
    }

    return -1;
}

static int find_matching_backward(const char *code, int position) {
    int depth = 1;

    for (int i = position - 1; i >= 0; i--) {
        if (code[i] == ']') {
            depth++;
        } else if (code[i] == '[') {
            depth--;

            if (depth == 0) {
                return i;
            }
        }
    }

    return -1;
}

static int grow_tape(unsigned char **tape, int *tape_size) {
    int new_size = (*tape_size) * 2;

    unsigned char *new_tape = realloc(*tape, (size_t)new_size);

    if (new_tape == NULL) {
        logger_log(LOG_ERROR, "Memory allocation error while growing tape");
        return 0;
    }

    memset(new_tape + *tape_size, 0, (size_t)(new_size - *tape_size));

    *tape = new_tape;
    *tape_size = new_size;

    logger_log(LOG_INFO, "Tape was expanded");

    return 1;
}

static int append_output(char **output, int *output_size, int *output_capacity, char symbol) {
    if (*output_size + 1 >= *output_capacity) {
        int new_capacity = (*output_capacity) * 2;

        char *new_output = realloc(*output, (size_t)new_capacity);

        if (new_output == NULL) {
            logger_log(LOG_ERROR, "Memory allocation error while growing output buffer");
            return 0;
        }

        *output = new_output;
        *output_capacity = new_capacity;
    }

    (*output)[*output_size] = symbol;
    (*output_size)++;
    (*output)[*output_size] = '\0';

    return 1;
}

static void dump_tape_to_file(const char *filename, const unsigned char *tape, int tape_size, int pointer) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        logger_log(LOG_WARNING, "Cannot save tape dump file");
        return;
    }

    fprintf(file, "Tape size: %d\n", tape_size);
    fprintf(file, "Pointer position: %d\n", pointer);
    fprintf(file, "Non-zero cells:\n");

    for (int i = 0; i < tape_size; i++) {
        if (tape[i] != 0) {
            fprintf(file, "[%d] = %u\n", i, tape[i]);
        }
    }

    fclose(file);
    logger_log(LOG_INFO, "Tape state was saved to file");
}

int bf_run_code(const char *code, const Config *config, char **output_result) {
    if (code == NULL || code[0] == '\0') {
        logger_log(LOG_ERROR, "Empty Brainfuck code");
        return BF_ERROR_FILE;
    }

    if (!check_brackets(code)) {
        logger_log(LOG_ERROR, "Incorrect brackets in Brainfuck code");
        return BF_ERROR_BRACKETS;
    }

    int tape_size = config->tape_size;

    if (tape_size <= 0) {
        tape_size = DEFAULT_TAPE_SIZE;
    }

    unsigned char *tape = calloc((size_t)tape_size, sizeof(unsigned char));

    if (tape == NULL) {
        logger_log(LOG_ERROR, "Memory allocation error while creating tape");
        return BF_ERROR_MEMORY;
    }

    int output_capacity = 128;
    int output_size = 0;
    char *output = malloc((size_t)output_capacity);

    if (output == NULL) {
        free(tape);
        logger_log(LOG_ERROR, "Memory allocation error while creating output buffer");
        return BF_ERROR_MEMORY;
    }

    output[0] = '\0';

    int pointer = 0;
    int steps = 0;

    for (int ip = 0; code[ip] != '\0'; ip++) {
        char command = code[ip];

        if (command != '>' && command != '<' && command != '+' && command != '-' &&
            command != '.' && command != ',' && command != '[' && command != ']') {
            continue;
        }

        steps++;

        if (steps > config->max_steps) {
            free(tape);
            free(output);
            logger_log(LOG_ERROR, "Maximum number of steps exceeded");
            return BF_ERROR_MAX_STEPS;
        }

        if (config->debug) {
            printf("DEBUG: ip=%d command=%c pointer=%d cell=%u\n",
                   ip, command, pointer, tape[pointer]);
            getchar();
        }

        switch (command) {
            case '>':
                pointer++;

                if (pointer >= tape_size) {
                    if (!grow_tape(&tape, &tape_size)) {
                        free(tape);
                        free(output);
                        return BF_ERROR_MEMORY;
                    }
                }
                break;

            case '<':
                pointer--;

                if (pointer < 0) {
                    free(tape);
                    free(output);
                    logger_log(LOG_ERROR, "Pointer moved left out of tape");
                    return BF_ERROR_POINTER_LEFT;
                }
                break;

            case '+':
                tape[pointer]++;
                break;

            case '-':
                tape[pointer]--;
                break;

            case '.':
                if (!config->silent) {
                    putchar(tape[pointer]);
                }

                if (!append_output(&output, &output_size, &output_capacity, (char)tape[pointer])) {
                    free(tape);
                    free(output);
                    return BF_ERROR_MEMORY;
                }
                break;

            case ',':
                tape[pointer] = (unsigned char)getchar();
                break;

            case '[':
                if (tape[pointer] == 0) {
                    int jump = find_matching_forward(code, ip);

                    if (jump < 0) {
                        free(tape);
                        free(output);
                        logger_log(LOG_ERROR, "Matching closing bracket was not found");
                        return BF_ERROR_BRACKETS;
                    }

                    ip = jump;
                }
                break;

            case ']':
                if (tape[pointer] != 0) {
                    int jump = find_matching_backward(code, ip);

                    if (jump < 0) {
                        free(tape);
                        free(output);
                        logger_log(LOG_ERROR, "Matching opening bracket was not found");
                        return BF_ERROR_BRACKETS;
                    }

                    ip = jump;
                }
                break;

            default:
                break;
        }
    }

    dump_tape_to_file(config->tape_dump_file, tape, tape_size, pointer);

    if (output_result != NULL) {
        *output_result = output;
    } else {
        free(output);
    }

    free(tape);

    logger_log(LOG_INFO, "Brainfuck code executed successfully");

    return BF_OK;
}

int bf_run_file(const char *filename, const Config *config) {
    char *code = read_file_content(filename);

    if (code == NULL) {
        return BF_ERROR_FILE;
    }

    logger_log(LOG_INFO, "Brainfuck source file opened successfully");

    int status = bf_run_code(code, config, NULL);

    free(code);

    return status;
}

const char *bf_status_to_string(int status) {
    switch (status) {
        case BF_OK:
            return "OK";
        case BF_ERROR_FILE:
            return "File error";
        case BF_ERROR_MEMORY:
            return "Memory allocation error";
        case BF_ERROR_BRACKETS:
            return "Bracket error";
        case BF_ERROR_POINTER_LEFT:
            return "Pointer moved left out of tape";
        case BF_ERROR_MAX_STEPS:
            return "Maximum number of steps exceeded";
        default:
            return "Unknown error";
    }
}