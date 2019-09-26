#include "VecPoly.hpp"



namespace LIBCAA {

	VecPolyParams createVecPolyParams(int degree, int dimIn, int dimOut)
	{
		int *params = (int *)malloc(sizeof(int) * 3);
		params[0] = degree;
		params[1] = dimIn;
		params[2] = dimOut;
		return params;
	}

	VecPoly::VecPoly(VecPolyParams params) : Tensor(3, params)
	{
		//this->type = "VecPoly";
	}

	VecPoly::VecPoly(VecPolyParams params, double ***coeff) : Tensor(3, params)
	{
		// flattening coeff
		for (int i = 0; i < this->dimensions[0]; i++)
			for (int j = 0; j < this->dimensions[1]; j++)
				for (int k = 0; k < this->dimensions[2]; k++)
					this->data[i * this->strides[0] + j * this->strides[1] + k] = coeff[i][j][k];

		this->init = true;
		//this->type = "VecPoly";
	}

	VecPoly::VecPoly(VecPolyParams params, double(*initFunc)()) : Tensor(3, params, initFunc)
	{

	}

	VecPoly::VecPoly(int *dimensions, double *data) : Tensor(3, dimensions, data) {}

	VecPoly::~VecPoly() {}

	Vector *VecPoly::eval(Vector *inputs) {
		return NULL;
	}


}