#include "msg/Path.msg"
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char **argv) {
  ros::init(argc, argv, "IGVC_path_planning_node");
  // Q: Should the 3rd argument always be the file name?

  ros::NodeHandle nodeHandle;

  ros::Publisher path_pub = nodeHandle.advertise<M - DART::Path>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably
  // become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the
  // oldest message from the queue or the new one attempted to be added to the
  // queue?

  ros::Subscriber subscriber =
      nodeHandle.subscribe("edges", 1, newLidarDataCallback);
  ros::Subscriber subscriber = nodeHandle.subscribe(
      "waypoints @Ethan needs new name", 1, newGPSDataCallback);

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok()) {

    ros::spinOnce();
    // calls newLidarDataCallback if there are messages in it's queue to be run

    M - DART::Path msg;

    /*
    float64 speed
    float64 turnRadius
    float64 distance
    */

    msg.speed = 1;
    msg.turnRadius = 0;
    msg.distance = 1;

    path_pub.publish(msg);

    loop_rate.sleep();
    // sleep such as to run at 50hz
    // Q: if this function takes n time to run, will it compensate be removing
    // the n time from the sleep amount in order to maintain 50hz?
  }

  return 0;
}

void newLidarDataCallback(const sensor_msg::LaserScan::ConstPtr &scan) {
  // TODO: use this data, currently writing this node as a stub to test
  // compiling/publishing/subscribing
  // http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
  ROS_INFO("PathGenerator Recieved LaserScan: [%s]", scan->ranges[539].c_str());
}

void newGPSDataCallback(const sensor_msg::LaserScan::ConstPtr &scan) {
  // TODO: use this data, currently writing this node as a stub to test
  // compiling/publishing/subscribing
  // http://docs.ros.org/api/sensor_msgs/html/msg/LaserScan.html
  ROS_INFO("PathGenerator Recieved LaserScan: [%s]", scan->ranges[539].c_str());
}