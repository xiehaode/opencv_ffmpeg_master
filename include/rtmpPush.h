//
// Created by 谢豪 on 2025/8/8.
//

#ifndef RTMPPUSH_H
#define RTMPPUSH_H

#include <iostream>

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
#include "libavutil/time.h"
};


class rtmpPush {
public:
    explicit rtmpPush(std::string url);
    int push(std::string url);
    int avError(int errNum);
private:
    std::string url=nullptr;
};

#endif //RTMPPUSH_H
