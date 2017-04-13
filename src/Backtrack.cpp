#include <climits>
#include "Backtrack.h"

size_t Backtrack::getSolution(const std::vector<int>& list) const {
    size_t solution = getSubsolution(list, INT_MIN, INT_MAX, 0, 0);
    Utils::log(INFO, "Found best solution: %d", solution);
    return solution;
}

size_t Backtrack::getSubsolution(const std::vector<int> &list, int lastRed,
                          int lastBlue, size_t index, size_t cur) const {
    size_t solution;
    if(index >= list.size()) {
        solution = cur;
        Utils::log(DEBUG, "Found solution with %d non-painted elements", solution);
    } else {
        solution = list.size();
        int next = list[index];
        if(lastRed < next) {
            size_t subsolutionRed = getSubsolution(list, next, lastBlue, index + 1, cur);
            solution = subsolutionRed < solution ? subsolutionRed : solution;
        }
        if(lastBlue > next) {
            size_t subsolutionBlue = getSubsolution(list, lastRed, next, index + 1, cur);
            solution = subsolutionBlue < solution ? subsolutionBlue : solution;
        }
        size_t subsolutionNone = getSubsolution(list, lastRed, lastBlue, index + 1, cur + 1);
        solution = subsolutionNone < solution ? subsolutionNone : solution;
    }
    return solution;
}
