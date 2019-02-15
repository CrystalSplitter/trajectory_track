#include <opencv2/opencv.hpp>

/**
 * Generates a lookup table for chars. An array of length 255 is produced which
 * can be indexed to produce the desired value.
 */
unsigned char* generateDivLookUp(unsigned char div, bool reduce);

/**
 * Reduces an image using a lookup table.
 */
void imageReduce(cv::Mat& m, unsigned char* lookupTable);

