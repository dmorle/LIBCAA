#ifndef MDA_H
#define MDA_H

#include "Object.h"
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

		// creates MDA obj without initialization from a rank and dimension array
		MDA(int rank, int *dimensions) {
			this->type = "MDA";
			this->stdInit(rank, dimensions);

			this->data = (dataType *)malloc(sizeof(dataType) * this->len);
			this->init = false;
		}

		// creates MDA obj with initialization from a rank and dimension array
		MDA(int rank, int *dimensions, dataType val) {
			this->type = "MDA";
			this->stdInit(rank, dimensions);

			this->data = (dataType *)malloc(sizeof(dataType) * this->len);
			for (int i = 0; i < this->len; i++) {
				this->data[i] = val;
			}

			this->init = true;
		}

		MDA(int rank, int *dimensions, dataType(*initFunc)()) {
			this->type = "MDA";
			this->stdInit(rank, dimensions);
			
			this->data = (dataType *)malloc(sizeof(dataType) * this->len);
			for (int i = 0; i < this->len; i++) {
				this->data[i] = initFunc();
			}

			this->init = true;
		}

		MDA(int rank, int *dimensions, dataType *data) {
			this->type = "MDA";
			this->stdInit(rank, dimensions);

			this->data = (dataType *)malloc(sizeof(dataType) * this->len);
			for (int i = 0; i < this->len; i++) {
				this->data[i] = data[i];
			}

			this->init = true;
		}

		// deallocates memory used by MDA obj
		~MDA() {
			// freeing the array memory
			free(this->data);
			
			// freeing the dimension memory
			free(this->dimensions);
		}

		// copies all data into nMDA
		void *clone() {
			MDA<datatype> *npMDA = new MDA<dataType>(this->rank, this->dimensions, this->data);
			return npMDA;
		}

		// displays the array
		void print() {
			if (!this->init)
				// the array has uninitialized values
				throw initEx;

			// print the MDA
		}

		// gets the value at the index
		dataType getRawIndex(int *indicies) {
			int index = 0;
			for (int i = 0; i < )
			return 
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
		int rank;
		int *dimensions;
		int *strides;
		int len;
		dataType *data;
		bool init;

		void stdInit(int rank, int *dimensions) {
			this->rank = rank;

			this->dimensions = (int *)malloc(sizeof(int) * rank);
			this->strides = (int *)malloc(sizeof(int) * rank);

			int maxIndex = rank - 1;
			this->strides[maxIndex] = 1;
			this->dimensions[maxIndex] = dimensions[maxIndex];
			this->len = dimenions[maxIndex];
			for (int i = maxIndex; i >= 0; i--) {
				this->dimensions[i] = dimensions[i];
				this->strides[i] = dimensions[i] * strides[i + 1];
				this->len *= dimensions[i];
			}
		}
	};

}

#endif