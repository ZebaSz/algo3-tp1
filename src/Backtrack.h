#ifndef ALGO3_TP1_BACKTRACK_H
#define ALGO3_TP1_BACKTRACK_H

#include "Solver.h"
#include "Utils.h"
#include <list>

class Backtrack : public Solver {
public:
    size_t getSolution(const std::vector<int>&) const;
protected:
    struct node {
        node(const node& n) : elem(n.elem), color(n.color) {}
        node(const int e, paintColor c) : elem(e), color(c) {}

        friend std::ostream& operator<<(std::ostream& os, const node& n) {
            os << "(" << n.elem << "-";
            if(n.color == RED) {
                os << "R";
            } else if(n.color == BLUE) {
                os << "B";
            } else {
                os << "N";
            }
            os << ")";
            return os;
        }

        const int elem;
        paintColor color;
    };

    virtual size_t getSubsolution(std::list<node> &prefix, const std::vector<int> &list) const;
    void stepForwards(std::list<node>&, const std::vector<int>&, paintColor) const;
    void stepBackwards(std::list<node>&) const;
    bool isValidPrefix(const std::list<node>&) const;
};


#endif //ALGO3_TP1_BACKTRACK_H
