#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "inputhandler.hpp"

InputHandler::InputHandler()
{
    // Do nothing.
}

InputHandler::InputHandler(int argc, char* argv[])
{
    this->readInput(argc, argv);
}

void InputHandler::printUsage()
{
    std::cout << std::endl << "Usage: tracker VIDEO_FILE STARTING_FRAME" << std::endl;
}

void InputHandler::readInput(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "[ERR] Insufficient Arguments." << std::endl;
        this->printUsage();
        throw std::runtime_error("Could not read input.");
    }
    char* resolvedPath = (char*) std::calloc(sizeof(char),  1024);
    realpath(argv[vidIndex_], resolvedPath);
    vidPath_ = std::string(resolvedPath);
    if (argc > 2) {
        frameStart_ = std::stoi(argv[frameStartIndex_]);
    }
}

std::string InputHandler::vidPath()
{
    return vidPath_;
}

int InputHandler::frameStart()
{
    return frameStart_;
}
