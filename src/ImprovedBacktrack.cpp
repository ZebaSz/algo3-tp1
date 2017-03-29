#include <climits>
#include "ImprovedBacktrack.h"

size_t ImprovedBacktrack::getSolution(const std::vector<int>& list) const {
    std::list<node> prefix;
    size_t best = list.size();
    size_t solution = getSubsolutionWithTrim(prefix, list, 0, best);
    Utils::log("Found best solution: " + Utils::toString(solution), INFO);
    return solution;
}

size_t ImprovedBacktrack::getSubsolutionWithTrim(std::list<node> &prefix,
                                                 const std::vector<int> &list,
                                                 size_t cur, size_t& best) const {
    size_t solution = list.size();
    if(isValidPrefix(prefix)) {
        if(prefix.size() == list.size()) {
            solution = cur;
            if(solution < best) {
                Utils::log("Found a better solution with " + Utils::toString(solution) + " non-painted elements: \n"
                           + Utils::itToStr(prefix), DEBUG);
                best = solution;
            }
        } else if(cur <= best) {
            stepForwards(prefix, list, RED);
            size_t subsolutionRed = getSubsolutionWithTrim(prefix, list, cur, best);
            solution = subsolutionRed < solution ? subsolutionRed : solution;
            if(solution == 0) {
                Utils::log("Found OPTIMAL solution; trimming", INFO);
            } else {
                stepForwards(prefix, list, BLUE);
                size_t subsolutionBlue = getSubsolutionWithTrim(prefix, list, cur, best);
                solution = subsolutionBlue < solution ? subsolutionBlue : solution;
                if (solution == 0) {
                    Utils::log("Found OPTIMAL solution; trimming", INFO);
                } else {
                    stepForwards(prefix, list, NONE);
                    size_t subsolutionNone = getSubsolutionWithTrim(prefix, list, cur + 1, best);
                    solution = subsolutionNone < solution ? subsolutionNone : solution;
                }
            }
        } else {
            Utils::log("Discarding long prefix: " + Utils::itToStr(prefix), TRACE);
        }
    } else {
        Utils::log("Discarding invalid prefix: " + Utils::itToStr(prefix), TRACE);
    }
    stepBackwards(prefix);
    return solution;
}