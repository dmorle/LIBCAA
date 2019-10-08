#include "LIBCAAEX.hpp"

namespace LIBCAA {

	const char * initEx::what() const throw()
	{
		return "array data does not exist";
	}

	const char * reinitEx::what() const throw()
	{
		return "variable already exists";
	}

	const char * shapeEx::what() const throw()
	{
		return "unmatching shapes";
	}

	const char * typeEx::what() const throw()
	{
		return "unmatching types";
	}

}