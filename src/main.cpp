#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include "inputhandler.hpp"
#include "tracker.hpp"
#include "physics/rigidbody.hpp"

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
    cv::VideoCapture vidCap(ihandle.vidPath());
    if (!vidCap.isOpened()) {
        std::cout << "Unable to open video. Quiting." << std::endl;
        return -1;
    }

    tr::trackerProc(vidCap, ihandle.frameStart());
    // Release the video.
    vidCap.release();
    return 0;
}
