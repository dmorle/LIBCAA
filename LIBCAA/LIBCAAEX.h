#ifndef LIBCAAEX_H
#define LIBCAAEX_H

#include <exception>

namespace LIBCAA {

	// data variable of a MDA or derived class has not been created
	class initExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "array data does not exist";
		}
	} initEx;

	// forced re-initialization of existing variable
	class reinitExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "variable already exists";
		}
	} reinitEx;

	// operation is called on a Tensor or derived class which have different shapes
	class shapeExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "unmatching shapes";
		}
	} shapeEx;

}

#endif