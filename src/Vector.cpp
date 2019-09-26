#include "Vector.hpp"



namespace LIBCAA {

	Vector::Vector(int size, double val) : Tensor(1, &size, val)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double *vals) : Tensor(1, &size, vals)
	{
		this->type = "Vector";
	}

	Vector::Vector(int size, double(*initFunc)()) : Tensor(1, &size, initFunc)
	{
		this->type = "Vector";
	}

	Vector::~Vector() {}

}