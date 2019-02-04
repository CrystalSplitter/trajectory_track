#include <opencv2/opencv.hpp>

static void help(char* progName);
int sharpenProc(int argc, char* argv[]);
void sharpen(const cv::Mat& myImage, cv::Mat& Result);
