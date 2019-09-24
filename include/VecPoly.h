#ifndef VECPOLY_H
#define VECPOLY_H

#include "Vector.h"
#include "VecFunc.h"

namespace LIBCAA {
	
	typedef int *VecPolyParams;
	VecPolyParams createVecPolyParams(int degree, int dimIn, int dimOut);

	class VecPoly : public VecFunc, protected Tensor
	{
	public:
		VecPoly(VecPolyParams params);
		VecPoly(VecPolyParams params, double ***coeff);
		VecPoly(VecPolyParams params, double(*initFunc)());
		~VecPoly();

		Vector *eval(Vector *inputs);

	protected:
		VecPoly(int *dimensions, double *data);
	};

}

#endif