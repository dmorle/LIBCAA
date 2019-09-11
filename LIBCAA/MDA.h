#ifndef MDA_H
#define MDA_H

#include "Object.h"
#include <stdarg.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>

namespace LIBCAA {

	// checks the the two shapes are the same
	bool sameShape(int rank1, int *dimensions1, int rank2, int *dimensions2);

	// checks if all shapes are the same
	bool sameShape(int shapeNum, int *ranks, int **dimensions);

	/*
	 *	Multi-dimensional array class
	 *	extremely limited functionality
	 *	base class for the following:
	 *		Tensor
	 *		Matrix
	 *		Vector
	 *		MDPolynomial
	 */
	template <typename dataType> class MDA : public Object
	{
	public:

		// creates an empty MDA obj
		MDA(int rank, int *dimensions) {
			this->type = "MDA";
			this->stdInit(rank, dimensions);
			
			this->init = false;
		}

		// creates an empty MDA obj
		MDA(int rank, int *dimensions, int *strides) {
			this->type = "MDA";
			this->stdInit(rank, dimensions, strides);

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

		// creates MDA obj with each element initialized by initFunc
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
			// freeing the dimensions memory
			free(this->dimensions);

			// freeing the strides memory
			free(this->strides);

			// freeing the data memory
			if (this->init)
				free(this->data);
		}

		// copies all data into a new MDA
		MDA<dataType> *clone() {
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
				throw initEx();

			// print the MDA
			this->printAxis("", 0, this->rank, this->dimensions, this->strides);
		}

		// initializes this->data with data
		// copies data
		void dataInit(int *data) {
			if (!this->init) {
				this->data = (dataType *)malloc(sizeof(dataType) * this->len);
				this->init = true;
			}

			for (int i = 0; i < this->len; i++) {
				this->data[i] = data[i];
			}
		}

		void setIndex(int *indicies, dataType val) {
			int index = 0;
			for (int i = 0; i < this->rank; i++) {
				index += indicies[i] * this->strides[i];
			}
			this->data[index] = val;
		}

		// gets the value at the index
		dataType getAbsIndex(int *indicies) {
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

			return this->getAbsIndex(indicies);
		}

		// TODO: overload () operator for indexing

		// TODO: impliment a slicing function

		// enter -1 for automatic dimension length on a single axis
		// 
		void reshape(int nRank, int *nDim) {
			int nLen = 1;
			int varDim = -1;
			for (int i = 0; i < nRank; i++) {
				if (nDim[i] == -1) {
					if (varDim == -1)
						varDim = i;;
					else
						throw shapeEx();
				}
				else
					nLen *= nDim[i];
			}
			if (varDim == -1) {
				if (this->len % nLen == 0)
					nDim[varDim] = this->len / nLen;
				else
					throw shapeEx();
			}
			else if (this->len != nLen)
				throw shapeEx();

			this->stdInit(nRank, nDim);
		}

		// TODO: impliment a concatonation function

		// TODO: impliment a tile function

		// unsafe function which sets this->data
		// only use if object is empty
		// DO NOT DELETE DATA
		void forceSetData(dataType *data) {
			if (this->init)
				throw reinitEx();

			this->init = true;
			this->data = data;
		}

		// gets the array at a location in RAM
		dataType getDataIndex(int index) {
			return this->data[index];
		}

		int getLen() {
			return this->len;
		}

		bool getInit() {
			return this->init;
		}

		friend bool sameShape(MDA<dataType> *MDA1, MDA<dataType> *MDA2) {
			return sameShape(MDA1->rank, MDA1->dimensions, MDA2->rank, MDA2->dimensions);
		}

		friend bool sameShape(int MDANum, MDA<dataType> **MDAs) {
			int *ranks = (int *)malloc(sizeof(int) * MDANum);
			int **allDimensions = (int **)malloc(sizeof(int *) * MDANum);

			for (int i = 0; i < MDANum; i++) {
				ranks[i] = MDAs[i]->rank;
				allDimensions[i] = MDAs[i]->dimensions;
			}

			return sameShape(MDANum, ranks, allDimensions);
		}

	protected:
		int rank;
		int *dimensions;
		int *strides;
		int len;
		dataType *data;
		bool init;

	private:
		int dspWidth;
		int dspIndent;

	private:
		// initializes the shape defining attributes
		void stdInit(int rank, int *dimensions) {
			this->rank = rank;

			this->dimensions = (int *)malloc(sizeof(int) * rank);
			this->strides = (int *)malloc(sizeof(int) * rank);

			int maxIndex = rank - 1;

			this->dimensions[maxIndex] = dimensions[maxIndex];
			this->strides[maxIndex] = 1;

			for (int i = maxIndex - 1; i >= 0; i--) {
				this->dimensions[i] = dimensions[i];
				this->strides[i] = dimensions[i + 1] * strides[i + 1];
			}

			this->len = this->strides[0] * this->dimensions[0];

			this->dspWidth = 6;
			this->dspIndent = " ";
		}

		void stdInit(int rank, int *dimensions, int *strides) {
			this->rank = rank;
			
			this->dimensions = (int *)malloc(sizeof(int) * rank);
			this->strides = (int *)malloc(sizeof(int) * rank);

			for (int i = 0; i < rank; i++) {
				this->dimensions[i] = dimensions[i];
				this->strides[i] = strides[i];
			}

			this->len = strides[0] * dimensions[0];

			this->dspWidth = 6;
			this->dspIndent = " ";
		}

		// recursively prints out the array
		void printAxis(std::string base, int startIndex, int cRank, int *cDimensions, int *cStride) {
			if (cRank == 1) {
				std::cout << base << "[";
				if (cDimensions[0] != 0) {
					std::cout << std::setw(this->dspWidth) << this->data[startIndex];
					for (int i = 1; i < cDimensions[0]; i++) {
						std::cout << ", ";
						std::cout << std::setw(this->dspWidth) << this->data[startIndex + i];
					}
				}
				std::cout << "]" << std::endl;
				return;
			}

			std::cout << base << "[" << std::endl;
			if (cDimensions[0] != 0) {
				for (int i = 0; i < cDimensions[0]; i++) {
					this->printAxis(base + dspIndent, startIndex + cStride[0] * i, cRank - 1, cDimensions + 1, cStride + 1);
				}
			}
			std::cout << base << "]" << std::endl;
		}
	};

}

#endif