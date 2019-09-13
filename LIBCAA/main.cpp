#include "Matrix.h"
#include "InitFunc.h"
#include <iostream>

using namespace LIBCAA;

void testMemLeak(Tensor *tens, int axisNum, int *axes) {
	Tensor *npTens = tens->collapseAxis(axisNum, axes);
	delete npTens;
}

void tesnorTesting() {
	int rank = 1;
	int dimensions[] = { 3 };

	Tensor *tens1 = new Tensor(rank, dimensions, INIT::arange<double>);
	Tensor *tens2 = new Tensor(rank, dimensions, INIT::arange<double>);

	tens1->print();
	tens2->print();

	Tensor *tens3 = outerProd(tens1, tens2);

	tens3->print();

	/*
	int axisNum = 2;
	int axes[] = { 0, 2, -1 };

	for (int i = 0; i < 100000; i++) {
		testMemLeak(tens, axisNum, axes);
		if (!(i % 10))
			std::cout << i << std::endl;
	}
	*/

	delete tens1;
	delete tens2;
	delete tens3;
}

void matrixInverseTesting() {
	Matrix *mrx = new Matrix(createMatrixParams(3, 3), INIT::uniformDist<double, int, -5, 5>);
	mrx->print();

	Matrix *inv = mrx->getInverse();
	if (inv)
		inv->print();
	else
		std::cout << "Could not find inverse";

	Matrix *result = matmul(mrx, inv);
	result->print();

	delete mrx;
	if (inv)
		delete inv;
	delete result;
}

void matmulTesting() {
	Matrix *mrx1 = new Matrix(createMatrixParams(2, 2), INIT::arange<double>);
	mrx1->print();
	Matrix *mrx2 = new Matrix(createMatrixParams(2, 2), INIT::arange<double>);
	mrx2->print();

	Matrix *result = matmul(mrx1, mrx2);
	result->print();

	delete mrx1;
	delete mrx2;
	delete result;
}

int main() {
	matmulTesting();

	std::cin.get();
	return 0;
}