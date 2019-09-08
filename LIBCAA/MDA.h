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

		// creates an empty MDA obj
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

		// 
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

		// copies all data into a new MDA
		void *clone() {
			if (this->init) {
				MDA<dataType> *npMDA = new MDA<dataType>(this->rank, this->dimensions, this->data);
				return npMDA;
			}
			MDA<dataType> *npMDA = new MDA<dataType>(this->rank, this->dimensions);
			return npMDA;
		}

		// displays the array
		void print() {
			if (!this->init)
				// the array has uninitialized values
				throw initEx;

			// print the MDA
			this->printAxis("", 0, this->rank, this->dimensions, this->strides);
		}

		// gets the value at the index
		dataType getRawIndex(int *indicies) {
			int index = 0;
			for (int i = 0; i < this->rank; i++) {
				index += indicies[i] * this->strides[i];
			}
			return this->data[index];
		}

		dataType getIndex(int *indicies) {
			for (int i = 0; i < this->rank; i++) {
				indicies[i] %= this->dimensions[i];
			}

			return this->getRawIndex(indicies);
		}

		// TODO: overload () operator for indexing

		// TODO: impliment a slicing function

		// TODO: impliment a reshaping function

	protected:
		int rank;
		int *dimensions;
		int *strides;
		int len;
		dataType *data;
		bool init;

		// initializes the shape defining attributes
		void stdInit(int rank, int *dimensions) {
			this->rank = rank;

			this->dimensions = (int *)malloc(sizeof(int) * rank);
			this->strides = (int *)malloc(sizeof(int) * rank);

			int maxIndex = rank - 1;

			this->dimensions[maxIndex] = dimensions[maxIndex];
			this->strides[maxIndex] = 1;
			this->len = dimensions[maxIndex];

			for (int i = maxIndex - 1; i >= 0; i--) {
				this->dimensions[i] = dimensions[i];
				this->strides[i] = dimensions[i] * strides[i + 1];
				this->len *= dimensions[i];
			}
		}

		// recursively prints out the array
		void printAxis(std::string base, int startIndex, int cRank, int *cDimensions, int *cStride) {
			if (cRank == 1) {
				std::cout << base << "[";
				if (cDimensions[0] != 0) {
					std::cout << this->data[startIndex];
					for (int i = 1; i < cDimensions[0]; i++) {
						std::cout << ", " << this->data[startIndex + i];
					}
				}
				std::cout << "]" << std::endl;
				return;
			}

			std::cout << base << "[" << std::endl;
			if (cDimensions[0] != 0) {
				for (int i = 0; i < cDimensions[0]; i++) {
					this->printAxis(base + " ", startIndex + cStride[0] * i, cRank - 1, cDimensions + 1, cStride + 1);
				}
			}
			std::cout << base << "]" << std::endl;
		}
	};

}

#endif