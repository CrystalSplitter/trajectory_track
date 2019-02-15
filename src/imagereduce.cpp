#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "imagereduce.hpp"

using namespace cv;

unsigned char* generateDivLookUp(unsigned char div, bool reduce)
{
    unsigned char* lookupTable = (unsigned char*) malloc(sizeof(char)*256);
    if (div == 0) {
        return nullptr;
    }
    for (unsigned int i = 0; i < 256; ++i) {
        if (reduce) {
            lookupTable[i] = i/div;
        } else {
            lookupTable[i] = div * (i/div);
        }
    }
    return lookupTable;
}

void imageReduce(Mat& m, unsigned char* lookupTable)
{
    // Get how many channels m has.
    size_t channels = m.channels();
    size_t rows = m.rows;
    size_t cols = m.cols;
    
    for (size_t i = 0; i < rows; ++i) {
        // Get a pointer to the row.
        uchar* ptr = m.ptr<uchar>(i);
        for (size_t j = 0; j < cols * channels; ++j) {
            *ptr = lookupTable[*ptr];
            ++ptr;
        }
    }
}
