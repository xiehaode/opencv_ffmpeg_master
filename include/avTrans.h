//
// Created by 谢豪 on 2025/8/7.
//

#ifndef AVCAMERA_H
#define AVCAMERA_H

#include <string>
#include <memory>
#include <thread>
#include <iostream>
extern "C"{
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}
#include "avTrans.h"

class avTrans
{
private:

	explicit  avTrans();
public:
	AVFrame sysTrans();

};





#endif //AVTRANS_H
