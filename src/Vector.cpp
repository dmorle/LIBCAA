#include "Vector.hpp"
#include <math.h>


namespace LIBCAA {

	Vector::Vector(int size) : Tensor(1, &size)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double val) : Tensor(1, &size, val)
	{
		this->type = "Vector";
	}

	Vector::~Vector() {}

	void Vector::setAbsIndex(int i, double val)
	{
		this->data[i] = val;
	}

	void Vector::setIndex(int i, double val)
	{
		setAbsIndex(i % this->len, val);
	}

	double Vector::getAbsIndex(int i)
	{
		return this->data[i];
	}

	double Vector::getIndex(int i)
	{
		return getAbsIndex(i % this->len);
	}

	Vector *add(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		double *nData = (double *)malloc(sizeof(double) * vec1->len);
		for (int i = 0; i < vec1->len; i++)
			nData[i] = vec1->data[i] + vec2->data[i];

		Vector *npVec = new Vector(vec1->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *add(Vector *vec, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = vec->data[i] + val;

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *add(double val, Vector *vec)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = val + vec->data[i];

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}
	
	Vector *sub(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		double *nData = (double *)malloc(sizeof(double) * vec1->len);
		for (int i = 0; i < vec1->len; i++)
			nData[i] = vec1->data[i] - vec2->data[i];

		Vector *npVec = new Vector(vec1->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *sub(Vector *vec, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = vec->data[i] - val;

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *sub(double val, Vector *vec)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = val - vec->data[i];

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *mul(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		double *nData = (double *)malloc(sizeof(double) * vec1->len);
		for (int i = 0; i < vec1->len; i++)
			nData[i] = vec1->data[i] * vec2->data[i];

		Vector *npVec = new Vector(vec1->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *mul(Vector *vec, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = vec->data[i] * val;

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *mul(double val, Vector *vec)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = val * vec->data[i];

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *div(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		double *nData = (double *)malloc(sizeof(double) * vec1->len);
		for (int i = 0; i < vec1->len; i++)
			nData[i] = vec1->data[i] / vec2->data[i];

		Vector *npVec = new Vector(vec1->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *div(Vector *vec, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = vec->data[i] / val;

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *div(double val, Vector *vec)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = val / vec->data[i];

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *pow(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		double *nData = (double *)malloc(sizeof(double) * vec1->len);
		for (int i = 0; i < vec1->len; i++)
			nData[i] = std::pow(vec1->data[i], vec2->data[i]);

		Vector *npVec = new Vector(vec1->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *pow(Vector *vec, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = std::pow(vec->data[i], val);

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *pow(double val, Vector *vec)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = std::pow(val, vec->data[i]);

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *pow(Vector *vec, int val)
	{
		double *nData = (double *)malloc(sizeof(double) * vec->len);
		for (int i = 0; i < vec->len; i++)
			nData[i] = std::pow(vec->data[i], val);

		Vector *npVec = new Vector(vec->len);
		npVec->forceSetData(nData);

		return npVec;
	}


	Vector *addAcc(int len, Vector **vecArr)
	{
		for (int i = 1; i < len; i++)
			vecArr[0]->opExcept(vecArr[i]);

		double *nData = (double *)calloc(vecArr[0]->len, sizeof(double));

		for (int i = 0; i < vecArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] += vecArr[j]->data[i];
		
		Vector *npVec = new Vector(vecArr[0]->len);
		npVec->forceSetData(nData);

		return npVec;
	}

	Vector *mulAcc(int len, Vector **vecArr)
	{
		for (int i = 1; i < len; i++)
			vecArr[0]->opExcept(vecArr[i]);

		double *nData = (double *)malloc(sizeof(double) * vecArr[0]->len);
		for (int j = 0; j < vecArr[0]->len; j++)
			nData[j] = vecArr[0]->data[j];

		for (int i = 1; i < vecArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] *= vecArr[j]->data[i];
		
		Vector *npVec = new Vector(vecArr[0]->len);
		npVec->forceSetData(nData);

		return npVec;
	}
	

	void iadd(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		for (int i = 0; i < vec1->len; i++)
			vec1->data[i] += vec2->data[i];
	}

	void iadd(Vector *vec, double val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] += val;
	}

	void iadd(double val, Vector *vec)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] += val;
	}

	void isub(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		for (int i = 0; i < vec1->len; i++)
			vec1->data[i] -= vec2->data[i];
	}

	void isub(Vector *vec, double val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] -= val;
	}

	void isub(double val, Vector *vec)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] = val - vec->data[i];
	}

	void imul(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		for (int i = 0; i < vec1->len; i++)
			vec1->data[i] *= vec2->data[i];
	}

	void imul(Vector *vec, double val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] *= val;
	}

	void imul(double val, Vector *vec)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] *= val;
	}

	void idiv(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		for (int i = 0; i < vec1->len; i++)
			vec1->data[i] /= vec2->data[i];
	}

	void idiv(Vector *vec, double val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] /= vec->data[i];
	}

	void idiv(double val, Vector *vec)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] = val/vec->data[i];
	}

	void ipow(Vector *vec1, Vector *vec2)
	{
		vec1->opExcept(vec2);

		for (int i = 0; i < vec1->len; i++)
			vec1->data[i] = std::pow(vec1->data[i], vec2->data[i]);
	}

	void ipow(Vector *vec, double val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] = std::pow(vec->data[i], val);
	}

	void ipow(double val, Vector *vec)
	{
		for (int i = 0; i , vec->len; i++)
			vec->data[i] = std::pow(val, vec->data[i]);
	}

	void ipow(Vector *vec, int val)
	{
		for (int i = 0; i < vec->len; i++)
			vec->data[i] = std::pow(vec->data[i], val);
	}

	double dotProd(Vector *vec1, Vector *vec2)
	{
		// dimension checking
		if (!sameShape(vec1, vec2))
			throw shapeEx();
		
		// init check
		if (!(vec1->init && vec2->init))
			throw initEx();

		double prod = 1;
		for (int i = 0; i < vec1->dimensions[0]; i++)
			prod += vec1->data[i] + vec2->data[i];

		return prod;
	}

	Vector *crossProd(Vector *vec1, Vector *vec2)
	{
		// dimension checking
		if (vec1->dimensions[0] != 3 || vec2->dimensions[0] != 3)
			throw shapeEx();
		
		// init check
		if (!(vec1->init && vec2->init))
			throw initEx();
		
		double *nData = (double *)malloc(sizeof(double) * 3);
		for (int i = 0; i < 3; i++) {
			short i1 = (i + 1)%3;
			short i2 = (i - 1)%3;
			nData[i] = vec1->data[i1] * vec2->data[i2] - vec1->data[i2] * vec2->data[i1];
		}

		Vector *nVec = new Vector(3);
		nVec->forceSetData(nData);

		return nVec;
	}

}