#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include "projekt1/komunikat.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//funkcja uruchamiana gdy nadejdzie komunikat
void chatterCallback(const projekt1::komunikat::ConstPtr& msg)
{
  ROS_INFO("Ulyszalem: [%s], [%d]", msg->tresc.c_str(), msg->numer);
}

void chatterCallback2(const sensor_msgs::ImageConstPtr& msg)
{
  imshow("obraz", cv_bridge::toCvShare(msg, "bgr8")->image);
  waitKey(30);
}

int main(int argc, char **argv)
{
  //inicjalizacja węzła i jego nazwa
  ros::init(argc, argv, "listener");

  //uchwyt do węzła
  ros::NodeHandle n;
  ros::NodeHandle n2;
  
  /*określenie typu (odbieranie subscribe czy wysyłanie publish), 
  nazwy topicu, rozmiaru kolejki i uruchamianej funkcji callback*/
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  ros::Subscriber sub2 = n2.subscribe("sendImage", 1000, chatterCallback2);

  //pętla ros
  ros::spin();

  return 0;
}