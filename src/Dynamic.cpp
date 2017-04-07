#include <list>
#include <cstdlib>
#include "Dynamic.h"
#include "Utils.h"

size_t Dynamic::getSolution(const std::vector<int>& list) const {
    state** memory = new state*[list.size() + 1];
    for (size_t i = 0; i <= list.size(); ++i) {
        memory[i] = new state[list.size() + 1];
    }
    state best;
    for (size_t i = 0; i <= list.size(); ++i) {
        for (size_t j = 0; j <= list.size(); ++j) {
            if(i != j) {
                state cur = getSubsolution(list, memory, i, j);
                if(cur.acum < best.acum) {
                    Utils::log(Utils::toString(cur.acum) + " is better than "
                               + Utils::toString(best.acum), DEBUG);
                    best = cur;
                }
            }
        }
    }
    state cur = best;
    std::list<state> lst;
    while(cur.acum != list.size()) {
        lst.push_front(cur);
        cur = memory[cur.prevR][cur.prevB];
    }
    Utils::log("Found answer: " + Utils::itToStr(lst), INFO);

    for (size_t i = 0; i <= list.size(); ++i) {
        delete[] memory[i];
    }
    delete[] memory;
    return best.acum;
}

Dynamic::state Dynamic::getSubsolution(const std::vector<int>& list, Dynamic::state** memory,
                                       size_t r, size_t b) const {
    if(!memory[r][b].built) {
        if (r == list.size() && b == list.size()) {
            memory[r][b] = state(list.size(), list.size(), list.size(), list.size(), list.size());
        } else {
            if(b == list.size() || (r != list.size() && r > b)) {
                // either no blues painted or red was last painted
                size_t prevRed(findPrevRed(list, memory, r, b));
                size_t val = getSubsolution(list, memory, prevRed, b).acum - 1;
                memory[r][b] = state(prevRed, b, r, b, val);
                Utils::log("[" + Utils::toString(prevRed) + "," + Utils::toString(b) + "] should precede ["
                           + Utils::toString(r) + "," + Utils::toString(b) + "]", DEBUG);
            } else {
                // either no reds painted or blue was last painted
                size_t prevBlue(findPrevBlue(list, memory, r, b));
                size_t val = getSubsolution(list, memory, r, prevBlue).acum - 1;
                memory[r][b] = state(r, prevBlue, r, b, val);
                Utils::log("[" + Utils::toString(r) + "," + Utils::toString(prevBlue) + "] should precede ["
                           + Utils::toString(r) + "," + Utils::toString(b) + "]", DEBUG);
            }
        }
    } else {
        Utils::log("Reusing position [" + Utils::toString(r)
                   + "," + Utils::toString(b) + "]", DEBUG);
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
        Utils::log("[PrevRed] " + Utils::toString(prevR)
                   + " should come before " + Utils::toString(r), TRACE);
        Utils::log("[PrevRed] " + Utils::toString(list[prevR])
                   + " should be less than " + Utils::toString(list[r]),
                   TRACE);
    } else {
        Utils::log("[PrevRed] no prev found", TRACE);
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
        Utils::log("[PrevBlue] " + Utils::toString(prevB)
                   + " should come before " + Utils::toString(b), TRACE);
        Utils::log("[PrevBlue] " + Utils::toString(list[prevB])
                   + " should be more than " + Utils::toString(list[b]), TRACE);
    } else {
        Utils::log("[PrevBlue] no prev found", TRACE);
    }
    return prevB;
}
