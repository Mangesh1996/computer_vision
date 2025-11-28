#include <iostream>
#include <vector>
#include <getopt.h>
#include <opencv2/opencv.hpp>
#include "inference.h"

using namespace std;
using namespace cv;

int main(int argc,char **argv){
    std::string Model_path="/home/easemyai/Documents/Workspace/work/opencv_practices/yolo_inference/model/yolov8s.onnx";
    bool runonGPU=false;

    Inference inf(Model_path,cv::Size(640,640),"classes.txt",runonGPU);
    std::vector<std::string> imageNames;
    imageNames.push_back("image/sample.jpg");
    for(int i=0;i<imageNames.size();++i){
        cv::Mat frame= cv::imread(imageNames[i]);

        //inference start here....
        std::vector<Detection> output= inf.runInference(frame);
        int detections=output.size();
        std::cout << "Number of detections: " << detections << std::endl;
        for(int i=0;i<detections;++i){
            Detection detections=output[i];
            cv::Rect box= detections.box;
            cv::Scalar color= detections.color;
            //Detection box
            cv::rectangle(frame,box,color,2);
            //Detection box test
            std::string classString = detections.className+' '+std::to_string(detections.confidence);
            cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);

            cv::Rect textBox(box.x,box.y-40,textSize.width+10,textSize.height+20);
            cv::rectangle(frame,textBox,color,cv::FILLED);
            cv::putText(frame,classString,cv::Point(box.x+5,box.y-10),cv::FONT_HERSHEY_DUPLEX,1,cv::Scalar(0,0,0),2,0);

        }
        //inference end here...
        float scale=0.8;
        cv::resize(frame,frame,cv::Size(frame.cols*scale,frame.rows*scale));
        cv::imshow("inference",frame);
        cv::waitKey(-1);
    }
}