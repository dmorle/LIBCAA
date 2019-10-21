#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.hpp"

namespace LIBCAA {

	// rank 1 tensor
	// used for:
	//	vector value functions
	//	linear Ordinary Differential Equations
	class Vector : public Tensor
	{
	private:
		Vector(int size);
	public:
		Vector(int size, double val);
		Vector(int size, double *vals);
		Vector(int size, double(*initFunc)());

		~Vector();

		Vector *operator + (Vector *vec);
		Vector *operator + (double val);
		Vector *operator - (Vector *vec);
		Vector *operator - (double val);
		Vector *operator * (Vector *vec);
		Vector *operator * (double val);
		Vector *operator / (Vector *vec);
		Vector *operator / (double val);
		Vector *operator ^ (Vector *vec);
		Vector *operator ^ (double val);
		Vector *operator ^ (int val);

		// overriding Tensor functions for efficiency
		void setAbsIndex(int i, double val);
		void setIndex(int i, double val);
		double getAbsIndex(int i);
		double getIndex(int i);

		// throws shapeEx and initEx
		friend double dotProd(Vector *vec1, Vector *vec2);
		// throws shapeEx and initEx
		friend Vector *crossProd(Vector *vec1, Vector *vec2);
	};

}

#endif