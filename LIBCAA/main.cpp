#include "MDA.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

int main() {
	int rank = 3;
	int dimensions[] = { 3, 3, 3 };

	MDA<double> arr(rank, dimensions, INIT::arange<double>);

	arr.print();

	int index[] = { 0, 0, 0 };
	std::cout << arr.getIndex(index);

	std::cin.get();
	return 0;
}