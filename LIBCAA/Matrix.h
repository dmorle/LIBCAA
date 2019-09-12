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

		// overriding Tensor functions for efficiency
		void setIndex(int i, int j, double val);
		double getAbsIndex(int i, int j);
		double getIndex(int i, int j);

		void scaleRow(int rowNum, double scale);
		void switchRows(int row1, int row2);
	};

}

#endif