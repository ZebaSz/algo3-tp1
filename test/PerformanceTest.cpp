#include "AbstractTest.h"
#include "../src/ImprovedBacktrack.h"
#include "../src/Dynamic.h"

#define REPETITIONS 100

class PerformanceTest : public AbstractTest {
protected:
    clock_t begin;
    clock_t end;
    clock_t best;

    std::vector<int> inputRandBig;
    std::vector<int> inputRandSmall;

    virtual void SetUp() {
        AbstractTest::SetUp();
        best = 0;
        inputRandBig = getRandomVectorOfSize(40);
        inputRandSmall = getRandomVectorOfSize(10);
    }

    virtual void recordResult() {
        clock_t last = end - begin;
        if(last < best || best == 0) {
            best = last;
        }
    }

    virtual void printResult() {
        double time = double(best)/CLOCKS_PER_SEC;
        std::string problem = typeid(*this).name();
        problem = problem.substr(problem.find('_', 0) + 1);
        problem = problem.substr(0, problem.find('_', 0));
        printf("Problem: %s;\tSolver: %s;\tbest time: %f\n\n",
               problem.c_str(), typeid(*solver).name(), time);
    }

    virtual void TearDown() {
        printResult();
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
    begin = clock();
    solver->getSolution(inputRandBig);
    end = clock();
    recordResult();
}

TEST_F(BacktrackPerfTest, randRepeat) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRandSmall);
        end = clock();
        recordResult();
    }
}

TEST_F(ImprovedBacktrackPerfTest, randOnce) {
    begin = clock();
    solver->getSolution(inputRandBig);
    end = clock();
    recordResult();
}

TEST_F(ImprovedBacktrackPerfTest, randRepeat) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRandSmall);
        end = clock();
        recordResult();
    }
}

TEST_F(DynamicPerfTest, randOnce) {;
    begin = clock();
    solver->getSolution(inputRandBig);
    end = clock();
    recordResult();
}

TEST_F(DynamicPerfTest, randRepeat) {
    for (int i = 0; i < REPETITIONS; ++i) {
        begin = clock();
        solver->getSolution(inputRandSmall);
        end = clock();
        recordResult();
    }
}

TEST_F(BacktrackPerfTest, randOnceAll) {
    begin = clock();
    size_t solutionBacktrack = solver->getSolution(inputRandBig);
    end = clock();
    recordResult();
    printResult();
    delete solver;
    solver = new ImprovedBacktrack();
    begin = clock();
    size_t solutionImpBtrack = solver->getSolution(inputRandBig);
    end = clock();
    recordResult();
    printResult();
    delete solver;
    solver = new Dynamic();
    begin = clock();
    size_t solutionDynamic = solver->getSolution(inputRandBig);
    end = clock();
    recordResult();

    ASSERT_EQ(solutionBacktrack, solutionImpBtrack);
    ASSERT_EQ(solutionBacktrack, solutionDynamic);
}