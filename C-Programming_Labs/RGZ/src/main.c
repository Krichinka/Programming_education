#include "brainfuck.h"
#include "config.h"
#include "logger.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    Config config;
    config_set_defaults(&config);

    if (argc < 2) {
        printf("Usage: %s <program.bf> [config.txt]\n", argv[0]);
        return 1;
    }

    if (argc >= 3) {
        if (!config_load(&config, argv[2])) {
            printf("Warning: config file was not found. Default values will be used.\n");
        }
    }

    if (!logger_open(config.log_file)) {
        printf("Error: cannot open log file: %s\n", config.log_file);
        return 1;
    }

    logger_log(LOG_INFO, "Program started");

    int status = bf_run_file(argv[1], &config);

    if (status != BF_OK) {
        logger_log(LOG_ERROR, bf_status_to_string(status));
        printf("Error: %s\n", bf_status_to_string(status));
        logger_close();
        return 1;
    }

    logger_log(LOG_INFO, "Program finished successfully");
    logger_close();

    return 0;
}