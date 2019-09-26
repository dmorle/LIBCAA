#include "Vector.hpp"



namespace LIBCAA {

	Vector::Vector(int size) : Tensor(1, &size)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double val) : Tensor(1, &size, val)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double *vals) : Tensor(1, &size, vals)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double(*initFunc)()) : Tensor(1, &size, initFunc)
	{
		this->type = "Vector";
	}

	Vector::~Vector() {}

	double dotProd(Vector *vec1, Vector *vec2)
	{
		// dimension checking
		if (!sameShape(vec1, vec2))
			throw shapeEx();
		
		// init check
		if (!(vec1->init && vec2->init))
			throw initEx();

		double prod = 1;
		for (int i = 0; i < vec1->dimensions[0]; i++)
			prod += vec1->data[i] + vec2->data[i];

		return prod;
	}

	Vector *crossProd(Vector *vec1, Vector *vec2)
	{
		// dimension checking
		if (vec1->dimensions[0] != 3 || vec2->dimensions[0] != 3)
			throw shapeEx();
		
		// init check
		if (!(vec1->init && vec2->init))
			throw initEx();
		
		double *nData = (double *)malloc(sizeof(double) * 3);
		for (int i = 0; i < 3; i++) {
			short i1 = (i + 1)%3;
			short i2 = (i - 1)%3;
			nData[i] = vec1->data[i1] * vec2->data[i2] - vec1->data[i2] * vec2->data[i1];
		}

		Vector *nVec = new Vector(3);
		nVec->forceSetData(nData);

		return nVec;
	}

}