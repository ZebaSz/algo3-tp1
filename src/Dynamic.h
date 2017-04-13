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
        state() : acum(0), built(false) {}
        state(size_t n) : acum(n), built(true) {}

        size_t acum;
        bool built;
    };

    state getSubsolution(const std::vector<int>&, state**, size_t, size_t) const;
    size_t findPrevRed(const std::vector<int>&, state**, size_t, size_t) const;
    size_t findPrevBlue(const std::vector<int>&, state**, size_t, size_t) const;
};


#endif //ALGO3_TP1_DYNAMIC_H
