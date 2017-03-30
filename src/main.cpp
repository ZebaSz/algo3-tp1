#include <iostream>
#include <vector>
#include "ImprovedBacktrack.h"

#define LOG_OFF

int main() {
    int n;
    int cur;

    std::cin >> n;

    std::vector<int> numbers;
    for (int i = 0; i < n; ++i) {
        std::cin >> cur;
        numbers.push_back(cur);
    }
    ImprovedBacktrack solver;
    std::cout << solver.getSolution(numbers);
    return 0;
}