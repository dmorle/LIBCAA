#ifndef MATRIX_H
#define MATRIX_H

#include "Tensor.hpp"

namespace LIBCAA {

	class Vector;
	class Matrix;

	// Matrix-Vector friend functions go here

	// solves Mx=b
	Vector *linearSystem(Matrix *M, Vector *b);

	// solves mrx * vec
	Vector *matmul(Matrix *mrx, Vector *vec);

	// end of Matrix-Vector friend functions


	class Matrix : public Tensor
	{
	public:

		friend class Factory;

		Matrix *clone();

		// overriding Tensor functions for efficiency
		void setAbsIndex(int i, int j, double val);
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

		friend Matrix *matmul(Matrix *mrx1, Matrix *mrx2);
		friend Vector *matmul(Matrix *mrx, Vector *vec);

	protected:
	
		Matrix(int *dimensions);
		Matrix(int *dimensions, double val);

		void opExcept(Matrix *mrx);
		void scaleRow(int rowNum, double scale);
		void switchRows(int row1, int row2);
		void rowSub(int row1, int row2, double scale);
	};

	Matrix *add(Matrix *mrx1, Matrix *mrx2);
	Matrix *add(Matrix *mrx, double val);
	Matrix *add(double val, Matrix *mrx);
	Matrix *sub(Matrix *mrx1, Matrix *mrx2);
	Matrix *sub(Matrix *mrx, double val);
	Matrix *sub(double val, Matrix *mrx);
	Matrix *mul(Matrix *mrx1, Matrix *mrx2);
	Matrix *mul(Matrix *mrx, double val);
	Matrix *mul(double val, Matrix *mrx);
	Matrix *div(Matrix *mrx1, Matrix *mrx2);
	Matrix *div(Matrix *mrx, double val);
	Matrix *div(double val, Matrix *mrx);
	Matrix *pow(Matrix *mrx1, Matrix *mrx2);
	Matrix *pow(Matrix *mrx, double val);
	Matrix *pow(double val, Matrix *mrx);
	Matrix *pow(Matrix *mrx, int val);

	Matrix *addAcc(int len, Matrix **mrxArr);
	Matrix *mulAcc(int len, Matrix **mrxArr);

	void iadd(Matrix *mrx1, Matrix *mrx2);
	void iadd(Matrix *mrx, double val);
	void iadd(double val, Matrix *mrx);
	void isub(Matrix *mrx1, Matrix *mrx2);
	void isub(Matrix *mrx, double val);
	void isub(double val, Matrix *mrx);
	void imul(Matrix *mrx1, Matrix *mrx2);
	void imul(Matrix *mrx, double val);
	void imul(double val, Matrix *mrx);
	void idiv(Matrix *mrx1, Matrix *mrx2);
	void idiv(Matrix *mrx, double val);
	void idiv(double val, Matrix *mrx);
	void ipow(Matrix *mrx1, Matrix *mrx2);
	void ipow(Matrix *mrx, double val);
	void ipow(double val, Matrix *mrx);
	void ipow(Matrix *mrx, int val);

	Matrix *eq(Matrix *mrx);
	Matrix *ne(Matrix *mrx);
	Matrix *gt(Matrix *mrx);
	Matrix *lt(Matrix *mrx);
	Matrix *le(Matrix *mrx);
	Matrix *ge(Matrix *mrx);

	Matrix *getInverse(Matrix *mrx);
	double determinant(Matrix *mrx);

	Matrix *transpose(Matrix *mrx);

	Matrix *getDiagonal(Matrix *mrx);

	Matrix *matmul(Matrix *mrx1, Matrix *mrx2);
	Vector *matmul(Matrix *mrx, Vector *vec);
	
}

#include "Vector.hpp"

#endif