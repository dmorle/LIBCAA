#ifndef DATASET_H
#define DATASET_H

#include <string>

namespace LIBCAA {

    template <typename dataType> class dataSet : public MDA<> {

    public:
        // no implimentation yet
        dataSet(std::string csvFile);

        dataSet()
        ~dataSet();
    };

}

#endif