#ifndef TENSOR_H
#define TENSOR_H

#include "MDA.h"

namespace LIBCAA {


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

		Tensor *operator + (Tensor *tens);
		Tensor *operator + (double val);
		Tensor *operator - (Tensor *tens);
		Tensor *operator - (double val);
		Tensor *operator * (Tensor *tens);
		Tensor *operator * (double val);
		Tensor *operator / (Tensor *tens);
		Tensor *operator / (double val);
		Tensor *operator ^ (Tensor *tens);
		Tensor *operator ^ (double val);
		Tensor *operator ^ (int val);

		void operator += (Tensor *tens);
		void operator += (double val);
		void operator -= (Tensor *tens);
		void operator -= (double val);
		void operator *= (Tensor *tens);
		void operator *= (double val);
		void operator /= (Tensor *tens);
		void operator /= (double val);
		void operator ^= (Tensor *tens);
		void operator ^= (double val);
		void operator ^= (int val);

		Tensor *operator == (Tensor *tens);
		Tensor *operator != (Tensor *tens);
		Tensor *operator >  (Tensor *tens);
		Tensor *operator <  (Tensor *tens);
		Tensor *operator >= (Tensor *tens);
		Tensor *operator <= (Tensor *tens);

		void operator = (Tensor tens);

		Tensor *transpose(int *axisOrder);

		Tensor *collapseAxis(int axisNum, int *axes);

		friend Tensor *outerProd(Tensor *tens1, Tensor *tens2);
		friend double innerProd(Tensor *tens1, Tensor *tens2);
		friend Tensor *tensorDot(Tensor *tens1, Tensor *tens2, int **axisCollapse);

	private:
		// checks if a pointwise operation can be performed
		// throws shapeEx() or initEx()
		void opExcept(Tensor *pTens);
		void opExcept(Tensor *pTens, bool checkType);
	};

}

#endif // !TENSOR_H