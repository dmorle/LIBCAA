#include "Shapes.h"
#include <stdarg.h>
#include <stdlib.h>

// all mda shape structures need a getLen and indexing operator

namespace LIBCAA {

	pSHAPE getShape(int rank, ...) {
		va_list ap;
		va_start(ap, rank);

		pSHAPE pShape = (pSHAPE)malloc(sizeof(SHAPE));

		// setting up the SHAPE structure
		pShape->rank = rank;
		pShape->dimensions = (int *)malloc(sizeof(int) * rank);

		// reading the argument list
		for (int i = 0; i < rank; i++) {
			pShape->dimensions[i] = va_arg(ap, int);
		}
		va_end(ap);

		return pShape;
	}

	void delShape(pSHAPE pShape) {
		free(pShape->dimensions);
	}

	int getLen(SHAPE Shape) {
		return Shape.rank;
	}

	int getLen(pSHAPE pShape) {
		return pShape->rank;
	}
}