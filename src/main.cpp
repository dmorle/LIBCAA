#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "InitFunc.hpp"

using namespace LIBCAA;

void vectorTesting() {
	int size = 6;
	Matrix *poly = new Matrix(createMatrixParams(6, 2), createArangeInit());

	poly->print();

	Matrix *derivative = new Matrix(createMatrixParams(size, size), createDerivativeMatrix(size));

	derivative->print();

	Matrix *prime = matmul(derivative, poly);

	prime->print();

    delete poly;
	delete derivative;
	delete prime;
}

int main() {
	vectorTesting();
	return 0;
}