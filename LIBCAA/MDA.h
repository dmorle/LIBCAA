#ifndef MDA_H
#define MDA_H

#include "Object.h"
#include "Shapes.h"
#include "IAXIS.h"
#include "LIBCAAEX.h"
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>

namespace LIBCAA {

	/*
	 *	Multi-dimensional array class
	 *	extremely limited functionality
	 *	base class for the following:
	 *		Tensor
	 *		Matrix
	 *		Vector
	 *		MDPolynomial
	 */
	template <typename dataType> class MDA:Object
	{
	public:
		// creates MDA obj without initialization.  NOTE: use getShape() for pShape parameter
		MDA(pSHAPE pShape) {
			this->type = "MDA";
			this->pShape = pShape;
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions);
			this->init = false;
		}

		// creates MDA obj with initialization. NOTE: use getShape() for pShape parameter
		MDA(pSHAPE pShape, dataType val) {
			this->type = "MDA";
			this->pShape = pShape;
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions, val);
			this->init = true;
		}

		// creates MDA obj without initialization from a rank and dimension array
		MDA(int rank, int *dimensions) {
			this->type = "MDA";
			this->pShape = getShape(rank, dimensions);
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions);
			this->init = false;
		}

		// creates MDA obj with initialization from a rank and dimension array
		MDA(int rank, int *dimensions, dataType val) {
			this->type = "MDA";
			this->pShape = getShape(rank, dimensions);
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions, val);
			this->init = true;
		}

		// deallocates memory used by MDA obj
		~MDA() {
			// deleting the array data
			IAXIS::delAxis(this->data, this->pShape->rank, this->pShape->dimensions);

			// deleting the shape data
			delShape(this->pShape);
		}

		// copies all data into nMDA
		void clone(void *npMDA) {
			((MDA<dataType> *)npMDA)->pShape = copyShape(this->pShape);
			((MDA<dataType> *)npMDA)->data = IAXIS::copyAxis<dataType>(this->data, this->pShape->rank, this->pShape->dimensions);
			((MDA<dataType> *)npMDA)->init = this->init;
		}

		// displays the array
		void print() {
			if (!this->init)
				// the array has uninitialized values
				throw initEx;

			IAXIS::printAxis<dataType>(this->data, this->pShape->rank, this->pShape->dimensions);
		}

		// gets the value at the index
		dataType getRawIndex(int *index) {
			return IAXIS::getIndex<dataType>(this->data, this->pShape->rank, index);
		}

		dataType getIndex(int *index) {
			for (int i = 0; i < this->pShape->rank; i++) {
				index[i] %= (*this->pShape)[i];
			}

			return this->getRawIndex(index);
		}

		// TODO: overload () operator for indexing

		// TODO: impliment a slicing function

	protected:
		pSHAPE pShape;
		void *data;
		bool init;
	};

}

#endif