#include <climits>
#include "Backtrack.h"

size_t Backtrack::getSolution(const std::vector<int>& list) const {
    std::list<node> prefix;
    size_t solution = getSubsolution(prefix, list);
    Utils::log("Found best solution: " + std::to_string(solution), LOG_LEVEL::INFO);
    return solution;
}

size_t Backtrack::getSubsolution(std::list<node> &prefix, const std::vector<int> &list) const {
    size_t solution = list.size();
    if(isValidPrefix(prefix)) {
        if(prefix.size() == list.size()) {
            std::list<node>::const_iterator it;
            for (it = prefix.begin(); it != prefix.end(); ++it) {
                if((*it).color != COLORS::NONE) {
                    --solution;
                }
            }
            Utils::log("Found solution with " + std::to_string(solution) + " non-painted elements: \n"
                       + Utils::itToStr(prefix), LOG_LEVEL::DEBUG);
        } else {
            stepForwards(prefix, list, COLORS::RED);
            size_t subsolutionRed = getSubsolution(prefix, list);
            solution = subsolutionRed < solution ? subsolutionRed : solution;
            stepForwards(prefix, list, COLORS::BLUE);
            size_t subsolutionBlue = getSubsolution(prefix, list);
            solution = subsolutionBlue < solution ? subsolutionBlue : solution;
            stepForwards(prefix, list, NONE);
            size_t subsolutionNone = getSubsolution(prefix, list);
            solution = subsolutionNone < solution ? subsolutionNone : solution;
        }
    } else {
        Utils::log("Discarding invalid prefix: " + Utils::itToStr(prefix), LOG_LEVEL::TRACE);
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

bool Backtrack::isValidPrefix(const std::list<node>& prefix) const {
    int lastRed = INT_MIN;
    int lastBlue = INT_MAX;
    std::list<node>::const_iterator it;
    for(it = prefix.begin(); it != prefix.end(); ++it) {
        if((*it).color == RED) {
            if(lastRed < (*it).elem) {
                lastRed = (*it).elem;
            } else {
                return false;
            }
        } else if((*it).color == BLUE) {
            if(lastBlue > (*it).elem) {
                lastBlue = (*it).elem;
            } else {
                return false;
            }
        }
    }
    return true;
}
