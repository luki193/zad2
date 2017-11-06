#include "ros/ros.h"
#include <iostream>
#include <sstream>
#include "projekt1/komunikat.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
  //inicjalizacja węzła + jego nazwa
  ros::init(argc, argv, "talker");

  //uchwyt do węzła
  ros::NodeHandle n;
  ros::NodeHandle n2;

  /*inicjalizacja publishera, typ publikowanych danych oraz nazwa topiku z
    wielkością buffora danych (ile wiadomosci moze czekac w kolejce do
    przeslania)*/
  ros::Publisher chatter_pub = n.advertise<projekt1::komunikat>("chatter", 1000);
  ros::Publisher chatter_pub2 = n2.advertise<sensor_msgs::Image>("sendImage", 1000);

  //czestotliwość w Hz uruchamiania
  ros::Rate loop_rate(10);

  int licznik = 0;
  Mat obrazCV = imread("/home/lukasz/ros_foto/obraz.jpg",1);
  sensor_msgs::ImagePtr obrazROS = cv_bridge::CvImage(std_msgs::Header(), "bgr8", obrazCV).toImageMsg();
  
  //pętla powtarzająca się z częstotliwością loop_rate
   while(ros::ok())
    {
    projekt1::komunikat msg;
    
    //zapisanie zmiennych do naszej wiadomosci
    std::stringstream ss;
    ss << "witaj smutny swiecie";
    msg.tresc = ss.str();
    msg.numer=licznik;

    ROS_INFO("%s po raz %d", msg.tresc.c_str(), msg.numer);
    
    //wyslanie wiadomosci
    chatter_pub.publish(msg);
    chatter_pub2.publish(obrazROS);

    //wejście do petli ros
    ros::spinOnce();

    //zatrzymanie pętli na czas określony wcześniej
    loop_rate.sleep();
    ++licznik;
  }


  return 0;
}