#ifndef LIBCAAEX_H
#define LIBCAAEX_H

#include <exception>

namespace LIBCAA {

	class initExecption : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Using Uninitialized Array Values";
		}
	} initEx;

}

#endif