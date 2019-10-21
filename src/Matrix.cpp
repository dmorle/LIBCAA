#include "Matrix.hpp"

#ifndef INITFUNC_H
#include "InitFunc.hpp"
#endif



namespace LIBCAA {

	matrixParams createMatrixParams(int m, int n)
	{
		int *params = (int *)malloc(sizeof(int) * 2);
		params[0] = m;
		params[1] = n;
		return params;
	}

	Matrix::Matrix(matrixParams params) : Tensor(2, params)
	{
		this->type = "Matrix";
	}

	Matrix::Matrix(matrixParams params, double val) : Tensor(2, params, val)
	{
		this->type = "Matrix";
	}

	Matrix::Matrix(matrixParams params, double **val) : Tensor(2, params)
	{
		// flattening val into this->data
		this->data = (double *)malloc(sizeof(double) * this->len);
		for (int i = 0; i < this->dimensions[0]; i++)
			for (int j = 0; j < this->dimensions[1]; j++)
				this->data[i*strides[0]] = val[i][j];

		this->init = true;
		this->type = "Matrix";
	}

	Matrix::Matrix(matrixParams params, double(*initFunc)()) : Tensor(2, params, initFunc)
	{
		this->type = "Matrix";
	}

	Matrix *Matrix::clone() {
		return (Matrix *) MDA::clone();
	}

	void Matrix::setIndex(int i, int j, double val)
	{
		this->data[i*this->strides[0] + j] = val;
	}

	double Matrix::getAbsIndex(int i, int j)
	{
		return this->data[i*this->strides[0] + j];
	}

	double Matrix::getIndex(int i, int j)
	{
		return getAbsIndex(i % this->dimensions[0], j % this->dimensions[1]);
	}

	void Matrix::scaleRow(int rowNum, double scale)
	{
		for (int i = 0; i < this->dimensions[1]; i++)
			this->data[rowNum * this->strides[0] + i] *= scale;
	}

	void Matrix::switchRows(int row1, int row2)
	{
		for (int i = 0; i < this->dimensions[1]; i++) {
			double temp = this->data[row1 * strides[0] + i];
			this->data[row1 * strides[0] + i] = this->data[row2 * strides[0] + i];
			this->data[row2 * strides[0] + i] = temp;
		}
	}

	// row1 = row1 - scale *row2
	void Matrix::rowSub(int row1, int row2, double scale)
	{
		for (int i = 0; i < this->dimensions[1]; i++)
			this->data[row1 * this->strides[0] + i] -= scale * this->data[row2 * this->strides[0] + i];
	}

	void Matrix::opExcept(Matrix *mrx)
	{
		// checking if operation can be performed
		if (
			mrx->dimensions[0] != this->dimensions[0] ||
			mrx->dimensions[1] != this->dimensions[1]
			)
			throw shapeEx();

		// checking if both matricies are initialized
		if (!this->init || !mrx->getInit())
			throw initEx();
	}

