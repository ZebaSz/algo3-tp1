#include "AbstractTest.h"
#include "../src/ImprovedBacktrack.h"

class ImprovedBacktrackTest : public AbstractTest {
protected:
    virtual Solver* getSolver() {
        return new ImprovedBacktrack();
    }
};

TEST_F(ImprovedBacktrackTest, listWithOptimal) {
    size_t solution = solver->getSolution(input1);
    ASSERT_EQ(solution, (size_t)0);
}

TEST_F(ImprovedBacktrackTest, listWithoutOptimal) {
    size_t solution = solver->getSolution(input2);
    ASSERT_EQ(solution, (size_t)2);
}

TEST_F(ImprovedBacktrackTest, listOfZeroes) {
    size_t solution = solver->getSolution(zeroes);
    ASSERT_EQ(solution, (size_t)zeroes.size() - 2);
}