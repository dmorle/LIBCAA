#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "InitFunc.hpp"

using namespace LIBCAA;

void vectorTesting() {
	Matrix *poly = new Matrix(createMatrixParams(6, 2), createArangeInit<double>());

	poly->print();

	Matrix *derivative = new Matrix(createMatrixParams(6, 6), createDerivativeMatrix<6>());

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