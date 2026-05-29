#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

int logger_open(const char *filename);
void logger_close(void);
void logger_log(LogLevel level, const char *message);

#endif