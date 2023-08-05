#include "lite/lite.h"

static void test_lite()
{

    std::string onnx_path = "../model/yolox_l.onnx";
    std::string test_img_path = "../img/horse.jpg";
    std::string save_img_path = "../img_out/horse.jpg";

    // 2. Test Specific Engine ONNXRuntime
    lite::onnxruntime::cv::detection::YoloX_V_0_1_1* yolox =
        new lite::onnxruntime::cv::detection::YoloX_V_0_1_1(onnx_path);

    std::vector<lite::types::Boxf> detected_boxes;
    cv::Mat img_bgr = cv::imread(test_img_path);
    yolox->detect(img_bgr, detected_boxes);

    lite::utils::draw_boxes_inplace(img_bgr, detected_boxes);

    cv::imwrite(save_img_path, img_bgr);

    std::cout << "ONNXRuntime Version Detected Boxes Num: " << detected_boxes.size() << std::endl;

    delete yolox;

}

int main(__unused int argc, __unused char* argv[])
{
    test_lite();
    return 0;
}
