#ifndef OBJECT_H
#define OBJECT_H

namespace LIBCAA {

	// abstract class which all other classes will inherit from
	// all classes need to be able to be cloned and have a cmd repr

	class Object
	{
	public:
		virtual void clone(void *) = 0;	// virtual clone function to be overridden
		virtual void print() = 0;		// virtual print function to be overridden

		std::string type() { return this->type; }

	protected:
		std::string type;
	};

}

#endif