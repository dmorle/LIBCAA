#ifndef OBJECT_H
#define OBJECT_H

namespace LIBCAA {

	class Object
	{
	public:
		virtual Object *clone() = 0;
		virtual void print() = 0;
	};

}

#endif