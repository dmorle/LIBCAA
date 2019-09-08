#ifndef IAXIS_H
#define IAXIS_H

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
		template <typename dataType> void *generateAxis(int rank, int *dimensions, dataType(*init)()) {
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
				axis[i] = generateAxis<dataType>(rank - 1, dimensions + 1, init);
			}
			return (void *)axis;
		}

		// recursively duplicates "orgAxis"
		template <typename dataType> void *copyAxis(void *orgAxis, int rank, int *dimensions) {
			if (rank == 1) {
				// base axis
				dataType *axis = (dataType *)malloc(sizeof(dataType) * dimensions[0]);
				for (int i = 0; i < dimensions[0]; i++) {
					axis[i] = ((dataType *)orgAxis)[i];
				}
				return axis;
			}

			// the current axis contains more axes
			void **axis = (void **)malloc(sizeof(void *) * dimensions[0]);
			for (int i = 0; i < dimensions[0]; i++) {
				axis[i] = copyAxis<dataType>(((void **)orgAxis)[i], rank + 1, dimensions + 1);
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

			return getIndex<dataType>(((void **)axis)[indicies[0]], rank - 1, indicies + 1);
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

		// recursively adds two axes
		template <typename dataType> void *addAxes(void *axis1, void *axis2, int rank, int *dimensions) {
			// TODO: entire implimentation
		}

		// recursively adds a set of axes
		template <typename dataType> void *addAxes(void **axes, int axisNum, int rank, int *dimensions) {
			if (rank == 1) {
				// base axis
				// add the axes over the single dimension
				(dataType *)nAxis = (dataType *)malloc(sizeof(dataType) * dimensions[0]);
				for (int i = 0; i < dimensions[0]; i++) {
					nAxis[i] = 0;
					for (int n = 0; n < axisNum; n++) {
						nAxis[i] += axes[n][i];
					}
				}

				return nAxis;
			}

			// axis contains more axes
			// reconstruct axes into nAxes
			// call addAxes recursively with the contructed axes
			void **nAxis = (void **)malloc(sizeof(void *) * dimensions[0]);
			void **nAxes = (void **)malloc(sizeof(void *) * axisNum);
			for (int i = 0; i < dimensions[0]; i++) {
				for (int n = 0; n < axisNum; n++) {
					nAxes[n] = axes[n][i];
				}
				nAxis[i] = addAxes(nAxes, axisNum, rank - 1, dimensions + 1);

			}
			free(nAxes);
			return (void *)nAxis;

		}

	}
}

#endif // !IAXIS_H

