#include "Tensor.h"
#include <math.h>


namespace LIBCAA {

	// helper functions

	template <typename dataType> void transposeAxis(dataType *oldData, int *oldSrd, int *axisOrder, dataType *newData, int *dim, int *newSrd, int rk)
	{
		if (rk == 1) {
			for (int i = 0; i < dim[0]; i++) {
				newData[i] = oldData[i * oldSrd[axisOrder[0]]];
			}
		}
		else {
			for (int i = 0; i < dim[0]; i++) {
				transposeAxis(oldData + i * oldSrd[axisOrder[0]], oldSrd, axisOrder + 1, newData + i * newSrd[0], dim + 1, newSrd + 1, rk - 1);
			}
		}
	}

	// final size, base array, insertion array, final insert locations (ascending) ending in 0
	template<typename dataType> dataType * insertArray(int size, dataType *baseArr, dataType *insertArr, int *locs, int locNum)
	{
		dataType *result = (dataType *)malloc(sizeof(dataType) * size);

		int bCount = 0;
		int iCount = 0;
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

	template<typename dataType> void partArray(int size, dataType *baseArr, int *locs, dataType *result)
	{
		int count = 0;
		for (int i = 0; i < size; i++) {
			if (i == locs[count]) {
				result[count] = baseArr[i];
				count++;
			}
		}
	}

	template <typename dataType> dataType sumAxis (dataType *oldData, int *oldDim, int *oldSrd, int oldRk)
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

	template <typename dataType> void generateAxis
	(
		dataType *oldData, int *oldDim, int *oldSrd, int oldRk,
		dataType *newData, int *newDim, int *newSrd, int newRk
	)
	{
		if (newRk == 1) {
			for (int i = 0; i < newDim[0]; i++) {
				newData[i * newSrd[0]] = sumAxis(oldData + oldSrd[0], oldDim, oldSrd, oldRk);
			}
		}
	}

	// end of helper functions

	Tensor::Tensor(int rank, int * dimensions) : MDA(rank, dimensions)
	{
		this->type = "Tensor";
	}

	Tensor::Tensor(int rank, int * dimensions, int * strides) : MDA(rank, dimensions, strides)
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

	Tensor *Tensor::operator+(Tensor *tens)
	{
		this->opExcept(tens);
		
		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] + tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator+(double val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator-(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator-(double val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] - val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator*(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] * tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator*(double val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] * val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator/(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] / tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator/(double val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] / val;
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator^(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], tens->getDataIndex(i));
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator^(double val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], val);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator^(int val)
	{
		if (!this->init)
			throw initEx();

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = std::pow(this->data[i], val);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	void Tensor::operator+=(Tensor *tens)
	{
		this->opExcept(tens);

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] += tens->getDataIndex(i);
	}

	void Tensor::operator+=(double val)
	{
		if (!this->init)
			throw initEx();

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] += val;
	}

