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

		Matrix *clone();

		// overriding Tensor functions for efficiency
		void setIndex(int i, int j, double val);
		double getAbsIndex(int i, int j);
		double getIndex(int i, int j);

		friend Matrix *add(Matrix *mrx1, Matrix *mrx2);
		friend Matrix *add(Matrix *mrx, double val);
		friend Matrix *add(double val, Matrix *mrx);
		friend Matrix *sub(Matrix *mrx1, Matrix *mrx2);
		friend Matrix *sub(Matrix *mrx, double val);
		friend Matrix *sub(double val, Matrix *mrx);
		friend Matrix *mul(Matrix *mrx1, Matrix *mrx2);
		friend Matrix *mul(Matrix *mrx, double val);
		friend Matrix *mul(double val, Matrix *mrx);
		friend Matrix *div(Matrix *mrx1, Matrix *mrx2);
		friend Matrix *div(Matrix *mrx, double val);
		friend Matrix *div(double val, Matrix *mrx);
		friend Matrix *pow(Matrix *mrx1, Matrix *mrx2);
		friend Matrix *pow(Matrix *mrx, double val);
		friend Matrix *pow(double val, Matrix *mrx);
		friend Matrix *pow(Matrix *mrx, int val);

		friend Matrix *addAcc(int len, Matrix **mrxArr);
		friend Matrix *mulAcc(int len, Matrix **mrxArr);

		friend void iadd(Matrix *mrx1, Matrix *mrx2);
		friend void iadd(Matrix *mrx, double val);
		friend void iadd(double val, Matrix *mrx);
		friend void isub(Matrix *mrx1, Matrix *mrx2);
		friend void isub(Matrix *mrx, double val);
		friend void isub(double val, Matrix *mrx);
		friend void imul(Matrix *mrx1, Matrix *mrx2);
		friend void imul(Matrix *mrx, double val);
		friend void imul(double val, Matrix *mrx);
		friend void idiv(Matrix *mrx1, Matrix *mrx2);
		friend void idiv(Matrix *mrx, double val);
		friend void idiv(double val, Matrix *mrx);
		friend void ipow(Matrix *mrx1, Matrix *mrx2);
		friend void ipow(Matrix *mrx, double val);
		friend void ipow(double val, Matrix *mrx);
		friend void ipow(Matrix *mrx, int val);

		friend Matrix *eq(Matrix *mrx);
		friend Matrix *ne(Matrix *mrx);
		friend Matrix *gt(Matrix *mrx);
		friend Matrix *lt(Matrix *mrx);
		friend Matrix *le(Matrix *mrx);
		friend Matrix *ge(Matrix *mrx);

		friend Matrix *getInverse(Matrix *mrx);
		friend double determinant(Matrix *mrx);

		friend Matrix *transpose(Matrix *mrx);

		// TODO: impliment this method
		friend Matrix *getDiagonal(Matrix *mrx);

		friend Matrix *matmul(Matrix *mat1, Matrix *mat2);


	private:
		void opExcept(Matrix *mrx);
		void scaleRow(int rowNum, double scale);
		void switchRows(int row1, int row2);
		void rowSub(int row1, int row2, double scale);
	};
}

#endif