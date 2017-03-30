#include <gtest/gtest.h>
#include "../src/ImprovedBacktrack.h"

class BacktrackTest : public ::testing::Test {
protected:
    Solver* solver;

    std::vector<int> input;

    virtual void SetUp() {
        solver = new ImprovedBacktrack();
    }

    virtual void TearDown() {
        delete solver;
    }
};

TEST_F(BacktrackTest, listWithOptimal) {
    int arr[8] = {0,7,1,2,2,1,5,0};
    input.insert(input.begin(), arr, arr + 8);

    size_t solution = solver->getSolution(input);
    ASSERT_EQ(solution, (size_t)0);
}

TEST_F(BacktrackTest, listWithoutOptimal) {
    int arr[12] = {3,11,0,1,3,5,2,4,1,0,9,3};
    input.insert(input.begin(), arr, arr + 12);

    size_t solution = solver->getSolution(input);
    ASSERT_EQ(solution, (size_t)2);
}

TEST_F(BacktrackTest, listOfZeroes) {
    int arr[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    input.insert(input.begin(), arr, arr + 12);

    size_t solution = solver->getSolution(input);
    ASSERT_EQ(solution, (size_t)input.size() - 2);

    input.insert(input.begin(), arr, arr + 12);
    solution = solver->getSolution(input);
    ASSERT_EQ(solution, (size_t)input.size() - 2);
}