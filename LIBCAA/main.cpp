#include "Tensor.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

void checkMemLeak(int rank, int *dimensions) {
	Tensor tens = Tensor(rank, dimensions, INIT::arange<double>);
}

int main() {
	int rank = 3;
	int dimensions[] = { 100, 100, 100 };

	for (int i = 0; i < 1000; i++) {
		checkMemLeak(rank, dimensions);
	}

	std::cout << "done";

	std::cin.get();
	return 0;
}