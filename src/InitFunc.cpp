#include "InitFunc.hpp"



namespace LIBCAA {
    
    namespace INIT {
        // variable for arange
		int arangeVal;

        // variable for random initializations
        double min;
        double max;
        DATA midType;

		// variables to keep track of indicies for an initialization
		int rank;
		int *dimensions;
		int *index;

        void nextIndex() {
			index[0] = (index[0] + 1) % dimensions[0];
			if (!index[0] && ++index[1] == dimensions[1]) {
				free(dimensions);
				free(index);
			}
		}

		// initializes sequential elements using the ++ operator
		double arange() {
			return arangeVal++;
		}

		// returns a random "dataType" between min and max that was first cast to midType
		double uniformDist() {
            double result = ((double)rand() / (double)(RAND_MAX / (max - min))) + min;

            if (midType == SHORT)
			    return (short)result;
            if (midType == INT)
			    return (int)result;
            if (midType == LONG)
			    return (long)result;
            if (midType == FLOAT)
			    return (float)result;
            if (midType == DOUBLE)
			    return result;
		}

		// returns a random "dataType" between min and max distributed binomially
		double binomialDist() {
            double trueMin = min;
            double trueMax = max;

            min = min/2;
            max = max/2;

            double result = uniformDist() + uniformDist();
			
            min = trueMin;
            max = trueMax;

            if (midType == SHORT)
			    return (short)result;
            if (midType == INT)
			    return (int)result;
            if (midType == LONG)
			    return (long)result;
            if (midType == FLOAT)
			    return (float)result;
            if (midType == DOUBLE)
			    return result;
		}

        double derivativeMatrix() {
			if (index[0] == index[1] + 1) {
				double ret = index[0];
				nextIndex();
				return ret;
			}
			nextIndex();
			return 0;
		}

        double identityMatrix() {
			if (index[0] == index[1]) {
				nextIndex();
				return 1;
			}
			nextIndex();
			return 0;
		}
    }
    // end of INIT namespace

    // initializes sequential elements using the ++ operator
	double(*createArangeInit()) () {
		INIT::arangeVal = 0;

		return INIT::arange;
	}

	double(*createArangeInit(int initVal)) () {
		INIT::arangeVal = initVal;

		return INIT::arange;
	}

	// returns a random double between min and max distributed uniformally
	double(*createUniformDist(double min, double max)) () {
        INIT::min = min;
        INIT::max = max;
        INIT::midType = DOUBLE;

		return INIT::uniformDist;
	}

    // returns a random double casted to midType and back
	double(*createUniformDist(double min, double max, DATA midType)) () {
        INIT::min = min;
        INIT::max = max;
        INIT::midType = midType;

		return INIT::uniformDist;
	}

    // returns a random double between min and max distributed binomially
    double(*createBinomialDist(double min, double max)) () {
        INIT::min = min;
        INIT::max = max;
        INIT::midType = DOUBLE;

        return INIT::binomialDist;
    }

    // returns a random double between min and max that was first cast to midType
    double(*createBinomialDist(double min, double max, DATA midType)) () {
        INIT::min = min;
        INIT::max = max;
        INIT::midType = midType;

        return INIT::binomialDist;
    }

    // returns the entries of a derivative matrix
    double(*createDerivativeMatrix(int size)) () {
		INIT::rank = 2;
		INIT::dimensions = (int *)malloc(sizeof(int) * 2);
		INIT::index = (int *)malloc(sizeof(int) * 2);

		INIT::dimensions[0] = INIT::dimensions[1] = size;
		INIT::index[0] = INIT::index[1] = 0;

		return INIT::derivativeMatrix;
	}

    // returns the entries of an identity matrix
	double(*createIdentityMatrix(int size)) () {
		INIT::dimensions = (int *)malloc(sizeof(int) * 2);
		INIT::index = (int *)malloc(sizeof(int) * 2);

		INIT::dimensions[0] = INIT::dimensions[1] = size;
		INIT::index[0] = INIT::index[1] = 0;

		return INIT::identityMatrix;
	}
}