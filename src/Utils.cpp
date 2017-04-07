#include "Utils.h"

namespace Utils {
    void log(std::string message, logLevel level) {
        if (CUR_LOG_LEVEL <= level) {
            std::cout << message << std::endl;
        }
    }

    const std::vector<int> getListFromInput() {
        int n;
        int cur;

        std::cin >> n;

        std::vector<int> numbers;
        for (int i = 0; i < n; ++i) {
            std::cin >> cur;
            numbers.push_back(cur);
        }
        return numbers;
    }
}