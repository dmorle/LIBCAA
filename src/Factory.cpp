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

    Tensor *Factory::constant(int rank, int *dimensions, double val = 0)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);
        for (int i = 0; i < npTens->len; i++)
            data[i] = val;

        npTens->forceSetData(data);
        npTens->init = true;
        return npTens;
    }

    Matrix *Factory::constant(int m, int n, double val = 0)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);
        for (int i = 0; i < npMat->len; i++)
            data[i] = val;

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::constant(int len, double val = 0)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * npVec->len);
        for (int i = 0; i < len; i++)
            data[i] = val;

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::arange(int rank, int *dimensions, double start = 0)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        for (int i = 0; i < npTens->len; i++)
            data[i] = start + i;

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::arange(int m, int n, double start = 0)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        for (int i = 0; i < npMat->len; i++)
            data[i] = start + i;

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::arange(int len, double start = 0)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * len);

        for (int i = 0; i < len; i++)
            data[i] = start + i;

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::uniDist(int rank, int *dimensions, double min = 0, double max = 1)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        // TODO: initialize data

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::uniDist(int m, int n, double min = 0, double max = 1)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::uniDist(int len, double min = 0, double max = 1)
    {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * len);

        // TODO: initialize data

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::normDist(int rank, int *dimensions, double mean = 0, double stdDev = 1)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);

        // TODO: initialize data

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::normDist(int m, int n, double mean = 0, double stdDev = 1)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        // TODO: initialize data

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::normDist(int len, double mean = 0, double stdDev = 1)
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