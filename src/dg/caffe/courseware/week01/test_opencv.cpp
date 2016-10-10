#include <iostream>
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char* argv[]){
  const std::string window_name = "lena";
  const std::string input_pic   = "lena.jpg";
  cv::Mat test_pic = cv::imread(input_pic);
  if(test_pic.empty()){
	  std::cout<<"no input image"<<std::endl;
	  return 1;
  }
  cv::namedWindow(window_name);
  cv::imshow(window_name,test_pic);
  cv::waitKey(0);
  return 0;
}
