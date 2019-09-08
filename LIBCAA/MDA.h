#ifndef MDA_H
#define MDA_H

#include "Object.h"
#include "Shapes.h"
#include "initEx.h"
#include <stdlib.h>
#include <iostream>

namespace LIBCAA {

	namespace IAXIS {

		// recursively generates axes according to dimensions
		template <typename dataType> void *generateAxis(int rank, int *dimensions) {
			// bottom layer axis
			if (rank == 1)
				return malloc(sizeof(dataType) * dimensions[0]);

			// the generated axis contains generated axes
			void **axis = (void **)malloc(sizeof(void *) * dimensions[0]);
			for (int i = 0; i < dimensions[0]; i++) {
				axis[i] = generateAxis<dataType>(rank - 1, dimensions + 1);
			}
			return (void *)axis;
		}

		// recursively generates axes according to dimensions and fills all entries with primative "val"
		template <typename dataType> void *generateAxis(int rank, int *dimensions, dataType val) {
			// bottom layer axis
			if (rank == 1) {
				 dataType *axis = (dataType *)malloc(sizeof(dataType) * dimensions[0]);
				 for (int i = 0; i < dimensions[0]; i++) {
					 axis[i] = val;
				 }
				 return axis;
			}

			// the generated axis contains generated axes
			void **axis = (void **)malloc(sizeof(void *) * dimensions[0]);
			for (int i = 0; i < dimensions[0]; i++) {
				axis[i] = generateAxis<dataType>(rank - 1, dimensions + 1, val);
			}
			return (void *)axis;
		}

		// recursively duplicates "orgAxis"
		template <typename dataType> void *copyAxis(void *orgAxis, int rank, int *dimensions) {
			// bottom layer axis
			if (rank == 1) {
				dataType *axis = (dataType *)malloc(sizeof(dataType) * dimensions[0]);
				for (int i = 0; i < dimensions[0]; i++) {
					axis[i] = orgAxis[i];
				}
				return axis;
			}
			
			// the current axis contains more axes
			void **axis = (void **)malloc(sizeof(void *) * dimensions[0]);
			for (int i = 0; i < dimensions[0]; i++) {
				axis[i] = copyAxis(rank + 1, dimensions + 1, orgAxis[i]);
			}
			return (void *)axis;
		}

		// recursively deletes the axis
		void delAxis(void *axis, int rank, int *dimensions) {
			if (rank == 1)
				free(axis);
			else {
				// recursively delete all child axes
				for (int i = 0; i < dimensions[0]; i++) {
					delAxis(((void **)axis)[i], rank - 1, dimensions + 1);
				}
				free(axis);
			}

		}

		template <typename dataType> dataType getIndex(void *axis, int rank, int *indicies) {
			if (rank == 1)
				return ((dataType *)axis)[indicies[0]];

			return getAxis<dataType>(((void **)axis)[indicies[0]], rank - 1, indicies + 1);
		}

		// recursively prints the axis
		template <typename dataType> void printAxis(void *axis, int rank, int *dimensions) {
			if (rank == 1) {
				std::cout << "[" << ((dataType *)axis)[0];
				for (int i = 1; i < dimensions[0]; i++) {
					std::cout << ", " << ((dataType *)axis)[i];
				}
				std::cout << "]" << std::endl;
			}
			else {
				std::cout << "[" << std::endl;
				for (int i = 0; i < dimensions[0]; i++) {
					printAxis<dataType>(((void **)axis)[i], rank - 1, dimensions + 1);
				}
				std::cout << "]";
			}
		}

	}

	template <typename dataType> class MDA:Object
	{
	public:
		MDA(pSHAPE pShape) {
			this->pShape = pShape;
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions);
			this->init = false;
		}

		MDA(pSHAPE pShape, dataType val) {
			this->pShape = pShape;
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions, val);
			this->init = true;
		}

		MDA(int rank, int *dimensions) {
			this->pShape = getShape(rank, dimensions);
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions);
			this->init = false;
		}

		MDA(int rank, int *dimensions, dataType val) {
			this->pShape = getShape(rank, dimensions);
			this->data = IAXIS::generateAxis<dataType>(this->pShape->rank, this->pShape->dimensions, val);
			this->init = true;
		}

		~MDA() {
			// deleting the array data
			IAXIS::delAxis(this->data, this->pShape->rank, this->pShape->dimensions);

			// deleting the shape data
			delShape(this->pShape);
		}

		void clone(MDA<dataType> * nMDA) {
			nMDA->pShape = copyShape(this->pShape);
			nMDA->data = IAXIS::copyAxis(this->data, this->pShape->rank, this->pShape->dimensions);
			nMDA->init = this->init;
		}

		void print() {
			if (!this->init)
				throw initEx;		// the array has uninitialized values

			IAXIS::printAxis<dataType>(this->data, this->pShape->rank, this->pShape->dimensions);
		}

		MDA<dataType> *getTranspose(int *axisOrder) {
			pSHAPE npShape = getShape(this->pShape->rank, axisOrder);

			return NULL;
		}

	protected:
		pSHAPE pShape;
		void *data;
		bool init;
	};

}

#endif