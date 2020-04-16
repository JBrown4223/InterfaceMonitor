
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

using namespace std;

typedef enum LOG_LEVEL {
    DEBUG,
    WARNING,
    ERROR,
    CRITICAL
} LOG_LEVEL;

int InitializeLog();
void SetLogLevel(LOG_LEVEL level);
void Log(LOG_LEVEL level, const char *prog, const char *func, int line, const char *message);
void ExitLog(); 

#endif//LOGGER_H
