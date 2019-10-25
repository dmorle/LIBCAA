#include "Factory.hpp"



namespace LIBCAA {

    Factory::Factory() {}

    Factory::~Factory() {}

    Tensor *Factory::noInit(int rank, int *dimensions)
    {
        Tensor *npTens = new Tensor(rank, dimensions);
        npTens->init = false;

        return npTens;
    }

    Matrix *Factory::noInit(int m, int n)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);
        npMat->init = false;

        return npMat;
    }

    Vector *Factory::noInit(int len)
    {
        Vector *npVec = new Vector(len);
        npVec->init = false;

        return npVec;
    }

    Tensor *Factory::constant(int rank, int *dimensions, double val)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);
        for (int i = 0; i < npTens->len; i++)
            data[i] = val;

        npTens->forceSetData(data);
        npTens->init = true;
        return npTens;
    }

    Matrix *Factory::constant(int m, int n, double val)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);
        for (int i = 0; i < npMat->len; i++)
            data[i] = val;

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::constant(int len, double val)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * npVec->len);
        for (int i = 0; i < len; i++)
            data[i] = val;

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::arange(int rank, int *dimensions, double start)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        for (int i = 0; i < npTens->len; i++)
            data[i] = start + i;

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::arange(int m, int n, double start)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        for (int i = 0; i < npMat->len; i++)
            data[i] = start + i;

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::arange(int len, double start)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * len);

        for (int i = 0; i < len; i++)
            data[i] = start + i;

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::uniDist(int rank, int *dimensions, double min, double max)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        // TODO: initialize data

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::uniDist(int m, int n, double min, double max)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::uniDist(int len, double min, double max)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * len);

        // TODO: initialize data

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::normDist(int rank, int *dimensions, double mean, double stdDev)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        // TODO: initialize data

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::normDist(int m, int n, double mean, double stdDev)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::normDist(int len, double mean, double stdDev)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * len);

        // TODO: initialize data

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::leviCivita(int rank, int *dimensions)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        // TODO: initialize data

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::identity(int size)
    {
        int dimensions[] = {size, size};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

    Matrix *Factory::derivativeMatrix(int size)
    {
        int dimensions[] = {size, size};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

}