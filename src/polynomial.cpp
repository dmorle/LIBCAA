#include "polynomial.hpp"
#include "Factory.hpp"
#include "Vector.hpp"

namespace LIBCAA
{

    polynomial::polynomial(std::string name, int degree, double *coeff) : Vector(degree + 1, coeff) {
        this->type = "poly";
        this->name = name;
    }

    polynomial::polynomial(std::string name, int degree) : Vector(degree + 1) {
        this->type = "poly";
        this->name = name;
    }

    polynomial::~polynomial() { }

    double polynomial::eval(double x) {
        Factory fact = Factory();
        Vector *vec = fact.arange(len);
        ipow(x, vec);

        double result = dotProd(this, vec);

        delete vec;
        return result;
    }

    polynomial *polynomial::clone() {
        polynomial *npPoly = new polynomial(name, len - 1, data);
        return npPoly;
    }

    polynomial *polynomial::getDerivative() {
        Factory fact = Factory();

        Matrix *dMat = fact.derivativeMatrix(len);
        Vector *result = matmul(dMat, (Vector *)this);
        polynomial *npPoly = new polynomial(name + (std::string)"Derivative", len - 2);

        double *nData = (double *)malloc(sizeof(double) * (len - 1));
        for (int i = 0; i < len - 1; i++)
            nData[i] = result->getAbsIndex(i);

        npPoly->forceSetData(nData);

        delete dMat;
        delete result;

        return npPoly;
    }

}