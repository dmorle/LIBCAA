#include "Matrix.hpp"



namespace LIBCAA {

	matrixParams createMatrixParams(int m, int n)
	{
		int *params = (int *)malloc(sizeof(int) * 2);
		params[0] = m;
		params[1] = n;
		return params;
	}

	Matrix *getIdentity(int size)
	{
		Matrix *nMrx = new Matrix(createMatrixParams(size, size));

		double *nData = (double *)malloc(sizeof(double) * size *size);
		for (int i = 0; i < size * size; i++) {
			if (i / size == i % size)
				nData[i] = 1;
			else
				nData[i] = 0;
		}

		nMrx->forceSetData(nData);

		return nMrx;
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


	// gauss-jordan elimination
	Matrix *Matrix::getInverse()
	{
		// check conditions

		int size = this->dimensions[0];

		Matrix *self = (Matrix *)this->clone();
		Matrix *inv = getIdentity(size);

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
					return NULL;
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

	Matrix * Matrix::transpose() {
		// no checks are needed

		double *nData = (double *)malloc(sizeof(double) * this->len);

		for (int i = 0; i < this->dimensions[0]; i++)
			for (int j = 0; j < this->dimensions[1]; j++)
				nData[j * this->dimensions[0] + i] = this->data[i * this->dimensions[1] + j];

		Matrix *nMrx = new Matrix(createMatrixParams(this->dimensions[1], this->dimensions[1]));
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