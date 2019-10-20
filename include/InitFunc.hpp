#ifndef INITFUNC_H
#define INITFUNC_H

#include <random>

namespace LIBCAA {

	// midType casts
	enum DATA {
		SHORT,
		INT,
		LONG,
		FLOAT,
		DOUBLE
	};

	class initFactory
	{
	public:
		initFactory();
		~initFactory();

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

	};

}

#endif