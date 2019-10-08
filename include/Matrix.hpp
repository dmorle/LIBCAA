#ifndef MATRIX_H
#define MATRIX_H

#include "Tensor.hpp"

namespace LIBCAA {

	typedef int *matrixParams;
	matrixParams createMatrixParams(int m, int n);

	class Matrix : public Tensor
	{
	public:
		Matrix(matrixParams params);
		Matrix(matrixParams params, double val);
		Matrix(matrixParams params, double **data);
		Matrix(matrixParams params, double(*initFunc)());

		// overriding Tensor functions for efficiency
		void setIndex(int i, int j, double val);
		double getAbsIndex(int i, int j);
		double getIndex(int i, int j);

		friend Matrix *getInverse(Matrix *mrx);

		friend Matrix *transpose(Matrix *mrx);

		// TODO: impliment this method
		friend Matrix *getDiagonal(Matrix *mrx);

		friend Matrix *matmul(Matrix *mat1, Matrix *mat2);

	private:
		void scaleRow(int rowNum, double scale);
		void switchRows(int row1, int row2);
		void rowSub(int row1, int row2, double scale);
	};
}

#endif