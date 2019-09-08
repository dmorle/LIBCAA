#ifndef SHAPES_H
#define SHAPES_H

namespace LIBCAA {

	typedef struct SHAPE SHAPE;
	struct SHAPE {
		int rank;
		int *dimensions;

		int &operator [] (int idx) {
			return this->dimensions[idx % this->rank];
		}
	};

	typedef SHAPE *pSHAPE;

	pSHAPE getShape(int rank, ...);
	void delShape(pSHAPE pShape);
	
	int getLen(SHAPE);
	int getLen(pSHAPE);
}

#endif SHAPES_H