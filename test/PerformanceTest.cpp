#include "AbstractTest.h"
#include "../src/ImprovedBacktrack.h"

#define REPETITIONS 500

class PerformanceTest : public AbstractTest {
protected:
    clock_t begin;
    clock_t end;
    clock_t best;

    virtual void SetUp() {
        AbstractTest::SetUp();
        best = 0;
    }

    virtual void recordResult() {
        clock_t last = end - begin;
        if(last < best || best == 0) {
            best = last;
        }
    }

    virtual void TearDown() {
        double time = double(best)/CLOCKS_PER_SEC;
        std::string problem = typeid(*this).name();
        problem = problem.substr(problem.find('_', 0) + 1);
        problem = problem.substr(0, problem.find('_', 0));
        printf("Problem: %s;\tSolver: %s;\tbest time: %f\n\n",
               problem.c_str(), typeid(*solver).name(), time);
        AbstractTest::TearDown();
    }
};

class BacktrackPerfTest : public PerformanceTest {
protected:
    virtual Solver* getSolver() {
        return new Backtrack();
    }
};

class ImprovedBacktrackPerfTest : public PerformanceTest {
protected:
    virtual Solver* getSolver() {
        return new ImprovedBacktrack();
    }
};

TEST_F(BacktrackPerfTest, listWithOptimal) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(input1);
        end = clock();
        recordResult();
    }
}

TEST_F(BacktrackPerfTest, listWithoutOptimal) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(input2);
        end = clock();
        recordResult();
    }
}

TEST_F(BacktrackPerfTest, listOfZeroes) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(zeroes);
        end = clock();
        recordResult();
    }
}

TEST_F(ImprovedBacktrackPerfTest, listWithOptimal) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(input1);
        end = clock();
        recordResult();
    }
}

TEST_F(ImprovedBacktrackPerfTest, listWithoutOptimal) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(input2);
        end = clock();
        recordResult();
    }
}

TEST_F(ImprovedBacktrackPerfTest, listOfZeroes) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(zeroes);
        end = clock();
        recordResult();
    }
}