#include <opencv2/opencv.hpp>

using namespace std;

static void help(char* progName)
{
    cout << endl << "Sharpens an image based using a kernel" << endl;
}

int sharpenProc(int argc, char* argv[])
{
    const char* filename = (argc >= 2) ? argv[1] : nullptr;
    if (!filename) {
        help(argv[0]);
        return -1;
    }

    cv::Mat src;
    cv::Mat sharpened;

    src = cv::imread(filename, cv::IMREAD_COLOR);
    return 0;
}
