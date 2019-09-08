#include "MDA.h"
#include <iostream>

using namespace LIBCAA;

int main() {
	int rank = 3;
	int dimensions[] = { 3, 3, 3 };
	MDA<double> arr(getShape(rank, dimensions), 2.0);

	arr.print();

	int index[] = { 0, 0, 0 };
	std::cout << arr.getIndex(index);

	std::cin.get();
	return 0;
}