#ifndef INITFUNC_H
#define INITFUNC_H

#include <random>

namespace LIBCAA {

	// initialization functions
	namespace INIT {

		// initializes sequential elements using the ++ operator
		double arange();

		// returns a random "dataType" between min and max that was first cast to midType
		double uniformDist();

		// returns a random "dataType" between min and max that was first cast to midType
		double binomialDist();

		// returns a sequence which creates a derivative matrix
		double derivativeMatrix();

		// returns a sequence which creates an identity matrix
		double identityMatrix();

		// returns a leviCivita tensor
	}

	// midType casts
	enum DATA {
		SHORT,
		INT,
		LONG,
		FLOAT,
		DOUBLE
	};

	// initializes sequential elements using the ++ operator
	double(*createArangeInit()) ();

	double(*createArangeInit(int initVal)) ();

	// returns a random double between min and max distributed uniformally
	double(*createUniformDist(double min, double max)) ();

	// returns a random double between min and max that was first cast to midType
	double(*createUniformDist(double min, double max, DATA midType)) ();

	// returns a random double between min and max distributed binomially
	double(*createBinomialDist(double min, double max)) ();

	// returns a random double between min and max that was first cast to midType
	double(*createBinomialDist(double min, double max, DATA midType)) ();

	// returns the entries of a derivative matrix
	double(*createDerivativeMatrix(int size)) ();

	// returns the entries of an identity matrix
	double(*createIdentityMatrix(int size)) ();

	// creates a levi-civita tensor
	double(*createLeviCivita(int rank)) ();
}

#endif