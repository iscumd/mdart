#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "tf/message_filter.h"
#include "tf/transform_listener.h"
   
#include <sstream>

void newLidarDataCallback(const sensor_msgs::LaserScan::ConstPtr& msg_in)
{
    // TODO: use this data, currently writing this node as a stub to test compiling/publishing/subscribing
    // http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
//	float center = msg_in->ranges[539];
 //   ROS_INFO("PathGenerator Received LaserScan: [%s]", center);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Figure_8_Path_Generator_node");
  // Q: Should the 3rd argument always be the file name?

  ros::NodeHandle nodeHandle;

  ros::Publisher path_pub = nodeHandle.advertise<geometry_msgs::Twist>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the oldest message from the queue or the new one attempted to be added to the queue?

    ros::Subscriber subscriber = nodeHandle.subscribe("edges", 1, newLidarDataCallback);

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok())
  {

    ros::spinOnce();
    // calls newLidarDataCallback if there are messages in it's queue to be run



 //     geometry_msgs::Twist msg;

    /*
    float64 speed
    float64 turnRadius
    float64 distance
    */

   //   msg.speed = 1;
   //   msg.turnRadius = 0;
   //   msg.distance = 1;

  //    path_pub.publish(msg);



      loop_rate.sleep();
      // sleep such as to run at 50hz
      // Q: if this function takes n time to run, will it compensate be removing the n time from the sleep amount in order to maintain 50hz?
  }

  return 0;
}

