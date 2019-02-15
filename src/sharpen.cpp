#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>

#include "imagereduce.hpp"
#include "sharpen.hpp"
#include "imgdiff.hpp"

using namespace std;

static void help(char* progName)
{
    cout << endl << "Sharpens an image based using a kernel" << endl;
}

int sharpenProc(int argc, char* argv[])
{
    const char* filename1 = (argc >= 2) ? argv[1] : nullptr;
    const char* filename2 = (argc >= 3) ? argv[2] : nullptr;
    if (!filename1 || !filename2) {
        help(argv[0]);
        return -1;
    }
    
    cv::Mat sharpened;
    cv::Mat scaled1;
    cv::Mat scaled2;
    
    cv::Mat src1 = cv::imread(filename1, cv::IMREAD_COLOR);
    cv::Mat src2 = cv::imread(filename2, cv::IMREAD_COLOR);
    printf("width: %d\n", src1.cols);
    printf("height: %d\n", src1.rows);
    
    auto start = std::chrono::high_resolution_clock::now();
    // Conduct resize.
    cv::resize(src1, scaled1, cv::Size(src1.cols/4, src2.rows/4), 0, 0,
            cv::INTER_NEAREST);
    cv::resize(src2, scaled2, cv::Size(src2.cols/4, src2.rows/4), 0, 0,
            cv::INTER_NEAREST);
    
    cv::Mat delta = cv::Mat(scaled2.cols, scaled2.rows, CV_8UC3);
    ImgDiff::diff(scaled2, scaled1, delta, 0);
    ImgDiff::diffThreshCentre(delta, 10);
    
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = stop - start;

    std::cout << "Calcs Per Sec: " << 1.0/elapsed_seconds.count() << std::endl;
    /*
    printf("Generating Lookup\n");
    unsigned char* lookup = generateDivLookUp(50, false);
    printf("Reducing...\n");
    imageReduce(scaled, lookup);
    printf("Reduced!\n");
    sharpen(scaled);
    printf("Masked!\n");
    */

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    printf("swidth: %d\n", delta.cols);
    printf("sheight: %d\n", delta.rows);
    cv::imshow("Display Image", delta);
    cv::waitKey(0);
    return 0;
}

void sharpen(cv::Mat& m)
{
    cv::Mat hsv;
    cv::cvtColor(m, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV, 0);
    for (size_t i = 0; i < hsv.rows; ++i) {
        unsigned char* hsvRowStart = hsv.ptr<unsigned char>(i);
        unsigned char* mRowStart = m.ptr<unsigned char>(i);
        for (size_t j = 0; j < hsv.cols*hsv.channels(); j += 3) {
            unsigned char* h = hsvRowStart;
            unsigned char* b = mRowStart;
            unsigned char* g = mRowStart + 1;
            unsigned char* r = mRowStart + 2;
            if (*h > 0 && *h < 40) {
                *b = 0;
                *g = 0;
                *r = 255;
            }
            hsvRowStart += 3;
            mRowStart += 3;
        }
    }
}
