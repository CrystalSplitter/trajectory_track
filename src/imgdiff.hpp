#ifndef __IMGDIFF_HPP__
#define __IMGDIFF_HPP__

#include <opencv2/opencv.hpp>

class ImgDiff {

public:
    void diff(cv::Mat& to, cv::Mat& from,
            cv::Mat& diff, int dilateThresh=0);
    
    /* Calculate the average pixel position of pixels
     * that exceed the threshold in any channel.
     */
    cv::Point diffThreshCentre(cv::Mat& diff, unsigned char threshold,
            cv::Mat& output);

    cv::Point centre_;
    cv::Rect boundingBox_;
};

#endif /* __IMGDIFF_HPP__ */
