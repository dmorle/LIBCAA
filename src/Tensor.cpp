#include "Tensor.hpp"
#include <math.h>

// applyFunc helpers

double sigmoid(double x) {
	// TODO: do sigmoid
	return 0;
}

double sigmoid1(double x) {
	// TODO: do sigmoid prime
	return 0;
}

double ReLU(double x) {
	if (x > 0)
		return x;
	return 0;
}

double ReLU1(double x) {
	if (x > 0)
		return 1;
	return 0;
}

namespace LIBCAA {

	// helper functions

	int **createAxisPairs(int axisNum, int *axis1, int *axis2) {
		int **axisPairs = (int **)malloc(sizeof(int *) * 2);
		axisPairs[0] = (int *)malloc(sizeof(int) * (axisNum + 1));
		axisPairs[1] = (int *)malloc(sizeof(int) * (axisNum + 1));

		for (int i = 0; i < axisNum; i++) {
			axisPairs[0][i] = axis1[i];
			axisPairs[1][i] = axis2[i];
		}

		axisPairs[0][axisNum] = -1;
		axisPairs[1][axisNum] = -1;

		return axisPairs;
	}

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

	void Tensor::opExcept(Tensor *pTens)
	{
		// checking if operation can be performed
		if (!sameShape(this, pTens))
			throw shapeEx();

		// checking if both tensors are initialized
		if (!this->init || !pTens->getInit())
			throw initEx();
	}

	void Tensor::opExcept(Tensor *pTens, bool checkType)
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

