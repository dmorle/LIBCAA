#ifndef VECTOR_H
#define VECTOR_H

#include "Tensor.hpp"

namespace LIBCAA {

	// rank 1 tensor
	// used for:
	//	vector value functions
	//	linear Ordinary Differential Equations
	class Vector : public Tensor
	{
	public:
		Vector(int size, double val);
		Vector(int size, double *vals);
		Vector(int size, double(*initFunc)());
		~Vector();
	};

}

#endif