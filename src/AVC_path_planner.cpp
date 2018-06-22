#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/String.h"

#include "mdart/Path.h"

#include <sstream>

void newLidarDataCallback(const sensor_msgs::LaserScan::ConstPtr &scan) {
  // TODO: use this data, currently writing this node as a stub to test
  // compiling/publishing/subscribing
  // http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
  
  float32 start = scan->angle_min; //radians
  float32 end = scan->angle_max; //radians
  float32 resolution = scan->angle_increment;  //radians
  int numPoints = ( angle_max - angle_min ) / angle_increment;
  
  ROS_INFO("PathGenerator Received LaserScan: [%f]", scan->ranges[(numPoints/2)]);
}

int main(int argc, char **argv) {
<<<<<<< HEAD
=======
#include "ros/ros.h"
#include "std_msgs/String.h"
//#include "geometry_msgs/Twist.msg"

#include <sstream>

int main(int argc, char **argv)
{
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
  ros::init(argc, argv, "AVC_path_planner");
  // Q: Should the 3rd argument always be the file name?

  ros::NodeHandle nodeHandle;

<<<<<<< HEAD
  ros::Publisher path_pub = nodeHandle.advertise<mdart::Path>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably
  // become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the
  // oldest message from the queue or the new one attempted to be added to the
  // queue?
<<<<<<< HEAD

  ros::Subscriber subscriber =
      nodeHandle.subscribe("scan", 1, newLidarDataCallback);
=======
//  ros::Publisher path_pub = nodeHandle.advertise<mdart::Path>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the oldest message from the queue or the new one attempted to be added to the queue?

//    ros::Subscriber subscriber = nodeHandle.subscribe("lidar_in", 1, newLidarDataCallback);
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
=======

  ros::Subscriber subscriber =
      nodeHandle.subscribe("scan", 1, newLidarDataCallback);
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok()) {

    ros::spinOnce();
    // calls newLidarDataCallback if there are messages in it's queue to be run

//    geometry_msgs::Twist path;

    /*
    float64 speed
    float64 turnRadius
    float64 distance
    */

    //     msg.speed = 1;
    //     msg.turnRadius = 0;
    //     msg.distance = 1;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
    // msg.linear.x = double(rand())/double(RAND_MAX); // vehicle speed in
    // meters per second
    // msg.angular.z = 2*double(rand())/double(RAND_MAX) - 1; // vehicle
    // rotation in radians per second
<<<<<<< HEAD
=======
//	path_pub.publish(path);
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19

    path_pub.publish(path);

    loop_rate.sleep();
    // sleep such as to run at 50hz
    // Q: if this function takes n time to run, will it compensate be removing
    // the n time from the sleep amount in order to maintain 50hz?
  }

  return 0;
}
<<<<<<< HEAD
<<<<<<< HEAD
=======

/*
void newLidarDataCallback(const sensor_msg::LaserScan::ConstPtr& scan)
{
    // TODO: use this data, currently writing this node as a stub to test compiling/publishing/subscribing
    // http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
    ROS_INFO("PathGenerator Received LaserScan: [%s]", scan->ranges[539].c_str());
}
*/
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
