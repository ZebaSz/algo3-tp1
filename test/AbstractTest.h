#include <gtest/gtest.h>
#include "../src/Solver.h"

class AbstractTest : public ::testing::Test {
protected:
    Solver* solver;

    std::vector<int> input1;
    std::vector<int> input2;
    std::vector<int> zeroes;

    virtual Solver* getSolver() = 0;

    virtual void SetUp() {
        solver = getSolver();

        int arr1[8] = {0,7,1,2,2,1,5,0};
        input1.clear();
        input1.insert(input1.begin(), arr1, arr1 + 8);

        int arr2[12] = {3,11,0,1,3,5,2,4,1,0,9,3};
        input2.clear();
        input2.insert(input2.begin(), arr2, arr2 + 12);

        int arrZeroes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
        zeroes.clear();
        zeroes.insert(zeroes.begin(), arrZeroes, arrZeroes + 12);
    }

    virtual void TearDown() {
        delete solver;
    }
};