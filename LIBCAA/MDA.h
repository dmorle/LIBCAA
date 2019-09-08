#ifndef MDA_H
#define MDA_H

#include "Object.h"
#include "Shapes.h"
#include "initEx.h"
#include <stdlib.h>
#include <iostream>

namespace LIBCAA {

	// seperate namespace for backend axis functionality
	namespace IAXIS {

		// recursively generates axes according to specified dimensions
		// leaves indicies uninitialized
		template <typename dataType> void *generateAxis(int rank, int *dimensions) {
			if (rank == 1)
				// base axis
				return malloc(sizeof(dataType) * dimensions[0]);

			// the generated axis contains generated axes
			void **axis = (void **)malloc(sizeof(void *) * dimensions[0]);
			for (int i = 0; i < dimensions[0]; i++) {
				axis[i] = generateAxis<dataType>(rank - 1, dimensions + 1);
			}
			return (void *)axis;
		}

		// recursively generates axes according to specified dimensions
		// initializes all entries with val
		template <typename dataType> void *generateAxis(int rank, int *dimensions, dataType val) {
			if (rank == 1) {
				// base axis
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

		// recursively generates axes according to specified dimensions
		// initializes all entries via the init function
		template <typename dataType> void *generateAxis(int rank, int *dimensions, dataType (*init)()) {
			if (rank == 1) {
				// base axis
				dataType *axis = (dataType *)malloc(sizeof(dataType) * dimensions[0]);
				for (int i = 0; i < dimensions[0]; i++) {
					axis[i] = init();
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
			if (rank == 1) {
				// base axis
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
				// base axis
				free(axis);
			else {
				// recursively deleting all child axes
				for (int i = 0; i < dimensions[0]; i++) {
					delAxis(((void **)axis)[i], rank - 1, dimensions + 1);
				}
				free(axis);
			}

		}

		// recursively finds the value of an axis at an index
		template <typename dataType> dataType getIndex(void *axis, int rank, int *indicies) {
			if (rank == 1)
				return ((dataType *)axis)[indicies[0]];

			return getAxis<dataType>(((void **)axis)[indicies[0]], rank - 1, indicies + 1);
		}

		// recursively prints the axis
		template <typename dataType> void printAxis(void *axis, int rank, int *dimensions) {
			if (rank == 1) {
				// base axis
				// display the axis horizontally
				std::cout << "[" << ((dataType *)axis)[0];
				for (int i = 1; i < dimensions[0]; i++) {
					std::cout << ", " << ((dataType *)axis)[i];
				}
				std::cout << "]" << std::endl;
			}
			else {
				// axis contains more axes
				// display the axis vertically
				std::cout << "[" << std::endl;
				for (int i = 0; i < dimensions[0]; i++) {
					printAxis<dataType>(((void **)axis)[i], rank - 1, dimensions + 1);
				}
				std::cout << "]";
			}
		}

	}

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
			((MDA<dataType> *)npMDA)->data = IAXIS::copyAxis(this->data, this->pShape->rank, this->pShape->dimensions);
			((MDA<dataType> *)npMDA)->init = this->init;
		}

		// displays 
		void print() {
			if (!this->init)
				// the array has uninitialized values
				throw initEx;

			IAXIS::printAxis<dataType>(this->data, this->pShape->rank, this->pShape->dimensions);
		}

	protected:
		pSHAPE pShape;
		void *data;
		bool init;
	};

}

#endif