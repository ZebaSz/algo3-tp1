#ifndef ALGO3_TP1_IMPROVED_BACKTRACK_H
#define ALGO3_TP1_IMPROVED_BACKTRACK_H

#include "Backtrack.h"

class ImprovedBacktrack : public Backtrack {
public:
    size_t getSolution(const std::vector<int>&) const;
protected:
    size_t getSubsolutionWithTrim(std::list<node>&, const std::vector<int>&, size_t, size_t&) const;
};


#endif //ALGO3_TP1_IMPROVED_BACKTRACK_H
