#include <stdlib.h>
#include <string>

class InputHandler
{
public:
    InputHandler();
    InputHandler(int argc, char* argv[]);
    void printUsage();
    void readInput(int argc, char* argv[]);
    std::string vidPath();
    int frameStart();
    bool useCamera();
private:
    const int vidIndex_ = 1;
    const int frameStartIndex_ = 2;
    std::string vidPath_;
    bool useCamera_ = false;
    int frameStart_ = 0;
};

