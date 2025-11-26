
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

void generate_pixels(std::string image_name,cv::Scalar color,cv::Size  img_size){
    cv::Mat myImage(img_size,CV_8UC3,color);
    cv::namedWindow(image_name,cv::WINDOW_AUTOSIZE);
    cv::imshow(image_name,myImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
     
};