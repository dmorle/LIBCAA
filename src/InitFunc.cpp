#include "InitFunc.hpp"
#include <iostream>



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

        // currently only for matricies
        void nextMatrixIndex() {
			index[0] = (index[0] + 1) % dimensions[0];
			if (!index[0] && ++index[1] == dimensions[1]) {
				free(dimensions);
				free(index);
			}
		}

        // generalized for tensors
        void nextIndex() {
            int i = 0;
            do {
                index[i] = (index[i] + 1) % dimensions[i];
            } while (!index[i++] && i < rank);
            if (i == rank && !index[rank - 1]) {
                free(dimensions);
                free(index);
            }
        }

        // determines whether the index is an even or odd parity (true => even)
        bool findIndexParity() {
            int cycleCount = 0;
            for (int i = 0; i < rank; i++) {
                if (index[i] < rank) {
                    // start cycle
                    cycleCount++;

                    int tempI = i;
                    do {
                        /*for (int i = 0; i < rank; i++)
                            std::cout<<index[i];
                        std::cout<<"\tindex"<<std::endl;
                        std::cin.get();

                        printf("%d\ttempI", tempI);
                        std::cin.get();*/

                        int temp = index[tempI];
                        index[tempI] += rank;
                        tempI = temp;
                    } while (tempI != i);
                }
            }

            // unmarking the indicies
            for (int i = 0; i < rank; i++)
                index[i] -= rank;
            
            return (rank - cycleCount)%2;
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

        double leviCivita() {
            for (int i = 0; i < rank; i++)
                for (int j = i + 1; j < rank; j++)
                    if (index[i] == index[j]) {
                        nextIndex();
                        return 0;
                    }
            
            // the index is a permutation

            if (findIndexParity()) {
                nextIndex();
                return 1;
            }
            nextIndex();
            return -1;
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

    // creates a levi-civita tensor
    double(*createLeviCivita(int rank)) () {
        INIT::rank = rank;
        INIT::dimensions = (int *)malloc(sizeof(int) * rank);
        INIT::index = (int *)malloc(sizeof(int) * rank);

        for (int i = 0; i < rank; i++) {
            INIT::index[i] = 0;
            INIT::dimensions[i] = rank;
        }

        return INIT::leviCivita;
    }
}