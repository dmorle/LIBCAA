#ifndef TENSOR_H
#define TENSOR_H

#include "MDA.hpp"

namespace LIBCAA {

	enum STDFUNC {
		SIGMOID,	// 1/(1+e^-x)
		SIGMOID1,	// 1/(1-sigmoid(x))
		RELU,		// max(0, x)
		RELU1,		// if x > 0:1 else:0 
		SQUARE,		// x^2
		SQRT,		// x^(1/2)
		EXP,		// e^x
		LN,			// ln(x)
		SIN,		// sin(x)
		COS,		// cos(x)
		TAN,		// tan(x)
		SINH,		// sinh(x)
		COSH,		// cosh(x)
		TANH		// tanh(x)
	};

	int **createAxisPairs(int axisNum, int *axis1, int *axis2);

	class Tensor : public MDA<double>
	{
	public:

		// all MDA constuctors are transferable to Tensor
		Tensor(int rank, int *dimensions);
		Tensor(int rank, int *dimensions, int *strides);
		Tensor(int rank, int *dimensions, double val);
		Tensor(int rank, int *dimensions, double(*initFunc)());
		Tensor(int rank, int *dimensions, double *data);

		// MDA deconstructor is transferable to Tensor
		~Tensor();

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
		friend Tensor *applyFunc(Tensor *tens, STDFUNC func);

		friend Tensor *outerProd(Tensor *tens1, Tensor *tens2);
		friend double innerProd(Tensor *tens1, Tensor *tens2);
		friend Tensor *tensorDot(Tensor *tens1, Tensor *tens2, int axisNum, int **axisPairs);

	protected:
		// checks if a pointwise operation can be performed
		// throws shapeEx() or initEx()
		void opExcept(Tensor *pTens);
		void opExcept(Tensor *pTens, bool checkType);
	};

}

#endif // !TENSOR_H