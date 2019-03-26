#include <opencv2/opencv.hpp>

#ifndef __TRACKER_HPP__
#define __TRACKER_HPP__

static void help(char* progName);
namespace tr
{
    int trackerProc(cv::VideoCapture& vidCap, int frameStart);
    int updateMatrices(
            cv::VideoCapture& vidCap,
            cv::Mat& frame,
            cv::Mat& shrinkFrame,
            cv::Mat& grey,
            cv::Mat& oldgrey,
            cv::Size newSize);
    void sharpen(cv::Mat& m);
};

#endif /* __TRACKER_HPP__ */
