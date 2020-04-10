
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

using namespace std;

const char FILENAME[]="../Server/LogFile.txt";

typedef enum LOG_LEVEL {
    DEBUG,
    WARNING,
    ERROR,
    CRITICAL
} LOG_LEVEL;

class Logger {
    private:
        
    public:
       int InitializeLog();
       void SetLogLevel(LOG_LEVEL level);
       void Log(LOG_LEVEL level, const char *prog, const char *func, int line, const char *message);
       void ExitLog();
};

#endif//LOGGER_H
