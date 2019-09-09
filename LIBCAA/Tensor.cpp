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

	// final size, base array, insertion array, final insert locations (ascending) ending in 0
	template<typename dataType> dataType * insertArray(int size, dataType *baseArr, dataType *insertArr, int *locs, int locNum) {
		dataType *result = (dataType *)malloc(sizeof(dataType) * size);

		int bCount = iCount = 0;
		for (int i = 0; i < size; i++) {
			if (i == locs[iCount]) {
				result[i] = insertArr[iCount];
				iCount++;
			}
			else {
				result[i] = baseArr[bCount];
				bCount++;
			}
		}
		return result;
	}

	template<typename dataType> void partArray(int size, dataType *baseArr, int *locs, dataType *part1, dataType *part2) {
		int count1 = 0;
		int count2 = 0;
		for (int i = 0; i < size; i++) {
			if (i == locs[count1]) {
				part1[count1] = baseArr[i];
				count1++;
			}
			else {
				part2[count2] = baseArr[i];
				count2++;
			}
		}
	}

	template <typename dataType> dataType sumAxis(
		dataType *oldData, int *oldDim, int *oldSrd, int oldRk
	)
	{
		int sum = 0;
		if (oldRk == 1) {
			for (int i = 0; i < oldDim[0]; i++) {
				sum += oldData[i];
			}
			return sum;
		}
		for (int i = 0; i < oldDim[0]; i++) {
			sum += sumAxis(oldData + i * oldSrd[0], oldDim + 1, oldSrd + 1, oldRk - 1);
		}
		return sum;
	}

	template <typename dataType> void generateAxis(
		dataType *oldData, int *oldDim, int *oldSrd, int oldRk, 
		dataType *newData, int *newDim, int *newSrd, int newRk
	)
	{
		if (newRk == 1) {
			for (int i = 0; i < newDim[0]; i++) {
				newData[i * newSrd[0]] = sumAxis(oldData + , oldDim, oldSrd, oldRk);
			}
		}
	}

	Tensor Tensor::collapseAxis(int axisNum, int *axes) {
		// check if the collapse is valid
		if (axisNum > this->rank)
			throw shapeEx();

		for (int i = 0; i < axisNum; i++)
			if (axes[i] >= this->rank)
				throw shapeEx();

		for (int i = 0; i < axisNum - 1; i++)
			if (axes[i] >= axes[i + 1])
				throw shapeEx();
		
		if (axes[axisNum - 1] >= axes[axisNum])
			throw shapeEx();

		// the axes can be collapsed

		int oldRk = axisNum;
		int newRk = this->rank - oldRk;

		int *newDim = (int *)malloc(sizeof(int) * newRk);
		int *newSrd = (int *)malloc(sizeof(int) * newRk);
		int *oldDim = (int *)malloc(sizeof(int) * oldRk);
		int *oldSrd = (int *)malloc(sizeof(int) * oldRk);

		partArray<int>(this->rank, this->dimensions, axes, oldDim, newDim);
		partArray<int>(this->rank, this->strides, axes, oldSrd, newSrd);
		
		// get oldData and newData
		// newData is an empty array
		// oldData is a transposed this->data

		Tensor *nTens = new Tensor(nRank, nDimensions, 0.0);
		free(nDimensions);

	}

}