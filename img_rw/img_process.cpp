#include <iostream>
#include <opencv2/opencv.hpp>
 
#include <filesystem>
namespace fs =std::filesystem;
bool save_img(const std::string& save_path,const std::string& filename,  const cv::Mat& image){

    if(!fs::exists(save_path)){
        fs::create_directories(save_path);
    } 
    cv::imwrite(save_path+"/"+filename+".jpg" ,image);
    return true;
}

cv::Mat draw_rectangle(const cv::Mat& image){
    cv::Point pt1(50, 50);  // Top-left corner (x, y)
    cv::Point pt2(200, 150); // Bottom-right corner (x, y)
    cv::rectangle(image,pt1,pt2,cv::Scalar(0,0,255),2);
    return image;
}

bool  display_img( const std::string& img_path){
    std::string filename=fs::path(img_path).stem().string();
    cv::Mat image=cv::imread(img_path);
    if(image.empty()){
        std::cerr <<"Failed to read image\n";
    }
    cv::Mat resized;
    cv::resize(image,resized,cv::Size(image.cols/2,image.rows/2));
    cv::namedWindow("Display Image",cv::WINDOW_AUTOSIZE);
    draw_rectangle(resized);
    if(!save_img("save",filename ,resized)){
        std::cerr << "waring failed to save resize image\n";
    }
    
    cv::imshow("Display Image",resized);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return true;

}
