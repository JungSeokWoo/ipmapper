#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>


cv::Mat ResizeRemainAR(cv::Mat _input_img, cv::Size _resize_size);

#endif // UTILS_H
