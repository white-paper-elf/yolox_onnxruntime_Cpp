//
// Created by DefTruth on 2022/5/2.
//

#ifndef LITE_AI_TOOLKIT_ORT_CV_YOLOV5_BLAZEFACE_H
#define LITE_AI_TOOLKIT_ORT_CV_YOLOV5_BLAZEFACE_H

#include "lite/ort/core/ort_core.h"

namespace ortcv
{
  class LITE_EXPORTS YOLOv5BlazeFace : public BasicOrtHandler
  {
  public:
    explicit YOLOv5BlazeFace(const std::string &_onnx_path, unsigned int _num_threads = 1);

    ~YOLOv5BlazeFace() override = default;

  private:
    // nested classes
    typedef struct
    {
      float ratio;
      int dw;
      int dh;
      bool flag;
    } YOLOv5BlazeFaceScaleParams;

  private:
    static constexpr const float mean_val = 0.f; // RGB
    static constexpr const float scale_val = 1.0 / 255.f;
    static constexpr const unsigned int max_nms = 30000;

  private:
    Ort::Value transform(const cv::Mat &mat_rs) override; // without resize

    void resize_unscale(const cv::Mat &mat,
                        cv::Mat &mat_rs,
                        int target_height,
                        int target_width,
                        YOLOv5BlazeFaceScaleParams &scale_params);

    void generate_bboxes_kps(const YOLOv5BlazeFaceScaleParams &scale_params,
                             std::vector<types::BoxfWithLandmarks> &bbox_kps_collection,
                             std::vector<Ort::Value> &output_tensors,
                             float score_threshold, float img_height,
                             float img_width); // rescale & exclude

    void nms_bboxes_kps(std::vector<types::BoxfWithLandmarks> &input,
                        std::vector<types::BoxfWithLandmarks> &output,
                        float iou_threshold, unsigned int topk);

  public:
    void detect(const cv::Mat &mat, std::vector<types::BoxfWithLandmarks> &detected_boxes_kps,
                float score_threshold = 0.3f, float iou_threshold = 0.45f,
                unsigned int topk = 400);

  };
}


#endif //LITE_AI_TOOLKIT_ORT_CV_YOLOV5_BLAZEFACE_H
