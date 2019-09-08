#include "Tensor.h"
#include <math.h>


namespace LIBCAA {

	Tensor::Tensor(int rank, int * dimensions) : MDA(rank, dimensions)
	{
		this->type = "Tensor";
	}

	Tensor::Tensor(int rank, int * dimensions, double val) : MDA(rank, dimensions, val)
	{
		this->type = "Tensor";
	}

	Tensor::Tensor(int rank, int * dimensions, double(*initFunc)()) : MDA(rank, dimensions, initFunc)
	{
		this->type = "Tensor";
	}

	Tensor::Tensor(int rank, int * dimensions, double * data) : MDA(rank, dimensions, data)
	{
		this->type = "Tensor";
	}

	Tensor::~Tensor() {}

	Tensor Tensor::operator+(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx();
		
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] + tens.getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator+(double val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator-(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - tens.getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator-(double val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator*(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] * tens.getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator*(double val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] * val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator/(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] / tens.getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator/(double val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] / val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator^(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], tens.getDataIndex(i));
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator^(double val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], val);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	Tensor Tensor::operator^(int val)
	{
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], val);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceDataSet(nData);

		return *npTens;
	}

	void Tensor::operator+=(Tensor tens)
	{
	}

	void Tensor::operator+=(double val)
	{
	}

	void Tensor::operator-=(Tensor tens)
	{
	}

	void Tensor::operator-=(double val)
	{
	}

	void Tensor::operator*=(Tensor tens)
	{
	}

	void Tensor::operator*=(double val)
	{
	}

	void Tensor::operator/=(Tensor tens)
	{
	}

	void Tensor::operator/=(double val)
	{
	}

	void Tensor::operator^=(Tensor tens)
	{
	}

	void Tensor::operator^=(double val)
	{
	}

	void Tensor::operator%=(Tensor tens)
	{
	}

	void Tensor::operator%=(double val)
	{
	}
	/*
	Tensor Tensor::operator==(Tensor tens)
	{
	}

	Tensor Tensor::operator!=(Tensor tens)
	{
	}

	Tensor Tensor::operator>=(Tensor tens)
	{
	}

	Tensor Tensor::operator<=(Tensor tens)
	{
	}
	*/

}