#ifndef ALGO3_TP1_BACKTRACK_H
#define ALGO3_TP1_BACKTRACK_H

#include "Solver.h"

class Backtrack : public Solver {
public:
    size_t getSolution(const std::vector<int>&) const;
protected:
    size_t getSubsolution(const std::vector<int>&,
                          int, int, size_t, size_t) const;
};


#endif //ALGO3_TP1_BACKTRACK_H
