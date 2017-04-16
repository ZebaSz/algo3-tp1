#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <chrono>
#include "../src/Solver.h"
#include "../src/Backtrack.h"
#include "../src/ImprovedBacktrack.h"
#include "../src/Dynamic.h"

#define REPETITIONS 500
#define MAXSIZE 500

std::vector<int> getRandomVectorOfSize(unsigned int size) {
    std::srand(std::time(NULL));
    std::vector<int> randVector;
    for (unsigned int i = 0; i < size; ++i) {
        randVector.push_back(std::rand());
    }
    return randVector;
}

std::vector<int> getIncreasingVector(unsigned int size) {
    std::srand(std::time(NULL));
    std::vector<int> randVector;
    for (unsigned int i = 0; i < size; ++i) {
        randVector.push_back(i);
    }
    return randVector;
}


void getData(Solver *solver, const char *name, FILE *data, std::vector<std::vector<int> > &inputs) {
    fprintf(data, "Nombre,Tamaño,Nanosegundos\n");
    for (unsigned int i = 0; i < MAXSIZE; ++i) {
        printf("Running with size %d for solver %s\n", i , name);
        long best = -1;
        for (int j = 0; j < REPETITIONS; ++j) {
            auto begin = std::chrono::high_resolution_clock::now();
            solver->getSolution(inputs[i]);
            auto end = std::chrono::high_resolution_clock::now();
            if(best == -1 || best > std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()) {
                best = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            }
        }
        fprintf(data, "%s,%d,%ld\n", name, i, best);
    }
}

int main() {
    FILE* data;

    std::vector< std::vector <int> > inputs;

    for (unsigned int i = 0; i < MAXSIZE; ++i) {
        inputs.push_back(getIncreasingVector(i));
    }
    /*
    remove("bt.csv");
    data = fopen("bt.csv", "a");
    Backtrack bt;
    getData(&bt, "Backtrack", data, inputs);
    fclose(data);*/

    remove("impbt-inc.csv");
    data = fopen("impbt-inc.csv", "a");
    ImprovedBacktrack impbt;
    getData(&impbt, "Backtrack Mejorado", data, inputs);
    fclose(data);
/*
    remove("dyn-inc.csv");
    data = fopen("dyn-inc.csv", "a");
    Dynamic dyn;
    getData(&dyn, "Programación Dinámica", data, inputs);
    fclose(data);*/

    return 0;
}
