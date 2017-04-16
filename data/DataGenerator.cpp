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

#define REPETITIONS 10
#define MAXSIZE 40

std::vector<int> getRandomVectorOfSize(unsigned int size) {
    std::srand(std::time(NULL));
    std::vector<int> randVector;
    for (unsigned int i = 0; i < size; ++i) {
        randVector.push_back(std::rand());
    }
    return randVector;
}

void getData(Solver *solver, const char *name, FILE *data, std::vector<std::vector<int> > &inputs) {
    fprintf(data, "Nombre,Tamaño,Microsegundos\n");
    for (unsigned int i = 0; i < MAXSIZE; ++i) {
        std::vector<int> input = inputs[i];
        printf("Running with size %d for solver %s\n", i, name);
        for (int j = 0; j < REPETITIONS; ++j) {
            auto begin = std::chrono::high_resolution_clock::now();
            solver->getSolution(input);
            auto end = std::chrono::high_resolution_clock::now();
            fprintf(data, "%s,%d,%ld\n", name, i,
                    std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
        }
    }
}

int main() {
    FILE* data;

    std::vector< std::vector <int> > inputs;

    for (unsigned int i = 0; i < MAXSIZE; ++i) {
        inputs.push_back(getRandomVectorOfSize(i));
    }

    remove("data/bt.csv");
    data = fopen("data/bt.csv", "a");
    Backtrack bt;
    getData(&bt, "Backtrack", data, inputs);
    fclose(data);

    remove("data/impbt.csv");
    data = fopen("data/impbt.csv", "a");
    ImprovedBacktrack impbt;
    getData(&impbt, "Backtrack Mejorado", data, inputs);
    fclose(data);

    remove("data/dyn.csv");
    data = fopen("data/dyn.csv", "a");
    Dynamic dyn;
    getData(&dyn, "Programación Dinámica", data, inputs);
    fclose(data);

    return 0;
}
