#ifndef OBJECT_H
#define OBJECT_H

#include "LIBCAAEX.h"
#include <string>

namespace LIBCAA {

	// abstract class which all other classes will inherit from
	// all classes need to be able to be cloned and have a cmd repr

	class Object
	{
	public:
		virtual void *clone() = 0;		// virtual clone function to be overridden
		virtual void print() = 0;		// virtual print function to be overridden

		std::string getType() { return this->type; }

	protected:
		std::string type;
	};

}

#endif