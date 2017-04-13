#include <climits>
#include "ImprovedBacktrack.h"

size_t ImprovedBacktrack::getSolution(const std::vector<int>& list) const {
    size_t best = list.size();
    getSubsolutionWithTrim(list, INT_MIN, INT_MAX, 0, 0, best);
    Utils::log(INFO, "Found best solution: %d", best);
    return best;
}

void ImprovedBacktrack::getSubsolutionWithTrim(const std::vector<int> &list,
                                               int lastRed, int lastBlue, size_t index,
                                               size_t cur, size_t &best) const {
    if(index >= list.size()) {
        if(cur < best) {
            Utils::log(DEBUG, "Found a better solution with %d non-painted elements", cur);
            best = cur;
        }
    } else if(cur <= best) {
        int next = list[index];
        if(lastRed < next) {
            getSubsolutionWithTrim(list, next, lastBlue, index + 1, cur, best);
        }
        if(best == 0) {
            Utils::log(INFO, "Found OPTIMAL solution; trimming");
        } else {
            if(lastBlue > next) {
                getSubsolutionWithTrim(list, lastRed, next, index + 1, cur, best);
            }
            if (best == 0) {
                Utils::log(INFO, "Found OPTIMAL solution; trimming");
            } else {
                getSubsolutionWithTrim(list, lastRed, lastBlue, index + 1, cur + 1, best);
            }
        }
    } else {
        Utils::log(TRACE, "Prefix too long; trimming");
    }
}