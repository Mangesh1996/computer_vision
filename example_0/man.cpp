#include <iostream>
#include "img_generate.h"

int main(){
    std::string window_name="first_windows";
    cv::Scalar color(255, 0, 0); 

    // 1280 width, 720 height
    cv::Size img_size(1280, 720);
    generate_pixels(window_name,color,img_size);
    return 0;
}