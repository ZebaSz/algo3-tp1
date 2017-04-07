#include "AbstractTest.h"
#include "../src/ImprovedBacktrack.h"
#include "../src/Dynamic.h"

#define REPETITIONS 100

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

class DynamicPerfTest : public PerformanceTest {
protected:
    virtual Solver* getSolver() {
        return new Dynamic();
    }
};

TEST_F(BacktrackPerfTest, randOnce) {
    std::vector<int> inputRand = getRandomVectorOfSize(20);
    begin = clock();
    solver->getSolution(inputRand);
    end = clock();
    recordResult();
}

TEST_F(BacktrackPerfTest, randRepeat) {
    std::vector<int> inputRand = getRandomVectorOfSize(10);
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRand);
        end = clock();
        recordResult();
    }
}

TEST_F(ImprovedBacktrackPerfTest, randOnce) {
    std::vector<int> inputRand = getRandomVectorOfSize(20);
    begin = clock();
    solver->getSolution(inputRand);
    end = clock();
    recordResult();
}

TEST_F(ImprovedBacktrackPerfTest, randRepeat) {
    std::vector<int> inputRand = getRandomVectorOfSize(10);
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRand);
        end = clock();
        recordResult();
    }
}

TEST_F(DynamicPerfTest, randOnce) {
    std::vector<int> inputRand = getRandomVectorOfSize(20);
    begin = clock();
    solver->getSolution(inputRand);
    end = clock();
    recordResult();
}

TEST_F(DynamicPerfTest, randRepeat) {
    std::vector<int> inputRand = getRandomVectorOfSize(10);
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRand);
        end = clock();
        recordResult();
    }
}