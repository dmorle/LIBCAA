#include "VecField.h"



namespace LIBCAA {

	// returns the coefficiant data for func as a Taylor Series
	double *TaylorSeries(int degree, int spatialDimension, double *(*func)(double *)) {
		return nullptr;
	}

	VecFieldParams createVecFieldParams(int degree, int spatialDimension, double *(*func)(double *))
	{
		VecFieldParams params = (VecFieldParams)malloc(sizeof(struct VecFieldStruct));
		params->degree = degree;
		params->spatialDimension = spatialDimension;
		params->coeff = TaylorSeries(degree, spatialDimension, func);
		return params;
	}

	VecField::VecField(VecFieldParams params) : VecPoly(createVecPolyParams(params->degree, params->spatialDimension, params->spatialDimension))
	{
	}


	VecField::~VecField()
	{
	}

}