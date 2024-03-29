#ifndef FACTORY_H
#define FACTORY_H

#include <random>
#include "Vector.hpp"
#include "Matrix.hpp"

namespace LIBCAA {

	class Factory
	{
	public:

		Tensor *noInit(int rank, int *dimensions);
		Matrix *noInit(int m, int n);
		Vector *noInit(int len);

		Tensor *usrInit(int rank, int *dimensions);
		Matrix *usrInit(int m, int n);
		Vector *usrInit(int len);

		Tensor *constant(int rank, int *dimensions, double val=0);
		Matrix *constant(int m, int n, double val=0);
		Vector *constant(int len, double val=0);

		Tensor *arange(int rank, int *dimensions, double start=0);
		Matrix *arange(int m, int n, double start=0);
		Vector *arange(int len, double start=0);

		Tensor *uniDist(int rank, int *dimensions, double min=0, double max=1);
		Matrix *uniDist(int m, int n, double min=0, double max=1);
		Vector *uniDist(int len, double min=0, double max=1);

		Tensor *normDist(int rank, int *dimensions, double mean=0, double stdDev=1);
		Matrix *normDist(int m, int n, double mean=0, double stdDev=1);
		Vector *normDist(int len, double mean=0, double stdDev=1);

		Tensor *leviCivita(int rank, int *dimensions);

		Matrix *identity(int size);
		Matrix *derivativeMatrix(int size);

		// used for deleting LIBCAA objects
		void release(void *_obj);
	
		// List of all non-virtual objects
		char objList[4][64]{ "MDA", "Tensor", "Matrix", "Vector" };

	};
	
}

#endif