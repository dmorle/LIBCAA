#ifndef TENSOR_H
#define TENSOR_H

#include "MDA.h"
#include "LIBCAAEX.h"

namespace LIBCAA {


	class Tensor : protected MDA<double>
	{
	public:

		// all MDA constuctors are transferable to Tensor
		Tensor(int rank, int *dimensions);
		Tensor(int rank, int *dimensions, double val);
		Tensor(int rank, int *dimensions, double(*initFunc)());
		Tensor(int rank, int *dimensions, double *data);

		// MDA deconstructor is transferable to Tensor
		~Tensor() { MDA<double>::~MDA(); }

		Tensor operator + (Tensor tens);
		Tensor operator + (double val);
		Tensor operator - (Tensor tens);
		Tensor operator - (double val);
		Tensor operator * (Tensor tens);
		Tensor operator * (double val);
		Tensor operator / (Tensor tens);
		Tensor operator / (double val);
		Tensor operator ^ (Tensor tens);
		Tensor operator ^ (double val);
		Tensor operator % (Tensor tens);
		Tensor operator % (double val);

		void operator += (Tensor tens);
		void operator += (double val);
		void operator -= (Tensor tens);
		void operator -= (double val);
		void operator *= (Tensor tens);
		void operator *= (double val);
		void operator /= (Tensor tens);
		void operator /= (double val);
		void operator ^= (Tensor tens);
		void operator ^= (double val);
		void operator %= (Tensor tens);
		void operator %= (double val);

		Tensor operator == (Tensor tens);
		Tensor operator != (Tensor tens);
		Tensor operator >= (Tensor tens);
		Tensor operator <= (Tensor tens);

		void operator = (Tensor tens);
	};

}

#endif // !TENSOR_H