	Tensor *add(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		double *nData = (double *)malloc(sizeof(double) * tens1->len);
		for (int i = 0; i < tens1->len; i++)
			nData[i] = tens1->data[i] + tens2->data[i];

		Tensor *npTens = new Tensor(tens1->rank, tens1->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *add(Tensor *tens, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = tens->data[i] + val;

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *add(double val, Tensor *tens)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = val + tens->data[i];

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}
	
	Tensor *sub(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		double *nData = (double *)malloc(sizeof(double) * tens1->len);
		for (int i = 0; i < tens1->len; i++)
			nData[i] = tens1->data[i] - tens2->data[i];

		Tensor *npTens = new Tensor(tens1->rank, tens1->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *sub(Tensor *tens, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = tens->data[i] - val;

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *sub(double val, Tensor *tens)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = val - tens->data[i];

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *mul(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		double *nData = (double *)malloc(sizeof(double) * tens1->len);
		for (int i = 0; i < tens1->len; i++)
			nData[i] = tens1->data[i] * tens2->data[i];

		Tensor *npTens = new Tensor(tens1->rank, tens1->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *mul(Tensor *tens, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = tens->data[i] * val;

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *mul(double val, Tensor *tens)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = val * tens->data[i];

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *div(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		double *nData = (double *)malloc(sizeof(double) * tens1->len);
		for (int i = 0; i < tens1->len; i++)
			nData[i] = tens1->data[i] / tens2->data[i];

		Tensor *npTens = new Tensor(tens1->rank, tens1->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *div(Tensor *tens, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = tens->data[i] / val;

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *div(double val, Tensor *tens)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = val / tens->data[i];

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *pow(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		double *nData = (double *)malloc(sizeof(double) * tens1->len);
		for (int i = 0; i < tens1->len; i++)
			nData[i] = std::pow(tens1->data[i], tens2->data[i]);

		Tensor *npTens = new Tensor(tens1->rank, tens1->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *pow(Tensor *tens, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = std::pow(tens->data[i], val);

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *pow(double val, Tensor *tens)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = std::pow(val, tens->data[i]);

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *pow(Tensor *tens, int val)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++)
			nData[i] = std::pow(tens->data[i], val);

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}


	Tensor *addAcc(int len, Tensor **tensArr)
	{
		for (int i = 1; i < len; i++)
			tensArr[0]->opExcept(tensArr[i]);

		double *nData = (double *)calloc(tensArr[0]->len, sizeof(double));

		for (int i = 0; i < tensArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] += tensArr[j]->data[i];
		
		Tensor *npTens = new Tensor(tensArr[0]->rank, tensArr[0]->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *mulAcc(int len, Tensor **tensArr)
	{
		for (int i = 1; i < len; i++)
			tensArr[0]->opExcept(tensArr[i]);

		double *nData = (double *)malloc(sizeof(double) * tensArr[0]->len);
		for (int j = 0; j < tensArr[0]->len; j++)
			nData[j] = tensArr[0]->data[j];

		for (int i = 1; i < tensArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] *= tensArr[j]->data[i];
		
		Tensor *npTens = new Tensor(tensArr[0]->rank, tensArr[0]->dimensions);
		npTens->forceSetData(nData);

		return npTens;
	}
	

	void iadd(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		for (int i = 0; i < tens1->len; i++)
			tens1->data[i] += tens2->data[i];
	}

	void iadd(Tensor *tens, double val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] += val;
	}

	void iadd(double val, Tensor *tens)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] += val;
	}

	void isub(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		for (int i = 0; i < tens1->len; i++)
			tens1->data[i] -= tens2->data[i];
	}

	void isub(Tensor *tens, double val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] -= val;
	}

	void isub(double val, Tensor *tens)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] = val - tens->data[i];
	}

	void imul(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		for (int i = 0; i < tens1->len; i++)
			tens1->data[i] *= tens2->data[i];
	}

	void imul(Tensor *tens, double val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] *= val;
	}

	void imul(double val, Tensor *tens)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] *= val;
	}

	void idiv(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		for (int i = 0; i < tens1->len; i++)
			tens1->data[i] /= tens2->data[i];
	}

	void idiv(Tensor *tens, double val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] /= tens->data[i];
	}

	void idiv(double val, Tensor *tens)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] = val/tens->data[i];
	}

	void ipow(Tensor *tens1, Tensor *tens2)
	{
		tens1->opExcept(tens2);

		for (int i = 0; i < tens1->len; i++)
			tens1->data[i] = std::pow(tens1->data[i], tens2->data[i]);
	}

	void ipow(Tensor *tens, double val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] = std::pow(tens->data[i], val);
	}

	void ipow(double val, Tensor *tens)
	{
		for (int i = 0; i , tens->len; i++)
			tens->data[i] = std::pow(val, tens->data[i]);
	}

	void ipow(Tensor *tens, int val)
	{
		for (int i = 0; i < tens->len; i++)
			tens->data[i] = std::pow(tens->data[i], val);
	}

	// TODO: impliment boolean comparisons
	/*
	Tensor *eq(Tensor *tens);
	Tensor *ne(Tensor *tens);
	Tensor *gt(Tensor *tens);
	Tensor *lt(Tensor *tens);
	Tensor *le(Tensor *tens);
	Tensor *ge(Tensor *tens);
	*/

	Tensor *transpose(Tensor *tens, int *axisOrder)
	{
		// checking possiblity
		for (int i = 0; i < tens->rank; i++)
			if (axisOrder[i] >= tens->rank)
				throw shapeEx();

		// generating the dimensions of the transpose
		int *nDimensions = (int *)malloc(sizeof(int) * tens->rank);
		for (int i = 0; i < tens->rank; i++) {
			nDimensions[i] = tens->dimensions[axisOrder[i]];
		}

		// generating the strides of the transpose
		int *nStrides = (int *)malloc(sizeof(int) * tens->rank);
		nStrides[tens->rank - 1] = 1;

		for (int i = tens->rank - 2; i >= 0; i--)
			nStrides[i] = nDimensions[i + 1] * nStrides[i + 1];

		// allocating memory for the new data
		double *newData = (double *)malloc(sizeof(double) * tens->len);

		// getting the transposed axes
		transposeAxis<double>(tens->data, tens->strides, axisOrder, newData, nDimensions, nStrides, tens->rank);

		// creating the tensor
		Tensor *npTens = new Tensor(tens->rank, nDimensions, nStrides);
		npTens->forceSetData(newData);

		return npTens;
	}

	// collapses axes of the tensor via summation
	// after the last entry in axes, the following integer MUST be -1
	Tensor *collapseAxis(Tensor *tens, int axisNum, int *axes)
	{
		// check if the collapse is valid
		if (axisNum > tens->rank)
			throw shapeEx();

		for (int i = 0; i < axisNum; i++)
			if (axes[i] >= tens->rank)
				throw shapeEx();

		for (int i = 0; i < axisNum - 1; i++)
			if (axes[i] >= axes[i + 1])
				throw shapeEx();
		
		if (axes[axisNum - 1] <= axes[axisNum])
			throw shapeEx();

		// the axes can be collapsed

			// generating the transpose of the original for axis collapse

		// getting the axis order for the transpose
		double *transData = (double *)malloc(sizeof(double) * tens->len);

		int count = 0;
		int *transOrder = (int *)malloc(sizeof(int) * tens->rank);
		for (int i = 0; i < tens->rank; i++) {
			if (i == axes[count]) {
				count++;
				continue;
			}

			transOrder[i - count] = i;
		}

		for (int i = 0; i < axisNum; i++) {
			transOrder[tens->rank - i - 1] = axes[i];
		}

		// generating the dimensions of the transpose
		int *transDimensions = (int *)malloc(sizeof(int) * tens->rank);
		for (int i = 0; i < tens->rank; i++) {
			transDimensions[i] = tens->dimensions[transOrder[i]];
		}


		// generating the strides of the transpose
		int *transStrides = (int *)malloc(sizeof(int) * tens->rank);
		transStrides[tens->rank - 1] = 1;

		for (int i = tens->rank - 2; i >= 0; i--)
			transStrides[i] = transDimensions[i + 1] * transStrides[i + 1];

		// generating the transpose
		transposeAxis<double>(tens->data, tens->strides, transOrder, transData, transDimensions, transStrides, tens->rank);

			// set up for axis collapse

		int newRank = tens->rank - axisNum;

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
		
		for (int i = 0; i < tens->len / sumLen; i++) {
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

	Tensor *applyFunc(Tensor *tens, double(*func)(double))
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);
		for (int i = 0; i < tens->len; i++) {
			nData[i] = func(tens->data[i]);
		}

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions, tens->rank);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *applyFunc(Tensor *tens, STDFUNC func)
	{
		double *nData = (double *)malloc(sizeof(double) * tens->len);

		switch(func) {
			case SIGMOID:
				for (int i = 0; i < tens->len; i++)
					nData[i] = sigmoid(tens->data[i]);
				break;
			case SIGMOID1:
				for (int i = 0; i < tens->len; i++)
					nData[i] = sigmoid1(tens->data[i]);
				break;
			case RELU:
				for (int i = 0; i < tens->len; i++)
					nData[i] = ReLU(tens->data[i]);
				break;
			case RELU1:
				for (int i = 0; i < tens->len; i++)
					nData[i] = ReLU1(tens->data[i]);
				break;
			case SQUARE:
				for (int i = 0; i < tens->len; i++)
					nData[i] = tens->data[i] * tens->data[i];
				break;
			case SQRT:
				for (int i = 0; i < tens->len; i++)
					nData[i] = sqrt(tens->data[i]);
				break;
			case EXP:
				for (int i = 0; i < tens->len; i++)
					nData[i] = exp(tens->data[i]);
				break;
			case LN:
				for (int i = 0; i < tens->len; i++)
					nData[i] = log(tens->data[i]);
				break;
			case SIN:
				for (int i = 0; i < tens->len; i++)
					nData[i] = sin(tens->data[i]);
				break;
			case COS:
				for (int i = 0; i < tens->len; i++)
					nData[i] = cos(tens->data[i]);
				break;
			case TAN:
				for (int i = 0; i < tens->len; i++)
					nData[i] = tan(tens->data[i]);
				break;
			case SINH:
				for (int i = 0; i < tens->len; i++)
					nData[i] = sinh(tens->data[i]);
				break;
			case COSH:
				for (int i = 0; i < tens->len; i++)
					nData[i] = cosh(tens->data[i]);
				break;
			case TANH:
				for (int i = 0; i < tens->len; i++)
					nData[i] = tanh(tens->data[i]);
				break;
		}

		Tensor *npTens = new Tensor(tens->rank, tens->dimensions, tens->rank);
		npTens->forceSetData(nData);

		return npTens;
	}

	Tensor *outerProd(Tensor *tens1, Tensor *tens2)
	{
		int newRank = tens1->rank + tens2->rank;

		int *newDimensions = (int *)malloc(sizeof(int) * newRank);
		int *newStrides = (int *)malloc(sizeof(int) * newRank);

		// initializing newDimensions
		for (int i = 0; i < tens1->rank; i++)
			newDimensions[i] = tens1->dimensions[i];
		for (int i = 0; i < tens2->rank; i++)
			newDimensions[i + tens1->rank] = tens2->dimensions[i];

		// initializing newStrides
		newStrides[newRank - 1] = 1;

		for (int i = newRank - 1; i > 0; i--)
			newStrides[i - 1] = newDimensions[i] * newStrides[i];

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

	Tensor *tensorDot(Tensor *tens1, Tensor *tens2, int axisNum, int **axisPairs)
	{
			// check all conditions for tensorDot

		// checks for initialization
		if (!tens1->init || !tens2->init)
			throw initEx();

		// checks for too many axes
		if (axisNum > tens1->rank || axisNum > tens2->rank)
			throw shapeEx();

		// checks for out of range axes
		for (int i = 0; i < axisNum; i++) {
			if (axisPairs[0][i] >= tens1->rank)
				throw shapeEx();
			if (axisPairs[1][i] >= tens2->rank)
				throw shapeEx();
		}

		// checks for repeated or decending axes
		for (int i = 0; i < axisNum - 1; i++) {
			if (axisPairs[0][i] >= axisPairs[0][i + 1])
				throw shapeEx();
			if (axisPairs[1][i] >= axisPairs[1][i + 1])
				throw shapeEx();
		}

		// checks if the paired axes have the same dimensions
		for (int i = 0; i < axisNum; i++)
			if (tens1->dimensions[axisPairs[0][i]] != tens2->dimensions[axisPairs[1][i]])
				throw shapeEx();

			// ready to perform tensorDot

		int currAxis;

		// creating t1AxisOrder
		int *t1AxisOrder = (int *)malloc(sizeof(int) * tens1->rank);
		currAxis = 0;
		for (int i = 0; i < tens1->rank - axisNum; i++) {
			while (currAxis == axisPairs[0][currAxis])
				currAxis++;

			t1AxisOrder[i] = currAxis++;
		}
		for (int i = 0; i < axisNum; i++)
			t1AxisOrder[tens1->rank - i - 1] = axisPairs[0][i];

		// creating t2AxisOrder
		int *t2AxisOrder = (int *)malloc(sizeof(int) * tens2->rank);
		currAxis = 0;
		for (int i = 0; i < tens2->rank - axisNum; i++) {
			while (currAxis == axisPairs[1][currAxis])
				currAxis++;

			t2AxisOrder[i] = currAxis++;
		}
		for (int i = 0; i < axisNum; i++)
			t2AxisOrder[tens2->rank - i - 1] = axisPairs[1][i];

		// creating t1Dim
		int *t1Dim = (int *)malloc(sizeof(int) * tens1->rank);
		for (int i = 0; i < tens1->rank; i++)
			t1Dim[i] = tens1->dimensions[t1AxisOrder[i]];

		// creating t2Dim
		int *t2Dim = (int *)malloc(sizeof(int) * tens2->rank);
		for (int i = 0; i < tens2->rank; i++)
			t2Dim[i] = tens2->dimensions[t2AxisOrder[i]];

		// creating t1Srd
		int *t1Srd = (int *)malloc(sizeof(int) * tens1->rank);
		t1Srd[tens1->rank - 1] = 1;
		for (int i = tens1->rank - 2; i >= 0; i--)
			t1Srd[i] = t1Dim[i + 1] * t1Srd[i + 1];

		// creating t2Srd
		int *t2Srd = (int *)malloc(sizeof(int) * tens2->rank);
		t2Srd[tens2->rank - 1] = 1;
		for (int i = tens2->rank - 2; i >= 0; i--)
			t2Srd[i] = t2Dim[i + 1] * t2Srd[i + 1];

		// creating t1Data
		double *t1Data = (double *)malloc(sizeof(double) * tens1->len);
		transposeAxis<double>(tens1->data, tens1->strides, t1AxisOrder, t1Data, t1Dim, t1Srd, tens1->rank);

		// creating t2Data
		double *t2Data = (double *)malloc(sizeof(double) * tens2->len);
		transposeAxis<double>(tens2->data, tens2->strides, t2AxisOrder, t2Data, t2Dim, t2Srd, tens2->rank);
		// finished grouping summed axes by transpose for both

		// getting sumLen
		int sumLen = 1; 
		for (int i = 0; i < axisNum; i++)
			sumLen *= t1Srd[tens1->rank - i];

		// creating nRank
		int nRank = tens1->rank + tens2->rank - 2 * axisNum;

		// creating nDim
		int *nDim = (int *)malloc(sizeof(int) * nRank);
		for (int i = 0; i < tens1->rank - axisNum; i++)
			nDim[i] = tens1->dimensions[i];
		for (int i = 0; i < tens2->rank - axisNum; i++)
			nDim[i + tens1->rank - axisNum] = tens2->dimensions[i];

		// creating nSrd
		int *nSrd = (int *)malloc(sizeof(int) *nRank);
		nSrd[nRank - 1] = 1;
		for (int i = nRank - 1; i > 0; i--) {
			nSrd[i - 1] = nDim[i] * nSrd[i];
		}

		// creating nData
		double *nData = (double *)malloc(sizeof(double) * nSrd[0] * nDim[0]);
		for (int i = 0; i < tens1->rank / sumLen; i++) {
			for (int j = 0; j < tens2->len / sumLen; j++) {
				nData[i * tens2->len / sumLen + j] = 0;
				for (int k = 0; k < sumLen; k++)
					nData[i * tens2->len / sumLen + j] += tens1->data[i * sumLen + k] * tens2->data[j * sumLen + k];
			}
		}

		// creating the Tensor
		Tensor *npTens = new Tensor(nRank, nDim, nSrd);
		npTens->forceSetData(nData);

		// freeing the allocated memory
		free(t1AxisOrder);
		free(t1Dim);
		free(t1Srd);
		free(t1Data);
		
		free(t2AxisOrder);
		free(t2Dim);
		free(t2Srd);
		free(t2Data);

		free(nDim);
		free(nSrd);

		free(axisPairs[0]);
		free(axisPairs[1]);

		return npTens;
	}

}