#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include <vector>
namespace fs=std::filesystem;


struct ProcessingPipeline{
    std::string input_dir;
    std::string output_dir;

    ProcessingPipeline(const std::string& in,const std::string& out):input_dir(in),output_dir(out){
        setupDirectories();
    }
    void setupDirectories(){
        std::vector<std::string> dirs ={
            output_dir+"/original/",
            output_dir+"/edges/",
            output_dir+"/resized/",
            output_dir+"/logs/",
            output_dir+"/gray_scale/"
        };
        for(const auto& dir:dirs){
            if(fs::create_directories(dir)){
                std::cout << "Created : "<< dir << std::endl;
            }
        }
    }
    void process(){
        
        for(const auto& entry:fs::directory_iterator(input_dir)){
            
            if(entry.path().extension()==".jpg" | entry.path().extension()==".png" ){
                processImage(entry.path());
            }
    }
    }
    void processImage(const fs::path& img_path){
        std::string filename=img_path.stem().string();
        cv::Mat img=cv::imread(img_path.string());
        
        if(img.empty()){
            std::cout << "faile to read image\n";
            return ;
        }
        
        //save original copy
        cv::imwrite(output_dir+"/original/"+filename+".jpg",img);
        //Grayscale
        cv::Mat gray;
        cv::cvtColor(img,gray,cv::COLOR_BGR2GRAY);
        cv::imwrite(output_dir+"/gray_scale/"+filename+"_gray.jpg",gray);
        //edge detection
        cv::Mat edge;
        cv::Canny(gray,edge,50,150);
        cv::imwrite(output_dir+"/edges/"+filename+"_edges.jpg",edge);
        //resized
        cv::Mat resized;
        cv::resize(img,resized,cv::Size(640,480));
        cv::imwrite(output_dir+"/resized/"+filename+"_resized.jpg",resized);
        std::cout << "Processd : "<< filename <<std::endl;


    }
};

int main(){
    ProcessingPipeline pipeline("input_dir","output_dir");
    
    pipeline.process();
    std::cout<< "check out all outputp\n";
    return 0;
}