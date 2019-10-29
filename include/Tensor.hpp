#ifndef TENSOR_H
#define TENSOR_H

#include "MDA.hpp"

namespace LIBCAA {

	int **createAxisPairs(int axisNum, int *axis1, int *axis2);

	class Tensor : public MDA<double>
	{
	public:

		friend class Factory;

		Tensor *clone();

		friend Tensor *add(Tensor *tens1, Tensor *tens2);
		friend Tensor *add(Tensor *tens, double val);
		friend Tensor *add(double val, Tensor *tens);
		friend Tensor *sub(Tensor *tens1, Tensor *tens2);
		friend Tensor *sub(Tensor *tens, double val);
		friend Tensor *sub(double val, Tensor *tens);
		friend Tensor *mul(Tensor *tens1, Tensor *tens2);
		friend Tensor *mul(Tensor *tens, double val);
		friend Tensor *mul(double val, Tensor *tens);
		friend Tensor *div(Tensor *tens1, Tensor *tens2);
		friend Tensor *div(Tensor *tens, double val);
		friend Tensor *div(double val, Tensor *tens);
		friend Tensor *pow(Tensor *tens1, Tensor *tens2);
		friend Tensor *pow(Tensor *tens, double val);
		friend Tensor *pow(double val, Tensor *tens);
		friend Tensor *pow(Tensor *tens, int val);

		friend Tensor *addAcc(int len, Tensor **tensArr);
		friend Tensor *mulAcc(int len, Tensor **tensArr);

		friend void iadd(Tensor *tens1, Tensor *tens2);
		friend void iadd(Tensor *tens, double val);
		friend void iadd(double val, Tensor *tens);
		friend void isub(Tensor *tens1, Tensor *tens2);
		friend void isub(Tensor *tens, double val);
		friend void isub(double val, Tensor *tens);
		friend void imul(Tensor *tens1, Tensor *tens2);
		friend void imul(Tensor *tens, double val);
		friend void imul(double val, Tensor *tens);
		friend void idiv(Tensor *tens1, Tensor *tens2);
		friend void idiv(Tensor *tens, double val);
		friend void idiv(double val, Tensor *tens);
		friend void ipow(Tensor *tens1, Tensor *tens2);
		friend void ipow(Tensor *tens, double val);
		friend void ipow(double val, Tensor *tens);
		friend void ipow(Tensor *tens, int val);

		friend Tensor *eq(Tensor *tens);
		friend Tensor *ne(Tensor *tens);
		friend Tensor *gt(Tensor *tens);
		friend Tensor *lt(Tensor *tens);
		friend Tensor *le(Tensor *tens);
		friend Tensor *ge(Tensor *tens);

		friend Tensor *transpose(Tensor *tens, int *axisOrder);
		friend Tensor *collapseAxis(Tensor *tens, int axisNum, int *axes);

		friend Tensor *applyFunc(Tensor *tens, double(*func)(double));

		friend Tensor *outerProd(Tensor *tens1, Tensor *tens2);
		friend double innerProd(Tensor *tens1, Tensor *tens2);
		friend Tensor *tensorDot(Tensor *tens1, Tensor *tens2, int axisNum, int **axisPairs);

	protected:

		// all MDA constuctors are transferable to Tensor
		Tensor(int rank, int *dimensions);
		Tensor(int rank, int *dimensions, int *strides);
		Tensor(int rank, int *dimensions, double val);

		// MDA deconstructor is transferable to Tensor
		~Tensor();

		// checks if a pointwise operation can be performed
		// throws shapeEx() or initEx()
		void opExcept(Tensor *pTens);
		void opExcept(Tensor *pTens, bool checkType);
	};

	Tensor *add(Tensor *tens1, Tensor *tens2);
	Tensor *add(Tensor *tens, double val);
	Tensor *add(double val, Tensor *tens);
	Tensor *sub(Tensor *tens1, Tensor *tens2);
	Tensor *sub(Tensor *tens, double val);
	Tensor *sub(double val, Tensor *tens);
	Tensor *mul(Tensor *tens1, Tensor *tens2);
	Tensor *mul(Tensor *tens, double val);
	Tensor *mul(double val, Tensor *tens);
	Tensor *div(Tensor *tens1, Tensor *tens2);
	Tensor *div(Tensor *tens, double val);
	Tensor *div(double val, Tensor *tens);
	Tensor *pow(Tensor *tens1, Tensor *tens2);
	Tensor *pow(Tensor *tens, double val);
	Tensor *pow(double val, Tensor *tens);
	Tensor *pow(Tensor *tens, int val);

	Tensor *addAcc(int len, Tensor **tensArr);
	Tensor *mulAcc(int len, Tensor **tensArr);

	void iadd(Tensor *tens1, Tensor *tens2);
	void iadd(Tensor *tens, double val);
	void iadd(double val, Tensor *tens);
	void isub(Tensor *tens1, Tensor *tens2);
	void isub(Tensor *tens, double val);
	void isub(double val, Tensor *tens);
	void imul(Tensor *tens1, Tensor *tens2);
	void imul(Tensor *tens, double val);
	void imul(double val, Tensor *tens);
	void idiv(Tensor *tens1, Tensor *tens2);
	void idiv(Tensor *tens, double val);
	void idiv(double val, Tensor *tens);
	void ipow(Tensor *tens1, Tensor *tens2);
	void ipow(Tensor *tens, double val);
	void ipow(double val, Tensor *tens);
	void ipow(Tensor *tens, int val);

	Tensor *eq(Tensor *tens);
	Tensor *ne(Tensor *tens);
	Tensor *gt(Tensor *tens);
	Tensor *lt(Tensor *tens);
	Tensor *le(Tensor *tens);
	Tensor *ge(Tensor *tens);

	Tensor *transpose(Tensor *tens, int *axisOrder);
	Tensor *collapseAxis(Tensor *tens, int axisNum, int *axes);

	Tensor *applyFunc(Tensor *tens, double(*func)(double));

	Tensor *outerProd(Tensor *tens1, Tensor *tens2);
	double innerProd(Tensor *tens1, Tensor *tens2);
	Tensor *tensorDot(Tensor *tens1, Tensor *tens2, int axisNum, int **axisPairs);

}

#endif // !TENSOR_H