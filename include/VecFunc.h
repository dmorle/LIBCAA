#ifndef VECFUNC_H
#define VECFUNC_H

#include "Vector.h"

namespace LIBCAA {

	class VecFunc : public Object
	{
	public:
		virtual Vector *eval(Vector *inputs) = 0;

	protected:
		int inDim;
		int outDim;
	};

}

#endif