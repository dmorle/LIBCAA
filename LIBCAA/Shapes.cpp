#include "Shapes.h"
#include <stdarg.h>
#include <stdlib.h>

// all mda shape structures need a getLen and indexing operator

namespace LIBCAA {

	pSHAPE getShape(int rank, ...) {
		va_list ap;
		va_start(ap, rank);

		pSHAPE npShape = (pSHAPE)malloc(sizeof(SHAPE));

		// setting up the SHAPE structure
		npShape->rank = rank;
		npShape->dimensions = (int *)malloc(sizeof(int) * rank);

		// reading the argument list
		for (int i = 0; i < rank; i++) {
			npShape->dimensions[i] = va_arg(ap, int);
		}
		va_end(ap);

		return npShape;
	}

	pSHAPE getShape(int rank, int *dimensions) {
		pSHAPE npShape = (pSHAPE)malloc(sizeof(SHAPE));

		npShape->rank = rank;
		npShape->dimensions = (int *)malloc(sizeof(int) * rank);
		for (int i = 0; i < rank; i++) {
			npShape->dimensions[i] = dimensions[i];
		}

		return npShape;
	}

	pSHAPE copyShape(SHAPE shape) {
		pSHAPE npShape = (pSHAPE)malloc(sizeof(SHAPE));

		npShape->rank = shape.rank;
		npShape->dimensions = (int *)malloc(sizeof(int) * shape.rank);
		for (int i = 0; i < shape.rank; i++) {
			npShape->dimensions[i] = shape.dimensions[i];
		}

		return npShape;
	}

	pSHAPE copyShape(pSHAPE pShape) {
		pSHAPE npShape = (pSHAPE)malloc(sizeof(SHAPE));

		npShape->rank = pShape->rank;
		npShape->dimensions = (int *)malloc(sizeof(int) * pShape->rank);
		for (int i = 0; i < pShape->rank; i++) {
			npShape->dimensions[i] = pShape->dimensions[i];
		}

		return npShape;
	}

	void delShape(pSHAPE pShape) {
		free(pShape->dimensions);
		free(pShape);
	}

	int getLen(SHAPE Shape) {
		return Shape.rank;
	}

	int getLen(pSHAPE pShape) {
		return pShape->rank;
	}
}