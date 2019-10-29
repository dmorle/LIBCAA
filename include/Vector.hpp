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
	public:

		friend class Factory;

		Vector *clone();

		// overriding Tensor functions for efficiency
		void setAbsIndex(int i, double val);
		void setIndex(int i, double val);
		double getAbsIndex(int i);
		double getIndex(int i);

		friend Vector *add(Vector *vec1, Vector *vec2);
		friend Vector *add(Vector *vec, double val);
		friend Vector *add(double val, Vector *vec);
		friend Vector *sub(Vector *vec1, Vector *vec2);
		friend Vector *sub(Vector *vec, double val);
		friend Vector *sub(double val, Vector *vec);
		friend Vector *mul(Vector *vec1, Vector *vec2);
		friend Vector *mul(Vector *vec, double val);
		friend Vector *mul(double val, Vector *vec);
		friend Vector *div(Vector *vec1, Vector *vec2);
		friend Vector *div(Vector *vec, double val);
		friend Vector *div(double val, Vector *vec);
		friend Vector *pow(Vector *vec1, Vector *vec2);
		friend Vector *pow(Vector *vec, double val);
		friend Vector *pow(double val, Vector *vec);
		friend Vector *pow(Vector *vec, int val);

		friend Vector *addAcc(int len, Vector **mrxArr);
		friend Vector *mulAcc(int len, Vector **mrxArr);

		friend void iadd(Vector *vec1, Vector *vec2);
		friend void iadd(Vector *vec, double val);
		friend void iadd(double val, Vector *vec);
		friend void isub(Vector *vec1, Vector *vec2);
		friend void isub(Vector *vec, double val);
		friend void isub(double val, Vector *vec);
		friend void imul(Vector *vec1, Vector *vec2);
		friend void imul(Vector *vec, double val);
		friend void imul(double val, Vector *vec);
		friend void idiv(Vector *vec1, Vector *vec2);
		friend void idiv(Vector *vec, double val);
		friend void idiv(double val, Vector *vec);
		friend void ipow(Vector *vec1, Vector *vec2);
		friend void ipow(Vector *vec, double val);
		friend void ipow(double val, Vector *vec);
		friend void ipow(Vector *vec, int val);

		friend Vector *eq(Vector *vec);
		friend Vector *ne(Vector *vec);
		friend Vector *gt(Vector *vec);
		friend Vector *lt(Vector *vec);
		friend Vector *le(Vector *vec);
		friend Vector *ge(Vector *vec);

		// throws shapeEx and initEx
		friend double dotProd(Vector *vec1, Vector *vec2);
		// throws shapeEx and initEx
		friend Vector *crossProd(Vector *vec1, Vector *vec2);

		friend Vector *matmul(Matrix *mrx, Vector *vec);
	
	protected:

		Vector(int size);
		Vector(int size, double val);
		Vector(int size, double *vals);

		~Vector();
	};


	Vector *add(Vector *vec1, Vector *vec2);
	Vector *add(Vector *vec, double val);
	Vector *add(double val, Vector *vec);
	Vector *sub(Vector *vec1, Vector *vec2);
	Vector *sub(Vector *vec, double val);
	Vector *sub(double val, Vector *vec);
	Vector *mul(Vector *vec1, Vector *vec2);
	Vector *mul(Vector *vec, double val);
	Vector *mul(double val, Vector *vec);
	Vector *div(Vector *vec1, Vector *vec2);
	Vector *div(Vector *vec, double val);
	Vector *div(double val, Vector *vec);
	Vector *pow(Vector *vec1, Vector *vec2);
	Vector *pow(Vector *vec, double val);
	Vector *pow(double val, Vector *vec);
	Vector *pow(Vector *vec, int val);

	Vector *addAcc(int len, Vector **mrxArr);
	Vector *mulAcc(int len, Vector **mrxArr);

	void iadd(Vector *vec1, Vector *vec2);
	void iadd(Vector *vec, double val);
	void iadd(double val, Vector *vec);
	void isub(Vector *vec1, Vector *vec2);
	void isub(Vector *vec, double val);
	void isub(double val, Vector *vec);
	void imul(Vector *vec1, Vector *vec2);
	void imul(Vector *vec, double val);
	void imul(double val, Vector *vec);
	void idiv(Vector *vec1, Vector *vec2);
	void idiv(Vector *vec, double val);
	void idiv(double val, Vector *vec);
	void ipow(Vector *vec1, Vector *vec2);
	void ipow(Vector *vec, double val);
	void ipow(double val, Vector *vec);
	void ipow(Vector *vec, int val);

	Vector *eq(Vector *vec);
	Vector *ne(Vector *vec);
	Vector *gt(Vector *vec);
	Vector *lt(Vector *vec);
	Vector *le(Vector *vec);
	Vector *ge(Vector *vec);

	// throws shapeEx and initEx
	double dotProd(Vector *vec1, Vector *vec2);
	// throws shapeEx and initEx
	Vector *crossProd(Vector *vec1, Vector *vec2);

	Vector *matmul(Matrix *mrx, Vector *vec);
}

#endif