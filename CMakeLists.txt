cmake_minimum_required(VERSION 3.10)
project(yolox_onnxruntime_Cpp)

set(CMAKE_CXX_STANDARD 11)

set(LITE_AI_DIR ${CMAKE_SOURCE_DIR}/lite.ai.toolkit)
include_directories(${LITE_AI_DIR}/include)
link_directories(${LITE_AI_DIR}/lib})

set(TOOLKIT_LIBS lite.ai.toolkit onnxruntime)
set(OpenCV_LIBS opencv_core opencv_imgcodecs opencv_imgproc opencv_highgui)

add_executable(test_infer obj_infer.cpp)
target_link_libraries(test_infer ${TOOLKIT_LIBS} ${OpenCV_LIBS})