//
// Created by 谢豪 on 2025/8/7.
//

#include "cvTrans.h"
#include <vector>
cv::Mat cvTrans::simpleSkinSmoothing(const cv::Mat& inputImage) {
    int d = 15; double sigmaColor = 150; double sigmaSpace = 15 ;
    if (inputImage.empty()) {
        std::cerr << "错误: 输入图像为空！" << std::endl;
        return inputImage;
    }

    cv::Mat smoothedImage;
    bilateralFilter(inputImage, smoothedImage, d, sigmaColor, sigmaSpace);

    return smoothedImage;
}

cv::Mat cvTrans::addTextWatermark(const cv::Mat& src, const std::string& text) {
    //初始化
    const cv::Point& pos = cv::Point(50, 50);
    double fontScale = 1.0;
    cv::Scalar color = cv::Scalar(0, 0, 255);  // BGR格式，默认红色
    int thickness = 2;
    int lineType = cv::LINE_AA;



    cv::Mat dst = src.clone();  // 克隆原图，避免修改原图

    // 设置字体（OpenCV支持的字体）
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;  // 常用字体

    // 绘制文字水印
    cv::putText(dst, text, pos, fontFace, fontScale, color, thickness, lineType);

    return dst;
}


cvTrans::cvTrans() {

}

cv::Mat cvTrans::Whitening(const cv::Mat& src) {
    if (src.empty()) return cv::Mat();

    cv::Mat dst=src.clone();
    // 转换为浮点型以避免运算溢出（中间过程使用更高精度）
    src.convertTo(dst, CV_32F);

    // 定义美白参数（与原逻辑保持一致）
    double alpha = 1.3;    // 比例系数
    int beta = 30;         // 偏移量

    // 矩阵运算：dst = src * alpha + beta（替代双重循环）
    dst = dst * alpha + beta;

    // 转换回原类型，并自动截断超出[0,255]的像素值（替代saturate_cast）
    dst.convertTo(dst, src.type(), 1.0, 0.0);

    return dst;
}

cv::Mat cvTrans::Whitening2(const cv::Mat &src) {
    std::vector<int> Color_list = {
    1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 31, 33, 35, 37, 39,
    41, 43, 44, 46, 48, 50, 52, 53, 55, 57, 59, 60, 62, 64, 66, 67, 69, 71, 73, 74,
    76, 78, 79, 81, 83, 84, 86, 87, 89, 91, 92, 94, 95, 97, 99, 100, 102, 103, 105,
    106, 108, 109, 111, 112, 114, 115, 117, 118, 120, 121, 123, 124, 126, 127, 128,
    130, 131, 133, 134, 135, 137, 138, 139, 141, 142, 143, 145, 146, 147, 149, 150,
    151, 153, 154, 155, 156, 158, 159, 160, 161, 162, 164, 165, 166, 167, 168, 170,
    171, 172, 173, 174, 175, 176, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187,
    188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203,
    204, 205, 205, 206, 207, 208, 209, 210, 211, 211, 212, 213, 214, 215, 215, 216,
    217, 218, 219, 219, 220, 221, 222, 222, 223, 224, 224, 225, 226, 226, 227, 228,
    228, 229, 230, 230, 231, 232, 232, 233, 233, 234, 235, 235, 236, 236, 237, 237,
    238, 238, 239, 239, 240, 240, 241, 241, 242, 242, 243, 243, 244, 244, 244, 245,
    245, 246, 246, 246, 247, 247, 248, 248, 248, 249, 249, 249, 250, 250, 250, 250,
    251, 251, 251, 251, 252, 252, 252, 252, 253, 253, 253, 253, 253, 254, 254, 254,
    254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
    255, 255, 255, 256};
    cv::Mat dst=src.clone();
    // 转换为浮点型以避免运算溢出（中间过程使用更高精度）

    if (Color_list.size() <= 255) {
        std::cerr << "错误：Color_list长度不足，无法覆盖0~255索引" << std::endl;
        return cv::Mat();
    }

    // 遍历像素进行颜色映射（使用指针访问提升效率）
    for (int i = 0; i < dst.rows; ++i) {
        // 获取第i行的指针（CV_8UC3对应cv::Vec3b）
        cv::Vec3b* row_ptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < dst.cols; ++j) {
            // 分别对B、G、R通道进行映射（注意OpenCV默认是BGR顺序）
            int b = row_ptr[j][0];  // 原B通道值（0~255）
            int g = row_ptr[j][1];  // 原G通道值
            int r = row_ptr[j][2];  // 原R通道值

            // 映射到Color_list中的值（确保索引在有效范围）
            row_ptr[j][0] = static_cast<uchar>(Color_list[b]);  // 新B通道
            row_ptr[j][1] = static_cast<uchar>(Color_list[g]);  // 新G通道
            row_ptr[j][2] = static_cast<uchar>(Color_list[r]);  // 新R通道
        }
    }

    // 转换回原类型，并自动截断超出[0,255]的像素值（替代saturate_cast）

    return dst;
}


cv::Mat addTextWatermark(const cv::Mat& src, const std::string& text,
                        const cv::Point& pos = cv::Point(50, 50),
                        double fontScale = 1.0,
                        cv::Scalar color = cv::Scalar(0, 0, 255),  // BGR格式，默认红色
                        int thickness = 2,
                        int lineType = cv::LINE_AA) {
    cv::Mat dst = src.clone();  // 克隆原图，避免修改原图

    // 设置字体（OpenCV支持的字体）
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;  // 常用字体

    // 绘制文字水印
    cv::putText(dst, text, pos, fontFace, fontScale, color, thickness, lineType);

    return dst;
}
