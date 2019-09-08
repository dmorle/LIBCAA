#ifndef LIBCAAEX_H
#define LIBCAAEX_H

#include <exception>

namespace LIBCAA {

	class initExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "array data does not exist";
		}
	} initEx;

	class shapeExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "unmatching shapes";
		}
	} shapeEx;

}

#endif