#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <stdexcept>

#include "recorder.hpp"

int Recorder::record(cv::VideoCapture& vidCap, float duration, std::string outputPath)
{
    double fps = 20.0;

    cv::Mat frame;
    cv::Mat flipFrame;
    vidCap.read(frame);

    cv::VideoWriter output;
    output.open(
            outputPath.c_str(),
            cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
            fps,
            frame.size(),
            true
    );

    if (!output.isOpened()) {
        throw std::runtime_error("Output video could not be opened.");
    }

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
    while (true) {
        if (frame.empty()) {
            // Video has ended. Break.
            break;
        }

        std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> timespan = currentTime - startTime;

        if (timespan.count() >= duration*1000) {
            // Duration completed. Quit.
            break;
        }

        vidCap.read(frame);
        output.write(frame);
        std::chrono::system_clock::time_point t2 = std::chrono::system_clock::now();

        std::chrono::duration<double, std::milli> writeTime = t2 - currentTime;
        double waitTime = 1000.0/fps - writeTime.count();

        std::cout << "Wait time: " << waitTime
            << " writeTime " << writeTime.count()
            << " timespan " << timespan.count()
            << std::endl;

        if (waitTime > 0) {
            cv::waitKey(waitTime);
        }
    }
    return 0;
}
