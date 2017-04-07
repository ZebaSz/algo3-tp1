#include "Utils.h"

namespace Utils {
    void log(std::string message, logLevel level) {
        if (CUR_LOG_LEVEL <= level) {
            std::cout << message << std::endl;
        }
    }
}