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
    cv::Rect2d getBBox(double centreX, double centreY, double width, double height);
    cv::Rect2d clipBBox(cv::Rect2d bbox, double imgW, double imgH);
    void sharpen(cv::Mat& m);
    void colourMask(
            cv::Mat& m,
            cv::Mat& output,
            cv::Vec3b colourMinHSV, 
            cv::Vec3b colourMaxHSV
    );
};

#endif /* __TRACKER_HPP__ */
