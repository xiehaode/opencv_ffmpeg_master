//
// Created by 谢豪 on 2025/8/8.
//

#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H
#include "cvTrans.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}
#include <thread>
class cameraSystem {
public:
    void start();
    int dowork();
    explicit cameraSystem();
private:
    std::thread t1;  // 线程对象作为成员，避免局部变量销毁问题


};
#endif //CAMERASYSTEM_H
