#ifndef VECFIELD_H
#define VECFIELD_H

#include "VecPoly.hpp"

namespace LIBCAA {

	typedef struct VecFieldStruct *VecFieldParams;
	struct VecFieldStruct {
		int degree;
		int spatialDimension;
		double *coeff;
	};

	VecFieldParams createVecFieldParams(int degree, int spatialDimension, double *(*func)(double *));

	class VecField : public VecPoly
	{
	public:
		VecField(VecFieldParams params);
		~VecField();
	};

}

#endif