#include "Tensor.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

void testMemLeak(Tensor *tens, int axisNum, int *axes) {
	Tensor *npTens = tens->collapseAxis(axisNum, axes);
	delete npTens;
}

int main() {
	int rank = 3;
	int dimensions[] = { 2, 3, 4 };

	Tensor *tens = new Tensor(rank, dimensions, INIT::arange<double>);

	tens->print();

	int axisNum = 2;
	int axes[] = { 0, 2, -1 };

	/*
	for (int i = 0; i < 100000; i++) {
		testMemLeak(tens, axisNum, axes);
		if (!(i % 10))
			std::cout << i << std::endl;
	}
	*/
	
	Tensor *npTens = tens->collapseAxis(axisNum, axes);
	npTens->print();

	delete tens;
	delete npTens;

	std::cin.get();
	return 0;
}