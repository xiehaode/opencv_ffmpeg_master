cmake_minimum_required(VERSION 3.28)
project(ffmpeg_master)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)
#VTK
find_package(VTK REQUIRED COMPONENTS
        CommonCore
        RenderingOpenGL2  # 根据你的实际需求添加需要的组件
        # 其他需要的组件...
)
if (VTK_FOUND)
    include(${VTK_USE_FILE})
else()
    message(FATAL_ERROR "VTK not found. Please set VTK_DIR.")
endif()

find_package(OpenCV REQUIRED) #找 OpenCV 4.0 安装路径
include_directories(${OpenCV_INCLUDE_DIRS}) #加载 OpenCV 4.0 的头文件

# 查找GLFW3（修改后）
find_package(glfw3 REQUIRED)  # 注意：在Ubuntu中通常是小写"glfw3"

# 查找FFmpeg库
find_package(PkgConfig REQUIRED)
find_package(dlib REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)

# 包含FFmpeg头文件路径
include_directories(${AVFORMAT_INCLUDE_DIRS})
include_directories(${AVCODEC_INCLUDE_DIRS})
include_directories(${AVUTIL_INCLUDE_DIRS})
  # 添加GLFW3头文件路径
include_directories(${GLFW3_INCLUDE_DIRS})

include_directories(include)


#include_directories(${dlib_INCLUDE_DIRS})

set(LIBS
        ${AVFORMAT_LIBRARIES} ${AVCODEC_LIBRARIES} ${AVUTIL_LIBRARIES}
        ${OpenCV_LIBS}
        ${GLFW3_INCLUDE_DIRS}  # 添加GLFW3头文件路径
        glfw  # Ubuntu中直接链接"glfw"
        dlib::dlib  # 这是推荐的dlib链接方式，替代了旧的变量
        Qt6::Core Qt6::Gui Qt6::Gui Qt6::Widgets
        #${dlib_LIBRARIES}
        ${VTK_LIBRARIES}  # 正确的变量名是VTK_LIBRARIES
)

set(SOURCE_FILES
        src/main.cpp
        src/glad.c
        src/cvTrans.cpp
        src/rtmpPush.cpp
        src/cameraSystem.cpp
)

add_executable(ffmpeg_master ${SOURCE_FILES})

# 链接FFmpeg库
target_link_libraries(ffmpeg_master ${LIBS})


