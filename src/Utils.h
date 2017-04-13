#ifndef ALGO3_TP1_UTILS_H
#define ALGO3_TP1_UTILS_H

#include <iostream>
#include <sstream>
#include <vector>

typedef int logLevel;
enum LOG_LEVEL {TRACE, DEBUG, INFO, WARN, ERROR, OFF};

#define CUR_LOG_LEVEL OFF

namespace Utils {
    void log(logLevel level, const char* format, ...);

    const std::vector<int> getListFromInput();
};


#endif //ALGO3_TP1_UTILS_H
