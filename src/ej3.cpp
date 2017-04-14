#include <stdio.h>
#include "Dynamic.h"
#include "Utils.h"

int main() {
	printf("%lu\n", Dynamic().getSolution(Utils::getListFromInput()));
    return 0;
}