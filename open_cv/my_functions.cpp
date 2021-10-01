#include <opencv2/opencv.hpp>
#include <chrono>

#ifdef __ANDROID__

#include <android/log.h>

#endif

using namespace cv;
using namespace std;

extern "C" {

void platform_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
#ifdef __ANDROID__
    __android_log_vprint(ANDROID_LOG_VERBOSE, "FFI Logger: ", fmt, args);
#else
    vprintf(fmt, args);
#endif
    va_end(args);
}

__attribute__((visibility("default"))) __attribute__((used))
const char *getOpenCVVersion() {
    return CV_VERSION;
}

__attribute__((visibility("default"))) __attribute__((used))
void convertImageToGrayImage(char *inputImagePath, char *outputPath) {
    platform_log("PATH %s: ", inputImagePath);
    cv::Mat img = cv::imread(inputImagePath);
    platform_log("Length: %d", img.rows);
    cv::Mat graymat;
    cvtColor(img, graymat, cv::COLOR_BGR2GRAY);
    platform_log("Output Path: %s", outputPath);
    cv::imwrite(outputPath, graymat);
    platform_log("Gray Image Length: %d", graymat.rows);
    platform_log("Image writed again ");
}
}
