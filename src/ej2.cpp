#include <stdio.h>
#include "ImprovedBacktrack.h"
#include "Utils.h"

int main() {
	printf("%lu\n", ImprovedBacktrack().getSolution(Utils::getListFromInput()));
    return 0;
}