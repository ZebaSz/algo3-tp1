#ifndef ALGO3_TP1_SOLVER_H
#define ALGO3_TP1_SOLVER_H

#include <vector>
#include <cstddef>

class Solver {
public:
    virtual ~Solver() {}
    virtual size_t getSolution(const std::vector<int>&) const = 0;
};


#endif //ALGO3_TP1_SOLVER_H
