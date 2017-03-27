#include "utils.hpp"

cv::Mat ResizeRemainAR(cv::Mat _input_img, cv::Size _resize_size){

    double resize_ratio;
    if(_input_img.cols/_resize_size.width >= _input_img.rows/_resize_size.height)
    {
        resize_ratio = (double)_input_img.cols/(double)_resize_size.width;
    }
    else
    {
        resize_ratio = (double)_input_img.rows/(double)_resize_size.height;
    }

    cv::Mat output_img;
    cv::resize(_input_img,output_img,cv::Size(),(1.0/resize_ratio),(1.0/resize_ratio));

    return output_img;
}
