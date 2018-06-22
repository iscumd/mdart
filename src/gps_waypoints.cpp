#include "msg/Path.msg"
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "GPS_Data_Node");

  ros::NodeHandle nodeHandle;

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok()) {

    ros::spinOnce()

            M -
        DART::Path msg;

    /*
    float64 latitude
    float64 longitude
    float64 altitude
    */

    msg.latitude = 1;
    msg.longitude = 0;
    msg.altitude = 1;

    path_pub.publish(msg);

    loop_rate.sleep();
  }

  return 0;
}
