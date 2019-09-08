#include "MDA.h"

namespace LIBCAA {

	bool sameShape(int rank1, int *dimensions1, int rank2, int *dimensions2) {
		if (rank1 != rank2)
			return false;

		for (int i = 0; i < rank1; i++)
			if (dimensions1[i] != dimensions2[i])
				return false;

		return true;
	}

	bool sameShape(int shapeNum, int *ranks, int **dimensions) {
		for (int i = 0; i < shapeNum; i++)
			for (int j = i + 1; j < shapeNum; j++)
				if (ranks[i] != ranks[j])
					return false;

		for (int i = 0; i < shapeNum; i++)
			for (int j = i + 1; j < shapeNum; j++)
				for (int k = 0; k < *ranks; k++)
					if (dimensions[i][k] != dimensions[j][k])
						return false;

		return true;
	}

}