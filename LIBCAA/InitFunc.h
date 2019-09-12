#ifndef INITFUNC_H
#define INITFUNC_H

#include <random>

namespace LIBCAA {

	// initialization functions
	namespace INIT {

		// initializes sequential elements using the ++ operator
		template <typename dataType> dataType arange() {
			static dataType val = 0;
			return val++;
		}

		// returns a random "dataType" between min and max distributed uniformally
		template <typename dataType, int min, int max> dataType uniformDist() {
			return ((double)rand() / (double)(RAND_MAX / (max - min))) + min;
		}

		// returns a random "dataType" between min and max distributed binomially
		template <typename dataType, int min, int max> dataType binomialDist() {
			double res1 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			double res2 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			return res1 + res2;
		}
	}
}

#endif