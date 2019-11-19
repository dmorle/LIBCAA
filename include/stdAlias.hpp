#ifdef USE_OBJ_MACROS

    typedef LIBCAA::Tensor *tensor;
    typedef LIBCAA::Matrix *matrix;
    typedef LIBCAA::Vector *vector;

#elif

    #define USE_OBJ_MACROS

#endif

#ifdef USE_OP_MACROS

    #ifndef NO_BASIC_OPS
        #define add LIBCAA::add
        #define sub LIBCAA::sub
        #define mul LIBCAA::mul
        #define div LIBCAA::div
        #define pow LIBCAA::pow
    #endif

    #ifndef NO_UNARY_OPS
        #define iadd LIBCAA::iadd
        #define isub LIBCAA::isub
        #define imul LIBCAA::imul
        #define idiv LIBCAA::idiv
        #define ipow LIBCAA::ipow
    #endif 

    #ifndef NO_COMPARISON_OPS
        #define eq LIBCAA::eq
        #define ne LIBCAA::ne
        #define gt LIBCAA::gt
        #define lt LIBCAA::lt
        #define le LIBCAA::le
        #define ge LIBCAA::ge
    #endif

    #ifndef NO_TENSOR_OPS
        #define trans LIBCAA::transpose
        #define collapseAxis LIBCAA::collapseAxis
        #define applyFunc LIBCAA::applyFunc
        #define outerProd LIBCAA::outerProd
        #define innerProd LIBCAA::innerProd
        #define tensorDot LIBCAA::tensorDot
    #endif

    #ifndef NO_MATRIX_OPS
        #define trans LIBCAA::transpose
        #define inv LIBCAA::getInverse
        #define det LIBCAA::determinant
        #define getDiagonal LIBCAA::getDiagonal
        #define matmul LIBCAA::matmul
        #define concat LIBCAA::concat
    #endif

    #ifndef NO_VECTOR_OPS
        #define dot LIBCAA::dotProd
        #define cross LIBCAA::crossProd
        #define matmul LIBCAA::matmul
    #endif

#elif

    #define USE_OP_MACROS

#endif