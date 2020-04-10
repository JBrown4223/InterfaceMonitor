
#include <iostream>

using namespace std;

const char FILENAME[]="../Server/FileLog.txt";

int InitializeLog();
void SetLogLevel(LOG_LEVEL level);
void Log(LOG_LEVEL level, const char *prog, const char *func, int line, const char *message);
void ExitLog();

typedef enum LOG_LEVEL {
    DEBUG,
    WARNING,
    ERROR,
    CRITICAL
} LOG_LEVEL;
