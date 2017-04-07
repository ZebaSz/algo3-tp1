#ifndef ALGO3_TP1_DYNAMIC_H
#define ALGO3_TP1_DYNAMIC_H

#include <ostream>
#include <climits>
#include "Solver.h"

class Dynamic : public Solver {
public:
    size_t getSolution(const std::vector<int>&) const;
private:
    struct state {
        state() : prevR(0), prevB(0), thisR(0), thisB(0), acum(ULONG_MAX), built(false) {}
        state(size_t pR, size_t pB, size_t tR, size_t tB, size_t n)
                : prevR(pR), prevB(pB), thisR(tR), thisB(tB), acum(n), built(true) {}

        size_t prevR, prevB;
        size_t thisR, thisB;
        size_t acum;
        bool built;

        friend std::ostream& operator<<(std::ostream& os, const state& s) {
            return os << "{[" << s.thisR << "," << s.thisB << "], " << s.acum << "}";
        }
    };

    state getSubsolution(const std::vector<int>&, state**, size_t, size_t) const;
    size_t findPrevRed(const std::vector<int>&, state**, size_t, size_t) const;
    size_t findPrevBlue(const std::vector<int>&, state**, size_t, size_t) const;
};


#endif //ALGO3_TP1_DYNAMIC_H
