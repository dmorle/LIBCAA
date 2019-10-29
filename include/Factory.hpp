#ifndef FACTORY_H
#define FACTORY_H

#include <random>
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Tensor.hpp"

#define OBJ_TOTAL

namespace LIBCAA {

	class Factory
	{
	public:

		static Tensor *noInit(int rank, int *dimensions);
		static Matrix *noInit(int m, int n);
		static Vector *noInit(int len);

		static Tensor *constant(int rank, int *dimensions, double val=0);
		static Matrix *constant(int m, int n, double val=0);
		static Vector *constant(int len, double val=0);

		static Tensor *arange(int rank, int *dimensions, double start=0);
		static Matrix *arange(int m, int n, double start=0);
		static Vector *arange(int len, double start=0);

		static Tensor *uniDist(int rank, int *dimensions, double min=0, double max=1);
		static Matrix *uniDist(int m, int n, double min=0, double max=1);
		static Vector *uniDist(int len, double min=0, double max=1);

		static Tensor *normDist(int rank, int *dimensions, double mean=0, double stdDev=1);
		static Matrix *normDist(int m, int n, double mean=0, double stdDev=1);
		static Vector *normDist(int len, double mean=0, double stdDev=1);

		static Tensor *leviCivita(int rank, int *dimensions);

		static Matrix *identity(int size);
		static Matrix *derivativeMatrix(int size);

		// used for deleting LIBCAA objects
		static void release(void *_obj);
	
		// List of all non-virtual objects
		const static std::string objList[OBJ_TOTAL];
	};

	const std::string Factory::objList[OBJ_TOTAL] = { "MDA", "Tensor", "Matrix", "Vector" };

}

#endif