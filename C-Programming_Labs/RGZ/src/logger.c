#include "logger.h"

static FILE *log_file = NULL;

int logger_open(const char *filename) {
    log_file = fopen(filename, "a");

    if (log_file == NULL) {
        return 0;
    }

    return 1;
}

void logger_close(void) {
    if (log_file != NULL) {
        fclose(log_file);
        log_file = NULL;
    }
}

void logger_log(LogLevel level, const char *message) {
    if (log_file == NULL) {
        return;
    }

    const char *level_text = "INFO";

    if (level == LOG_WARNING) {
        level_text = "WARNING";
    } else if (level == LOG_ERROR) {
        level_text = "ERROR";
    }

    fprintf(log_file, "[%s] %s\n", level_text, message);
    fflush(log_file);
}