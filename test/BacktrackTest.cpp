#include "AbstractTest.h"
#include "../src/Backtrack.h"

class BacktrackTest : public AbstractTest {
protected:
    virtual Solver* getSolver() {
        return new Backtrack();
    }
};

TEST_F(BacktrackTest, listWithOptimal) {
    size_t solution = solver->getSolution(input1);
    ASSERT_EQ(solution, (size_t)0);
}

TEST_F(BacktrackTest, listWithoutOptimal) {
    size_t solution = solver->getSolution(input2);
    ASSERT_EQ(solution, (size_t)2);
}

TEST_F(BacktrackTest, listOfZeroes) {
    size_t solution = solver->getSolution(zeroes);
    ASSERT_EQ(solution, (size_t)zeroes.size() - 2);
}