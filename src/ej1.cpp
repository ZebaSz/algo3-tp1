#include <stdio.h>
#include "Backtrack.h"
#include "Utils.h"

int main() {
	printf("%lu\n", Backtrack().getSolution(Utils::getListFromInput()));
    return 0;
}