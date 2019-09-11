#ifndef VECPOLY_H
#define VECPOLY_H

#include "Vector.h"

namespace LIBCAA {
	
	typedef int *VecPolyParams;
	VecPolyParams createMDPolyParams(int degree, int dimIn, int dimOut);

	class VecPoly : protected Tensor
	{
	public:
		VecPoly(VecPolyParams params);
		VecPoly(VecPolyParams params, double ***coeff);
		VecPoly(VecPolyParams params, double(*initFunc)());
		~VecPoly();

		double eval(Vector *inputs);

	protected:
		VecPoly(int *dimensions, double *data);
	};

}

#endif