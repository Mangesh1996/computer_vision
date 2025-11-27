#ifndef IMG_PROCESS_H
#define IMG_PROCESS_H
#include <iostream>
#include <opencv2/opencv.hpp>

bool save_img(const std::string& save_path,const std::string& filename,const cv::Mat&  image);
bool  display_img(const std::string&  img_path);
cv::Mat draw_rectangle(const cv::Mat& image);

#endif
 
