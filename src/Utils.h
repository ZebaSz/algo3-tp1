//
// Created by sebastianszperling on 27/03/17.
//

#ifndef ALGO3_TP1_UTILS_H
#define ALGO3_TP1_UTILS_H

#include <iostream>
#include <sstream>

#define CUR_LOG_LEVEL 0

typedef int paintColor;
enum COLORS {RED, BLUE, NONE};

typedef int logLevel;
enum LOG_LEVEL {TRACE, DEBUG, INFO, WARN, ERROR};


class Utils {
public:
    template<typename T>
    static std::string itToStr(const T &iterable) {
        std::stringstream stream;
        stream << "{";
        typename T::const_iterator it = iterable.begin();
        while (it != iterable.end()) {
            stream << (*it);
            ++it;
            if (it != iterable.end()) {
                stream << ",";
            }
        }
        stream << "}";
        return stream.str();
    }

    static void log(std::string message, logLevel level) {
        if (CUR_LOG_LEVEL <= level) {
            std::cout << message << std::endl;
        }
    }

private:
    Utils() {
        // Do not instantiate utils class
    }
};


#endif //ALGO3_TP1_UTILS_H