	void Tensor::operator-=(Tensor *tens)
	{
		this->opExcept(tens);

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] -= tens->getDataIndex(i);
	}

	void Tensor::operator-=(double val)
	{
		if (!this->init)
			throw initEx();

		for (int i = 0; i < this->len; i++)
			this->data[i] -= val;
	}

	void Tensor::operator*=(Tensor *tens)
	{
		this->opExcept(tens);

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] *= tens->getDataIndex(i);
	}

	void Tensor::operator*=(double val)
	{
		if (!this->init)
			throw initEx();

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] *= val;
	}

	void Tensor::operator/=(Tensor *tens)
	{
		this->opExcept(tens);

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] /= tens->getDataIndex(i);
	}

	void Tensor::operator/=(double val)
	{
		if (!this->init)
			throw initEx();

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] /= val;
	}

	void Tensor::operator^=(Tensor *tens)
	{
		this->opExcept(tens);

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] = pow(this->data[i], tens->getDataIndex(i));
	}

	void Tensor::operator^=(double val)
	{
		if (!this->init)
			throw initEx();

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] = pow(this->data[i], val);
	}

	void Tensor::operator^=(int val)
	{
		if (!this->init)
			throw initEx();

		// operation
		for (int i = 0; i < this->len; i++)
			this->data[i] = pow(this->data[i], val);
	}

	Tensor *Tensor::operator==(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] == tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator!=(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] != tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator>(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] > tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator<(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] < tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator>=(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] >= tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::operator<=(Tensor *tens)
	{
		this->opExcept(tens);

		double *nData = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->len; i++) {
			nData[i] = this->data[i] <= tens->getDataIndex(i);
		}

		Tensor *npTens = new Tensor(this->rank, this->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *Tensor::transpose(int *axisOrder)
	{
		// checking possiblity
		for (int i = 0; i < this->rank; i++)
			if (axisOrder[i] >= this->rank)
				throw shapeEx();

		// generating the dimensions of the transpose
		int *nDimensions = (int *)malloc(sizeof(int) * this->rank);
		for (int i = 0; i < this->rank; i++) {
			nDimensions[i] = this->dimensions[axisOrder[i]];
		}

		// generating the strides of the transpose
		int *nStrides = (int *)malloc(sizeof(int) * this->rank);
		nStrides[this->rank - 1] = 1;

		for (int i = this->rank - 2; i >= 0; i--)
			nStrides[i] = nDimensions[i + 1] * nStrides[i + 1];

		// allocating memory for the new data
		double *newData = (double *)malloc(sizeof(double) * this->len);

		// getting the transposed axes
		transposeAxis<double>(this->data, this->strides, axisOrder, newData, nDimensions, nStrides, this->rank);

		// creating the tensor
		Tensor *npTens = new Tensor(this->rank, nDimensions, nStrides);
		npTens->forceSetData(newData);

		return npTens;
	}

	// collapses axes of the tensor via summation
	// after the last entry in axes, the following integer MUST be -1
	Tensor *Tensor::collapseAxis(int axisNum, int *axes)
	{
		// check if the collapse is valid
		if (axisNum > this->rank)
			throw shapeEx();

		for (int i = 0; i < axisNum; i++)
			if (axes[i] >= this->rank)
				throw shapeEx();

		for (int i = 0; i < axisNum - 1; i++)
			if (axes[i] >= axes[i + 1])
				throw shapeEx();
		
		if (axes[axisNum - 1] <= axes[axisNum])
			throw shapeEx();

		// the axes can be collapsed

			// generating the transpose of the original for axis collapse

		// getting the axis order for the transpose
		double *transData = (double *)malloc(sizeof(double) * this->len);

		int count = 0;
		int *transOrder = (int *)malloc(sizeof(int) * this->rank);
		for (int i = 0; i < this->rank; i++) {
			if (i == axes[count]) {
				count++;
				continue;
			}

			transOrder[i - count] = i;
		}

		for (int i = 0; i < axisNum; i++) {
			transOrder[this->rank - i - 1] = axes[i];
		}

		// generating the dimensions of the transpose
		int *transDimensions = (int *)malloc(sizeof(int) * this->rank);
		for (int i = 0; i < this->rank; i++) {
			transDimensions[i] = this->dimensions[transOrder[i]];
		}


		// generating the strides of the transpose
		int *transStrides = (int *)malloc(sizeof(int) * this->rank);
		transStrides[this->rank - 1] = 1;

		for (int i = this->rank - 2; i >= 0; i--)
			transStrides[i] = transDimensions[i + 1] * transStrides[i + 1];

		// generating the transpose
		transposeAxis<double>(this->data, this->strides, transOrder, transData, transDimensions, transStrides, this->rank);

			// set up for axis collapse

		int newRank = this->rank - axisNum;

		int *newDimensions = (int *)malloc(sizeof(int) * newRank);
		int *newStrides = (int *)malloc(sizeof(int) * newRank);

		int sumLen = transStrides[newRank - 1];

		for (int i = 0; i < newRank; i++) {
			newDimensions[i] = transDimensions[i];
			newStrides[i] = transStrides[i] / sumLen;
		}

			// creating the collapsed axes

		// len = dim[0] * srd[0]
		double *newData = (double *)malloc(sizeof(double) * newDimensions[0] * newStrides[0]);
		
		for (int i = 0; i < this->len / sumLen; i++) {
			newData[i] = transData[i * sumLen];
			for (int j = 1; j < sumLen; j++) {
				newData[i] += transData[i * sumLen + j];
			}
		}

		Tensor *npTens = new Tensor(newRank, newDimensions, newStrides);
		npTens->forceSetData(newData);

		free(transData);
		free(transOrder);
		free(transDimensions);
		free(transStrides);

		free(newDimensions);
		free(newStrides);
		
		return npTens;
	}

	void Tensor::opExcept(Tensor *pTens)
	{
		// checking if operation can be performed
		if (!sameShape(this, pTens))
			throw shapeEx();

		// checking if both tensors are initialized
		if (!this->init || !pTens->getInit())
			throw initEx();
	}

	void Tensor::opExecpt(Tensor *pTens, bool checkType)
	{
		// checking if tensors have the same type
		if (this->getType() != pTens->getType())
			throw typeEx();

		// checking if operation can be performed
		if (!sameShape(this, pTens))
			throw shapeEx();

		// checking if both tensors are initialized
		if (!this->init || !pTens->getInit())
			throw initEx();
	}

	Tensor *outerProd(Tensor *tens1, Tensor *tens2) {
		int newRank = tens1->rank + tens2->rank;

		int *newDimensions = (int *)malloc(sizeof(int) * newRank);
		int *newStrides = (int *)malloc(sizeof(int) * newRank);

		// initializing newDimensions
		for (int i = 0; i < tens1->rank; i++) {
			newDimensions[i] = tens1->dimensions[i];
		}
		for (int i = 0; i < tens2->rank; i++) {
			newDimensions[i + tens1->rank] = tens2->dimensions[i];
		}

		// initializing newStrides
		newStrides[newRank - 1] = 1;

		for (int i = newRank - 1; i > 0; i--) {
			newStrides[i - 1] = newDimensions[i] * newStrides[i];
		}

		double *newData = (double *)malloc(sizeof(double) * newStrides[0] * newDimensions[0]);

		// initializing newData
		for (int i = 0; i < tens1->len; i++)
			for (int j = 0; j < tens2->len; j++)
				newData[i * tens2->len + j] = tens1->data[i] * tens2->data[j];

		Tensor *nTens = new Tensor(newRank, newDimensions, newStrides);
		nTens->forceSetData(newData);

		free(newDimensions);
		free(newStrides);
		
		return nTens;
	}

	double innerProd(Tensor *tens1, Tensor *tens2) {
		tens1->opExcept(tens2);

		double result = 0;
		for (int i = 0; i < tens1->len; i++) {
			result += tens1->data[i] * tens2->data[i];
		}
		return result;
	}

}