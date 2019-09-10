#ifndef MATRIX_H
#define MATRIX_H

#include "Tensor.h"

namespace LIBCAA {

	typedef int *matrixParams;
	matrixParams createMatrixParams(int m, int n);

	class Matrix : public Tensor
	{
	public:
		Matrix(matrixParams params, double val);
		Matrix(matrixParams params, double **data);
		Matrix(matrixParams params, double(*initFunc)());
		~Matrix();
	};

}

#endif