	Matrix *add(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		double *nData = (double *)malloc(sizeof(double) * mrx1->len);
		for (int i = 0; i < mrx1->len; i++)
			nData[i] = mrx1->data[i] + mrx2->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx1->dimensions[0], mrx1->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *add(Matrix *mrx, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = mrx->data[i] + val;

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *add(double val, Matrix *mrx)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = val + mrx->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}
	
	Matrix *sub(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		double *nData = (double *)malloc(sizeof(double) * mrx1->len);
		for (int i = 0; i < mrx1->len; i++)
			nData[i] = mrx1->data[i] - mrx2->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx1->dimensions[0], mrx1->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *sub(Matrix *mrx, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = mrx->data[i] - val;

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *sub(double val, Matrix *mrx)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = val - mrx->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *mul(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		double *nData = (double *)malloc(sizeof(double) * mrx1->len);
		for (int i = 0; i < mrx1->len; i++)
			nData[i] = mrx1->data[i] * mrx2->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx1->dimensions[0], mrx1->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *mul(Matrix *mrx, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = mrx->data[i] * val;

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *mul(double val, Matrix *mrx)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = val * mrx->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *div(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		double *nData = (double *)malloc(sizeof(double) * mrx1->len);
		for (int i = 0; i < mrx1->len; i++)
			nData[i] = mrx1->data[i] / mrx2->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx1->dimensions[0], mrx1->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *div(Matrix *mrx, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = mrx->data[i] / val;

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *div(double val, Matrix *mrx)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = val / mrx->data[i];

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *pow(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		double *nData = (double *)malloc(sizeof(double) * mrx1->len);
		for (int i = 0; i < mrx1->len; i++)
			nData[i] = std::pow(mrx1->data[i], mrx2->data[i]);

		Matrix *npMrx = new Matrix(createMatrixParams(mrx1->dimensions[0], mrx1->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *pow(Matrix *mrx, double val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = std::pow(mrx->data[i], val);

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *pow(double val, Matrix *mrx)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = std::pow(val, mrx->data[i]);

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *pow(Matrix *mrx, int val)
	{
		double *nData = (double *)malloc(sizeof(double) * mrx->len);
		for (int i = 0; i < mrx->len; i++)
			nData[i] = std::pow(mrx->data[i], val);

		Matrix *npMrx = new Matrix(createMatrixParams(mrx->dimensions[0], mrx->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}


	Matrix *addAcc(int len, Matrix **mrxArr)
	{
		for (int i = 1; i < len; i++)
			mrxArr[0]->opExcept(mrxArr[i]);

		double *nData = (double *)calloc(mrxArr[0]->len, sizeof(double));

		for (int i = 0; i < mrxArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] += mrxArr[j]->data[i];
		
		Matrix *npMrx = new Matrix(createMatrixParams(mrxArr[0]->dimensions[0], mrxArr[0]->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}

	Matrix *mulAcc(int len, Matrix **mrxArr)
	{
		for (int i = 1; i < len; i++)
			mrxArr[0]->opExcept(mrxArr[i]);

		double *nData = (double *)malloc(sizeof(double) * mrxArr[0]->len);
		for (int j = 0; j < mrxArr[0]->len; j++)
			nData[j] = mrxArr[0]->data[j];

		for (int i = 1; i < mrxArr[0]->len; i++)
			for (int j = 0; j < len; j++)
				nData[j] *= mrxArr[j]->data[i];
		
		Matrix *npMrx = new Matrix(createMatrixParams(mrxArr[0]->dimensions[0], mrxArr[0]->dimensions[1]));
		npMrx->forceSetData(nData);

		return npMrx;
	}
	

	void iadd(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		for (int i = 0; i < mrx1->len; i++)
			mrx1->data[i] += mrx2->data[i];
	}

	void iadd(Matrix *mrx, double val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] += val;
	}

	void iadd(double val, Matrix *mrx)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] += val;
	}

	void isub(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		for (int i = 0; i < mrx1->len; i++)
			mrx1->data[i] -= mrx2->data[i];
	}

	void isub(Matrix *mrx, double val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] -= val;
	}

	void isub(double val, Matrix *mrx)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] = val - mrx->data[i];
	}

	void imul(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		for (int i = 0; i < mrx1->len; i++)
			mrx1->data[i] *= mrx2->data[i];
	}

	void imul(Matrix *mrx, double val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] *= val;
	}

	void imul(double val, Matrix *mrx)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] *= val;
	}

	void idiv(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		for (int i = 0; i < mrx1->len; i++)
			mrx1->data[i] /= mrx2->data[i];
	}

	void idiv(Matrix *mrx, double val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] /= mrx->data[i];
	}

	void idiv(double val, Matrix *mrx)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] = val/mrx->data[i];
	}

	void ipow(Matrix *mrx1, Matrix *mrx2)
	{
		mrx1->opExcept(mrx2);

		for (int i = 0; i < mrx1->len; i++)
			mrx1->data[i] = std::pow(mrx1->data[i], mrx2->data[i]);
	}

	void ipow(Matrix *mrx, double val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] = std::pow(mrx->data[i], val);
	}

	void ipow(double val, Matrix *mrx)
	{
		for (int i = 0; i , mrx->len; i++)
			mrx->data[i] = std::pow(val, mrx->data[i]);
	}

	void ipow(Matrix *mrx, int val)
	{
		for (int i = 0; i < mrx->len; i++)
			mrx->data[i] = std::pow(mrx->data[i], val);
	}


	// gauss-jordan elimination
	Matrix *getInverse(Matrix *mrx)
	{
		// check conditions
		// TODO: check for square and init

		int size = mrx->dimensions[0];

		Matrix *self = mrx->clone();
		Matrix *inv = new Matrix(createMatrixParams(size, size), createIdentityMatrix(size));

		for (int i = 0; i < size; i++) {

			/*
			std::cout << "self:" << std::endl;
			self->print();
			std::cout << "inverse:" << std::endl;
			inv->print();
			std::cout << "row swapping" << std::endl;
			*/

			double leadCoeff = self->getAbsIndex(i, i);
			if (leadCoeff == 0) {
				// find a row with a non-zero value at pos i
				int j;
				for (j = i + 1; j < size; j++) {
					if (self->getAbsIndex(j, i) != 0) {
						self->switchRows(i, j);
						inv->switchRows(i, j);
						break;
					}
				}
				if (j == size) {
					// could not find an inverse
					delete self;
					delete inv;
					throw invEx();
				}
				leadCoeff = self->getAbsIndex(i, i);
			}

			/*
			std::cout << "self:" << std::endl;
			self->print();
			std::cout << "inverse:" << std::endl;
			inv->print();
			std::cout << "row scaling" << std::endl;
			*/

			if (leadCoeff != 1) {
				self->scaleRow(i, 1 / leadCoeff);
				inv->scaleRow(i, 1 / leadCoeff);
			}
			/*
			std::cout << "self:" << std::endl;
			self->print();
			std::cout << "inverse:" << std::endl;
			inv->print();
			std::cout << "row subs" << std::endl;
			*/

			// the leading coefficient is now 1, subtract the rows
			for (int j = 0; j < size; j++) {
				if (j != i) {
					double scale = self->getAbsIndex(j, i);
					self->rowSub(j, i, scale);
					inv->rowSub(j, i, scale);
				}
			}

			/*
			std::cout << "self:" << std::endl;
			self->print();
			std::cout << "inverse:" << std::endl;
			inv->print();
			std::cout << std::endl << std::endl;
			*/
		}

		delete self;

		return inv;
	}

	double determinant(Matrix *mrx) {

		// check conditions
		// TODO: check for square and init
		
		int size = mrx->dimensions[0];

		Matrix *self = mrx->clone();

		double det = 1;

		for (int i = 0; i < size; i++) {
			double leadCoeff = self->getAbsIndex(i, i);

			// swapping rows if a 0 was found in the leading coefficient
			if (leadCoeff == 0) {
				// find a row with a non-zero value at pos i
				int j;
				for (j = i + 1; j < size; j++) {
					if (self->getAbsIndex(j, i) != 0) {
						self->switchRows(i, j);
						det *= -1;
						break;
					}
				}
				if (j == size) {
					delete self;
					return 0;
				}
				leadCoeff = self->getAbsIndex(i, i);
			}

			// scaling row for easier computation
			if (leadCoeff != 1) {
				self->scaleRow(i, 1 / leadCoeff);
				det *= leadCoeff;
			}

			// row elimination
			for (int j = i + 1; j < size; j++) {
				double scale = self->getAbsIndex(j, i);
				self->rowSub(j, i, scale);
			}
		}

		delete self;

		return det;
	}

	Matrix * transpose(Matrix *mrx) {
		// no checks are needed

		double *nData = (double *)malloc(sizeof(double) * mrx->len);

		for (int i = 0; i < mrx->dimensions[0]; i++)
			for (int j = 0; j < mrx->dimensions[1]; j++)
				nData[j * mrx->dimensions[0] + i] = mrx->data[i * mrx->dimensions[1] + j];

		Matrix *nMrx = new Matrix(createMatrixParams(mrx->dimensions[1], mrx->dimensions[1]));
		nMrx->forceSetData(nData);

		return nMrx;
	}

	Matrix *matmul(Matrix *mat1, Matrix *mat2)
	{
		// checking if multiplcation is possible
		if (mat1->dimensions[1] != mat2->dimensions[0])
			throw shapeEx();

		double *nData = (double *)malloc(sizeof(double) * mat1->dimensions[0] * mat2->dimensions[1]);
		for (int i = 0; i < mat1->dimensions[0]; i++) {
			for (int j = 0; j < mat2->dimensions[1]; j++) {
				nData[i * mat1->dimensions[1] + j] = 0;
				for (int k = 0; k < mat1->dimensions[1]; k++)
					nData[i * mat1->dimensions[1] + j] += mat1->getAbsIndex(i, k) * mat2->getAbsIndex(k, j);
			}
		}

		Matrix *nMrx = new Matrix(createMatrixParams(mat1->dimensions[0], mat2->dimensions[1]));
		nMrx->forceSetData(nData);

		return nMrx;
	}

}