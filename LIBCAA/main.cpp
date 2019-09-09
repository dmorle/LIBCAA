#include "Tensor.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

int main() {
	int rank = 3;
	int dimensions[] = { 2, 3, 4 };

	Tensor tens = Tensor(rank, dimensions, INIT::arange<double>);

	tens.print();

	int axisOrder[] = { 2, 1, 0 };
	Tensor nTens = tens.transpose(axisOrder);

	nTens.print();

	std::cin.get();
	return 0;
}