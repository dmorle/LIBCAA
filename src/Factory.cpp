#include "Factory.hpp"
#include <stdio.h>



namespace LIBCAA {

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

    Tensor *Factory::usrInit(int rank, int *dimensions)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);
        int *index = (int *)alloca(sizeof(int) * rank);
        for (int i = 0; i < npTens->len; i++) {
            index[0]++;
            for (int j = 0; j < rank; j++) {
                if (index[j] == dimensions[j]) {
                    index[j] = 0;
                    index[j+1]++;
                }
            }

            // printing the current index
            printf("Enter the value for entry ( ");
            printf("%3d", index[0]);
            for (int j = 1; j < rank; j++)
                printf(", %3d", index[j]);
            printf(" ): ");

            scanf("%lf", data + i);
        }

        npTens->forceSetData(data);
        return npTens;
    }

    Matrix *Factory::usrInit(int m, int n)
    {
        int dimensions[] = {m, n};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);
        for (int i = 0; i < npMat->len; i++) {
            printf("Enter the value for entry ( %3d, %3d ): ", i/n, i%n);

            scanf("%lf", data + i);
        }

        npMat->forceSetData(data);
        return npMat;
    }

    Vector *Factory::usrInit(int len) {
        Vector *npVec = new Vector(len);

        double *data = (double *)malloc(sizeof(double) * npVec->len);
        for (int i = 0; i < npVec->len; i++) {
            printf("Enter the value for entry %3d: ", i);

            scanf("%lf", data + i);
        }

        npVec->forceSetData(data);
        return npVec;
    }

    Tensor *Factory::constant(int rank, int *dimensions, double val)
    {
        Tensor *npTens = new Tensor(rank, dimensions);

        double *data = (double *)malloc(sizeof(double) * npTens->len);
        for (int i = 0; i < npTens->len; i++)
            data[i] = val;

        npTens->forceSetData(data);
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

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j)
                    data[i * size + j] = 1;
                else
                    data[i * size + j] = 0;
            }
        }

        npMat->forceSetData(data);
        return npMat;
    }

    Matrix *Factory::derivativeMatrix(int size)
    {
        int dimensions[] = {size - 1, size};
        Matrix *npMat = new Matrix(dimensions);

        double *data = (double *)malloc(sizeof(double) * npMat->len);

        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size; j++) {
                if (j == i + 1)
                    data[i * size + j] = j;
                else
                    data[i * size + j] = 0;
            }
        }

        npMat->forceSetData(data);
        return npMat;
    }

    void Factory::release(void *_obj) {
        Object *obj = (Object *)_obj;
        for (std::string _ : objList)
            if (_ == obj->getType()) {
                delete _obj;
                return;
            }
        
        throw typeEx();
    }

}