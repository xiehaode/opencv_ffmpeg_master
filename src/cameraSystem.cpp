//
// Created by 谢豪 on 2025/8/8.
//
#include "cameraSystem.h"
#include <vtkCubeSource.h>

void cameraSystem::start() {
    t1= std::thread(&cameraSystem::dowork,this);
    t1.join();
}

int cameraSystem::dowork() {
    // 打开摄像头
    cv::VideoCapture cap("rtmp://159.75.85.170/live/test");
    if (!cap.isOpened()) {
        std::cerr << "无法打开摄像头!" << std::endl;
        return -1;
    }
    // 获取摄像头的一些参数
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    double fps = 30.0; // 设置帧率
    // 定义 VideoWriter 对象，并指定编解码器、文件名、帧率和画面尺寸
    cv::VideoWriter videoWriter("output.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));



    if (!videoWriter.isOpened()) {
        std::cerr << "无法打开 VideoWriter!" << std::endl;
        return -1;
    }
    cv::Mat frame;
    while (true) {
        cap >> frame; // 从摄像头获取一帧
        if (frame.empty()) {
            break; // 如果捕获失败，则退出循环
        }


        cvTrans cT;

        //frame=cT.simpleSkinSmoothing(frame);
        time_t now;
        time(&now);
        struct tm* local_time = localtime(&now);
        char time_str[100];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
        std::string text=time_str;
        frame=cT.addTextWatermark(frame,text);

        frame=cT.Whitening2(frame);

        videoWriter.write(frame); // 写入当前帧
        cv::imshow("Camera", frame); // 显示当前帧
        char c = (char)cv::waitKey(25);
        if (c == 27) { // 按下 Esc 键退出
            break;
        }
    }
    cap.release();          // 释放摄像头
    videoWriter.release();  // 释放 VideoWriter
    cv::destroyAllWindows(); // 销毁所有窗口
    return 0;
}

cameraSystem::cameraSystem() {
}
