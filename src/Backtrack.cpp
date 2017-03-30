#include <climits>
#include "Backtrack.h"

size_t Backtrack::getSolution(const std::vector<int>& list) const {
    std::list<node> prefix;
    size_t solution = getSubsolution(prefix, list, INT_MIN, INT_MAX, 0);
    Utils::log("Found best solution: " + Utils::toString(solution), INFO);
    return solution;
}

size_t Backtrack::getSubsolution(std::list<node> &prefix, const std::vector<int> &list,
                                 int lastRed, int lastBlue, size_t cur) const {
    size_t solution;
    if(prefix.size() == list.size()) {
        solution = cur;
        Utils::log("Found solution with " + Utils::toString(solution) + " non-painted elements: \n"
                   + Utils::itToStr(prefix), DEBUG);
    } else {
        solution = list.size();
        int next = list[prefix.size()];
        if(lastRed < next) {
            stepForwards(prefix, list, RED);
            size_t subsolutionRed = getSubsolution(prefix, list, next, lastBlue, cur);
            solution = subsolutionRed < solution ? subsolutionRed : solution;
        }
        if(lastBlue > next) {
            stepForwards(prefix, list, BLUE);
            size_t subsolutionBlue = getSubsolution(prefix, list, lastRed, next, cur);
            solution = subsolutionBlue < solution ? subsolutionBlue : solution;
        }
        stepForwards(prefix, list, NONE);
        size_t subsolutionNone = getSubsolution(prefix, list, lastRed, lastBlue, cur + 1);
        solution = subsolutionNone < solution ? subsolutionNone : solution;
    }
    stepBackwards(prefix);
    return solution;
}


void Backtrack::stepForwards(std::list<node>& prefix, const std::vector<int>& list, paintColor color) const {
    if(prefix.size() < list.size()) {
        prefix.push_back(node(list[prefix.size()], color));
    }
}

void Backtrack::stepBackwards(std::list<node>& prefix) const {
    if(!prefix.empty()) {
        prefix.pop_back();
    }
}
