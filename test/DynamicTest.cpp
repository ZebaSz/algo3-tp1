#include "AbstractTest.h"
#include "../src/Dynamic.h"
#include "../src/ImprovedBacktrack.h"

class DynamicTest : public AbstractTest {
protected:
    virtual Solver* getSolver() {
        return new Dynamic();
    }
};

TEST_F(DynamicTest, listWithOptimal) {
    size_t solution = solver->getSolution(input1);
    ASSERT_EQ(solution, (size_t)0);
}

TEST_F(DynamicTest, listWithoutOptimal) {
    size_t solution = solver->getSolution(input2);
    ASSERT_EQ(solution, (size_t)2);
}

TEST_F(DynamicTest, listOfZeroes) {
    size_t solution = solver->getSolution(zeroes);
    ASSERT_EQ(solution, (size_t)zeroes.size() - 2);
}

TEST_F(DynamicTest, listRand) {
    std::vector<int> inputRand = generateRandomVector(10);
    size_t solution = solver->getSolution(inputRand);
    ASSERT_EQ(solution, ImprovedBacktrack().getSolution(inputRand));
}