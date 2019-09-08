#include "MDA.h"
#include <iostream>

using namespace LIBCAA;

int main() {
	MDA<double> arr(getShape(3, 3, 3, 3), 2.0);

	arr.print();

	std::cin.get();
	return 0;
}