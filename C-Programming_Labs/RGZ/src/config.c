#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void config_set_defaults(Config *config) {
    config->tape_size = DEFAULT_TAPE_SIZE;
    config->max_steps = DEFAULT_MAX_STEPS;
    config->debug = 0;
    config->silent = 0;

    strcpy(config->log_file, "brainfuck.log");
    strcpy(config->tape_dump_file, "tape_dump.txt");
}

int config_load(Config *config, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        return 0;
    }

    char line[512];

    while (fgets(line, sizeof(line), file) != NULL) {
        char key[256];
        char value[256];

        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        if (sscanf(line, "%255[^=]=%255s", key, value) != 2) {
            continue;
        }

        if (strcmp(key, "TAPE_SIZE") == 0) {
            config->tape_size = atoi(value);
        } else if (strcmp(key, "MAX_STEPS") == 0) {
            config->max_steps = atoi(value);
        } else if (strcmp(key, "DEBUG") == 0) {
            config->debug = atoi(value);
        } else if (strcmp(key, "SILENT") == 0) {
            config->silent = atoi(value);
        } else if (strcmp(key, "LOG_FILE") == 0) {
            strncpy(config->log_file, value, sizeof(config->log_file) - 1);
            config->log_file[sizeof(config->log_file) - 1] = '\0';
        } else if (strcmp(key, "TAPE_DUMP_FILE") == 0) {
            strncpy(config->tape_dump_file, value, sizeof(config->tape_dump_file) - 1);
            config->tape_dump_file[sizeof(config->tape_dump_file) - 1] = '\0';
        }
    }

    fclose(file);
    return 1;
}