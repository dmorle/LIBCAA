#include "MDPolynomial.h"



namespace LIBCAA {

	MDPolynomial::MDPolynomial(MDPolyParams params) : Tensor(3, params)
	{

	}

	MDPolynomial::MDPolynomial(MDPolyParams params, double *coeff) : Tensor(3, params, coeff)


	MDPolynomial::~MDPolynomial()
	{
	}

}