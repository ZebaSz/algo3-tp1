#include <list>
#include <cstdlib>
#include "Dynamic.h"
#include "Utils.h"

size_t Dynamic::getSolution(const std::vector<int>& list) const {
    state** memory = new state*[list.size() + 1];
    for (size_t i = 0; i <= list.size(); ++i) {
        memory[i] = new state[list.size() + 1];
    }
    size_t best = list.size();
    for (size_t i = 0; i <= list.size(); ++i) {
        for (size_t j = 0; j <= list.size(); ++j) {
            if(i != j) {
                state cur = getSubsolution(list, memory, i, j);
                if(cur.acum < best) {
                    Utils::log(DEBUG, "%d is better than %d", cur.acum, best);
                    best = cur.acum;
                }
            }
        }
    }
    Utils::log(INFO, "Found best solution: %d", best);

    for (size_t i = 0; i <= list.size(); ++i) {
        delete[] memory[i];
    }
    delete[] memory;
    return best;
}

Dynamic::state Dynamic::getSubsolution(const std::vector<int>& list, Dynamic::state** memory,
                                       size_t r, size_t b) const {
    if(!memory[r][b].built) {
        if (r == list.size() && b == list.size()) {
            memory[r][b] = state(list.size());
        } else {
            if(b == list.size() || (r != list.size() && r > b)) {
                // either no blues painted or red was last painted
                size_t prevRed(findPrevRed(list, memory, r, b));
                size_t val = getSubsolution(list, memory, prevRed, b).acum - 1;
                memory[r][b] = state(val);
                Utils::log(DEBUG, "[%d,%d] should precede [%d,%d]", prevRed, b, r, b);
            } else {
                // either no reds painted or blue was last painted
                size_t prevBlue(findPrevBlue(list, memory, r, b));
                size_t val = getSubsolution(list, memory, r, prevBlue).acum - 1;
                memory[r][b] = state(val);
                Utils::log(DEBUG, "[%d,%d] should precede [%d,%d]", r, prevBlue, r, b);
            }
        }
    } else {
        Utils::log(DEBUG, "Reusing position [%d,%d]", r, b);
    }
    return memory[r][b];
}

size_t Dynamic::findPrevRed(const std::vector<int>& list, state** memory,
                            size_t r, size_t b) const {
    size_t prevR = list.size();
    size_t bestAcum = list.size();
    for (size_t i = 0; i < r; ++i) {
        if(i != b && list[i] < list[r] && getSubsolution(list, memory, i, b).acum <= bestAcum) {
            prevR = i;
            bestAcum = getSubsolution(list, memory, i, b).acum;
        }
    }
    if(prevR < list.size()) {
        Utils::log(TRACE, "[PrevRed] %d should come before %d", prevR, r);
        Utils::log(TRACE, "[PrevRed] %d should be less than %d", list[prevR], list[r]);
    } else {
        Utils::log(TRACE, "[PrevRed] no prev found");
    }
    return prevR;
}

size_t Dynamic::findPrevBlue(const std::vector<int>& list, state** memory,
                             size_t r, size_t b) const {
    size_t prevB = list.size();
    size_t bestAcum = list.size();
    for (size_t i = 0; i < b; ++i) {
        if(i != r && list[i] > list[b] && getSubsolution(list, memory, r, i).acum <= bestAcum) {
            prevB = i;
            bestAcum = getSubsolution(list, memory, r, i).acum;
        }
    }
    if(prevB < list.size()) {
        Utils::log(TRACE, "[PrevBlue] %d should come before %d", prevB, b);
        Utils::log(TRACE, "[PrevBlue] %d should be more than %d", list[prevB], list[b]);
    } else {
        Utils::log(TRACE, "[PrevBlue] no prev found");
    }
    return prevB;
}
