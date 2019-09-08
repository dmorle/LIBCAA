#ifndef INITFUNC_H
#define INITFUNC_H

namespace LIBCAA {

	// initialization functions
	namespace INIT {

		// initializes sequential elements using the ++ operator
		template <typename dataType> dataType arange() {
			static dataType val = 0;
			return val++;
		}

	}
}

#endif