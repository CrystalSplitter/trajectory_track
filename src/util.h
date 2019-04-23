#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>

namespace util
{
    /*!
     * Return the max of a vector.
     * \param vec Vector to get max of.
     */
    template <class T>
    unsigned int argvecmax(std::vector<T> vec)
    {
        if (vec.size() < 1) {
            return -1;
        }

        unsigned int currentMaxIt = 0;
        T currentMax = vec[currentMaxIt];
        for (unsigned int it = 0; it != vec.size(); ++it) {
            if (currentMax < vec[it]) {
                currentMax = vec[it];
                currentMaxIt = it;
            }
        }
        return currentMaxIt;
    }

    template <typename T>
    unsigned int argvecmin(std::vector<T> vec)
    {
        if (vec.size() < 1) {
            return -1;
        }

        unsigned int currentMinIt = 0;
        T currentMin = vec[currentMinIt];
        for (unsigned int it = 0; it != vec.size(); ++it) {
            if (vec[it] < currentMin) {
                currentMin = vec[it];
                currentMinIt = it;
            }
        }
        return currentMinIt;
    }
};

#endif /* __UTIL_H__ */
