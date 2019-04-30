#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <stdexcept>
#include <algorithm>

#include "inputhandler.hpp"
#include "imagereduce.hpp"
#include "tracker.hpp"
#include "imgdiff.hpp"


const int TR_NEWWIDTH = 128*4;

const int TR_BBOX_WIDTH = 35;
const int TR_BBOX_HEIGHT = 35;

const double FPS = 20;

int tr::trackerProc(cv::VideoCapture& vidCap, int frameStart, std::string outfile)
{
    cv::Ptr<cv::Tracker> tracker;
    cv::Mat frame;
    vidCap.read(frame); // Get the first frame.
    cv::Mat shrinkFrame;
    cv::Mat greysc;
    cv::Mat oldgreysc;
    cv::VideoWriter output;

    // Calculate the size of the rescale.
    float aspectRatio = ((float) frame.cols)/((float) frame.rows);
    cv::Size newSize = cv::Size(640/2,480/2);/*cv::Size(TR_NEWWIDTH,
            (int) TR_NEWWIDTH/aspectRatio);*/

    // Open a video output stream.
    output.open(outfile, cv::VideoWriter::fourcc('M','J','P','G'),
                FPS, newSize, true);

    if (!output.isOpened()) {
        throw std::runtime_error("Output video could not be opened.");
    }

    cv::Mat diffFrame(cv::Mat(newSize, CV_8UC1));
    cv::Mat diffMask(cv::Mat(newSize, CV_8UC1));
    // Get the first frame.
    tr::updateMatrices(vidCap, frame, shrinkFrame, greysc, oldgreysc, newSize);

    cv::Mat colourMask = cv::Mat(newSize, CV_8UC1);

    // Skip ahead specified number of frames.
    for (int i = 1; i < frameStart; ++i) {
        tr::updateMatrices(vidCap, frame, shrinkFrame, greysc,
                oldgreysc, newSize);
    }

    cv::Rect2d bbox = tr::getBBox(shrinkFrame.cols/2, shrinkFrame.rows/2, 40, 40);
    bbox = tr::clipBBox(bbox, shrinkFrame.cols, shrinkFrame.rows);

    // Display the bounding box.
    cv::rectangle(shrinkFrame, bbox, cv::Scalar(255, 0, 0), 1, 1);

    // Create the tracker.
    tracker = cv::TrackerMOSSE::create();
    tracker->init(greysc, bbox);

    // Create the difference calculator.
    ImgDiff imgdiff = ImgDiff();
    unsigned int counter = 0;
    while(tr::updateMatrices(
                vidCap,
                frame,
                shrinkFrame,
                greysc,
                oldgreysc,
                newSize))
    {
        cv::rectangle(shrinkFrame, bbox, cv::Scalar(255, 0, 0), 1, 1);

        // If the frame is empty, break immediately
        if (frame.empty()) {
            break;
        }

        // Compute the colour mask.
        tr::colourMask(
                shrinkFrame,
                colourMask,
                cv::Vec3b(5,100,0),
                cv::Vec3b(75,255,200)
        );

        bool trackOkay = tracker->update(greysc, bbox);
        if (trackOkay) {
            cv::rectangle(shrinkFrame, bbox, cv::Scalar(255, 0, 0), 1, 1);
        } else {
            std::cout << "Failing to track" << std::endl;
        }

        // Compute the difference between now and before.
        imgdiff.diff(greysc, oldgreysc, diffFrame, 4);
        imgdiff.diffThreshCentre(diffFrame, 20, diffMask);

        cv::Mat tempDiffConverted(newSize, CV_8UC3);
        cv::cvtColor(diffMask, tempDiffConverted,
                cv::ColorConversionCodes::COLOR_GRAY2BGR, 0);

        cv::rectangle(tempDiffConverted, imgdiff.boundingBox_,
                cv::Scalar(0, 255, 0), 1, 1
        );
        cv::rectangle(tempDiffConverted, imgdiff.centre_, imgdiff.centre_,
                cv::Scalar(0, 0, 255), -2, 1
        );

        // Display the resulting frames.
        //cv::imshow("Diff", diffMask);
        output.write(tempDiffConverted);
        cv::imshow("Display Image", tempDiffConverted);
        cv::waitKey(20);

        // Press  ESC on keyboard to exit
        if (counter > 360) {
            break;
        } else {
            counter++;
        }
    }
    output.release();
    return 0;
}

int tr::updateMatrices(
        cv::VideoCapture& vidCap,
        cv::Mat& frame,
        cv::Mat& shrinkFrame,
        cv::Mat& grey,
        cv::Mat& oldgrey,
        cv::Size newSize)
{
    vidCap.read(frame);
    // If the frame is empty, break immediately
    if (frame.empty()) {
        return 0;
    }
    // Create a temporary matrix to store the flipped matrix.
    cv::Mat shrinkFramePreFlip = cv::Mat(newSize, CV_8UC3);
    cv::resize(frame, shrinkFramePreFlip, newSize);
    // Flip horizontally and vertically.
    // Assign that to the shrinkFrame.
    cv::flip(shrinkFramePreFlip, shrinkFrame, -1);
    // Copy the old greyscale.
    grey.copyTo(oldgrey);
    // Load the new greyscale.
    cv::cvtColor(shrinkFrame, grey,
                 cv::ColorConversionCodes::COLOR_BGR2GRAY, 0);
    return 1;
}

cv::Rect2d tr::getBBox(double centreX, double centreY, double width, double height)
{
    // Create bounding box.
    cv::Rect2d bbox(
            centreX - width*0.5,
            centreY - height*0.5,
            width,
            height
    );
    return bbox;
}


cv::Rect2d tr::clipBBox(cv::Rect2d bbox, double imgW, double imgH)
{
    double tlX = std::max(bbox.x, 0.0);
    double tlY = std::max(bbox.y, 0.0);
    double brX = std::min(bbox.x + bbox.width, imgW);
    double brY = std::min(bbox.y + bbox.height, imgH);
    cv::Rect2d newBbox(tlX, tlY, brX, brY);
    return newBbox;
}


void tr::colourMask(
        cv::Mat& m,
        cv::Mat& output,
        cv::Vec3b minColourHSV,
        cv::Vec3b maxColourHSV)
{
    if (output.channels() > 1) {
        throw std::runtime_error("Colour mask output matrix has too many dimenions.");
    }

    cv::Mat hsv;
    cv::cvtColor(m, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV, 0);

    for (size_t i = 0; i < hsv.rows; ++i) {
        unsigned char* hsvRowStart = hsv.ptr<unsigned char>(i);
        unsigned char* outRowStart = output.ptr<unsigned char>(i);
        for (size_t j = 0; j < hsv.cols*hsv.channels(); j += hsv.channels()) {
            // Split our channels up into 3 parts
            unsigned char* h = hsvRowStart;
            unsigned char* s = hsvRowStart + 1;
            unsigned char* v = hsvRowStart + 2;

            unsigned char* outptr = outRowStart;
            // Check every single point in the hypercube.
            if (*h > minColourHSV[0] &&
                *h < maxColourHSV[0] &&
                *s > minColourHSV[1] &&
                *s < maxColourHSV[1] &&
                *v > minColourHSV[2] &&
                *v < maxColourHSV[2])
            {
                *outptr = 255;
            } else {
                *outptr = 0;
            }

            // Add the number of channels each one stores.
            hsvRowStart += hsv.channels();
            outRowStart += 1;
        }
    }
}
