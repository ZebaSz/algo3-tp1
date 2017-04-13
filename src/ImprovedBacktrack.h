#ifndef ALGO3_TP1_IMPROVED_BACKTRACK_H
#define ALGO3_TP1_IMPROVED_BACKTRACK_H

#include "Backtrack.h"

class ImprovedBacktrack : public Backtrack {
public:
    size_t getSolution(const std::vector<int>&) const;
protected:
    void getSubsolutionWithTrim(const std::vector<int> &,
                                int, int, size_t, size_t, size_t &) const;
};


#endif //ALGO3_TP1_IMPROVED_BACKTRACK_H
