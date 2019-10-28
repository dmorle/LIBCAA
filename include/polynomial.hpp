#ifndef POLY_H
#define POLY_H

#include "Vector.hpp"

namespace LIBCAA {

    class polynomial : public Vector{

    public:
        polynomial(std::string name, int degree, double coeff[]);
        polynomial(std::string name, int degree);
        ~polynomial();

        polynomial *clone();

        polynomial *getDerivative();

        double eval(double x);

        std::string name;
    };

}

#endif