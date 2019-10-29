#ifndef LIBCAAEX_H
#define LIBCAAEX_H

#include <exception>

namespace LIBCAA {

    // data variable of a MDA or derived class has not been created
	class initEx : public std::exception
	{
		virtual const char * what() const throw();
	};

	// forced re-initialization of existing variable
	class reinitEx : public std::exception
	{
		virtual const char * what() const throw();
	};

	// operation is called on a Tensor or derived class which have different shapes
	class shapeEx : public std::exception
	{
		virtual const char * what() const throw();
	};

	// type given to a function is invalid
	class typeEx : public std::exception
	{
		virtual const char * what() const throw();
	};

	// operation is called on a Tensor or derived class which requires an inverse; the inverse does not exist
	class invEx : public std::exception
	{
		virtual const char * what() const throw();
	};

}

#endif