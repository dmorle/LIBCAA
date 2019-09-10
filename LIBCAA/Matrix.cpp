#include "Matrix.h"



namespace LIBCAA {

	matrixParams createMatrixParams(int m, int n)
	{
		int *params = (int *)malloc(sizeof(int) * 2);
		params[0] = m;
		params[1] = n;
		return params;
	}

	Matrix::Matrix(matrixParams params, double val) : Tensor(2, params, val)
	{
		this->type = "Matrix";
	}

	Matrix::Matrix(matrixParams params, double **val) : Tensor(2, params)
	{
		// flattening val into this->data
		this->data = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->dimensions[0])
			for (int j = 0; j < this->dimensions[1])
				this->data[i*strides[0]] = val[i][j];

		this->init = true;
		this->type = "Matrix";
	}

	Matrix::Matrix(matrixParams params, double(*initFunc)()) : Tensor(2, params, initFunc)
	{
		this->type = "Matrix";
	}

	Matrix::~Matrix()
	{
	}

}