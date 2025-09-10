//
// Created by 谢豪 on 2025/8/7.
//

#ifndef CVTRANS_H
#define CVTRANS_H
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp> // cv::imread
#include <opencv2/objdetect.hpp>

class cvTrans {
private:

public:
    explicit cvTrans();
    cv::Mat Whitening(const cv::Mat& src);
    cv::Mat Whitening2(const cv::Mat& src);
    cv::Mat simpleSkinSmoothing(const cv::Mat& inputImage);
    cv::Mat addTextWatermark(const cv::Mat& src, const std::string& text);
};

#endif //CVTRANS_H
