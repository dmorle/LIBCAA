#ifndef INITFUNC_H
#define INITFUNC_H

#include <random>

namespace LIBCAA {

	// initialization functions
	namespace INIT {

		int arangeVal;

		// initializes sequential elements using the ++ operator
		template <typename dataType> dataType arange() {
			return arangeVal++;
		}

		// returns a random "dataType" between min and max distributed uniformally
		template <typename dataType, int min, int max> dataType uniformDist() {
			return ((double)rand() / (double)(RAND_MAX / (max - min))) + min;
		}

		// returns a random "dataType" between min and max that was first cast to midType
		template <typename dataType, typename midType, int min, int max> dataType uniformDist() {
			return (midType)(((double)rand() / (double)(RAND_MAX / (max - min))) + min);
		}

		// returns a random "dataType" between min and max distributed binomially
		template <typename dataType, int min, int max> dataType binomialDist() {
			double res1 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			double res2 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			return res1 + res2;
		}

		// returns a random "dataType" between min and max that was first cast to midType
		template <typename dataType, typename midType, int min, int max> dataType binomialDist() {
			double res1 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			double res2 = uniformDist<double, ((double)min) / 2, ((double)max) / 2>();
			return (midType)(res1 + res2);
		}
	}

	// initializes sequential elements using the ++ operator
	template <typename dataType> dataType(*createArangeInit()) () {
		INIT::arangeVal = 0;
		return INIT::arange<dataType>;
	}

	// initializes sequential elements using the ++ operator
	template <typename dataType> dataType(*createArangeInit(int initVal)) () {
		INIT::arangeVal = initVal;
		return INIT::arange<dataType>;
	}

	// returns a random "dataType" between min and max distributed uniformally
	template <typename dataType, int min, int max> dataType(*createUniformDist()) () {
		return INIT::uniformDist<dataType, min, max>;
	}

	// returns a random "dataType" between min and max that was first cast to midType
	template <typename dataType, typename midType, int min, int max> dataType(*createUniformDist()) () {
		return INIT::uniformDist<dataType, midType, min, max>;
	}

	// returns a random "dataType" between min and max distributed binomially
	template <typename dataType, int min, int max> dataType(*createBinomialDist()) () {
		return INIT::binomialDist<dataType, min, max>;
	}

	// returns a random "dataType" between min and max that was first cast to midType
	template <typename dataType, typename midType, int min, int max> dataType(*createBinomialDist()) () {
		return INIT::binomialDist<dataType, midType, min, max>;
	}

		// initialization getters for double data type MDAs

	// initializes sequential elements using the ++ operator
	double(*createArangeInit()) () {
		INIT::arangeVal = 0;
		return INIT::arange<double>;
	}

	double(*createArangeInit(int initVal)) () {
		INIT::arangeVal = initVal;
		return INIT::arange<double>;
	}

	// returns a random double between min and max distributed uniformally
	template <int min, int max> double(*createUniformDist()) () {
		return INIT::uniformDist<double, min, max>;
	}

	// returns a random double between min and max that was first cast to midType
	template <typename midType, int min, int max> double(*createUniformDist()) () {
		return INIT::uniformDist<double, midType, min, max>;
	}

	// returns a random double between min and max distributed binomially
	template <int min, int max> double(*createBinomialDist()) () {
		return INIT::binomialDist<double, min, max>;
	}

	// returns a random double between min and max that was first cast to midType
	template <typename midType, int min, int max> double(*createBinomialDist()) () {
		return INIT::binomialDist<double, midType, min, max>;
	}
}

#endif