#include "Tensor.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

int main() {
	int rank = 2;
	int dimensions[] = { 2, 2 };

	Tensor tens = Tensor(rank, dimensions, INIT::arange<double>);

	tens.print();

	int axisOrder[] = { 1, 0 };
	Tensor nTens = tens.transpose(axisOrder);

	nTens.print();

	std::cin.get();
	return 0;
}