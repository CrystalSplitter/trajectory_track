#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include "inputhandler.hpp"
#include "tracker.hpp"
#include "physics/rigidbody.hpp"
#include "recorder.hpp"

int main(int argc, char* argv[])
{
    // Set up the input handler to handle any important values.

    InputHandler ihandle;
    try {
        ihandle.readInput(argc, argv);
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    std::cout << ihandle.vidPath() << std::endl;
    // capture the video and check validity.
    cv::VideoCapture vidCap;
    if (ihandle.useCamera()) {
        // We're trying to record from the camera.
        std::cout << "Streaming video camera..." << std::endl;
        try {
            vidCap = cv::VideoCapture(0);
        } catch (std::exception e) {
            vidCap = cv::VideoCapture(-1);
        }
        if (!vidCap.isOpened()) {
            std::cout << "Unable to open video. Quiting." << std::endl;
            return -1;
        }
    } else {
        std::cout << "Loading video..." << std::endl;
        try {
            vidCap = cv::VideoCapture(ihandle.vidPath());
        } catch (cv::Exception e) {
            std::cout << "Unable to open video: " << ihandle.vidPath()
                      << ". Quiting." << std::endl;
            return -1;
        }
    }

    //Recorder recorder;
    //recorder.record(vidCap, 60.0, ihandle.outputFile());
    tr::trackerProc(vidCap, ihandle.frameStart(), ihandle.outputFile());
    // Release the video.
    vidCap.release();

    return 0;
}
