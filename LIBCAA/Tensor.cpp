#include "Tensor.h"



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

	Tensor Tensor::operator+(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator+(double val)
	{
		return Tensor();
	}

	Tensor Tensor::operator-(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator-(double val)
	{
		return Tensor();
	}

	Tensor Tensor::operator*(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator*(double val)
	{
		return Tensor();
	}

	Tensor Tensor::operator/(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator/(double val)
	{
		return Tensor();
	}

	Tensor Tensor::operator^(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator^(double val)
	{
		return Tensor();
	}

	Tensor LIBCAA::Tensor::operator%(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator%(double val)
	{
		return Tensor();
	}

	void Tensor::operator+=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator+=(double val)
	{
	}

	void Tensor::operator-=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator-=(double val)
	{
	}

	void Tensor::operator*=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator*=(double val)
	{
	}

	void Tensor::operator/=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator/=(double val)
	{
	}

	void Tensor::operator^=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator^=(double val)
	{
	}

	void Tensor::operator%=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	void Tensor::operator%=(double val)
	{
	}

	Tensor Tensor::operator==(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator!=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator>=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

	Tensor Tensor::operator<=(Tensor tens)
	{
		if (!sameShape(this, &tens))
			throw shapeEx;
	}

}