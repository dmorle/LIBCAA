#ifndef MDPOLY_H
#define MDPOLY_H

#include "Tensor.h"

namespace LIBCAA {
	
	typedef int *MDPolyParams;
	MDPolyParams createMDPolyParams(int degree, int dimIn, int dimOut);

	class MDPolynomial : public Tensor
	{
	public:
		MDPolynomial(MDPolyParams);
		MDPolynomial(MDPolyParams, double *coeff);
		~MDPolynomial();
	};

}

#endif