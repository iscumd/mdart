#include "ros/ros.h"
#include "mdart/WheelVals.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <string>

geometry_msgs::Twist twistIn;
sensor_msgs::Imu imuIn;
mdart::WheelVals odomIn;
mdart::WheelVals wheelOut;

float turnLimit // max G force applied to driver in y-direction
float vehicleSpeed // placeholder for modified speed
float vehicleWidth // dimensions to determine vehicle angles and speed
float vehicleLength // dimensions to determine vehicle angles and speed
float turnRadius

int main(int argc, char **argv)
{
    // define name of node and start
    ros::init(argc, argv, "vehicle_dynamics");
    // The first NodeHandle constructed will fully initialize this node
    ros::NodeHandle nodeHandle;
    // define topic name to publish to and queue size
    ros::Publisher dynamicsPub = nodeHandle.advertise<mdart::WheelVals>("wheels", 10) 
    // define topic names to subscribe to and queue size
    ros::Subscriber twistSub = nodeHandle.subscribe("arbitrator_output", 10, twistCallback);
    ros::Subscriber imuSub = nodeHandle.subscribe("imu_in", 10, imuCallback);
    // specify loop frequency, works with Rate::sleep to sleep for the correct time
    ros::Rate loop_rate(50)
    while(ros::ok())
    {
        // do some stuff to put data in the message
        /*
        WheelVals - output - wheels
        Wheel Odometry - input - something?
        imu - input - imu
        arbitrator - input - Twist
        */
        ros::spinOnce(); //checks for subscription callbacks to update

        wheelOut.angleFrontLeft = 0;
        wheelOut.angleFrontRight = 0;
        wheelOut.angleRearLeft = 0;
        wheelOut.angleRearRight = 0;

        wheelOut.speedFrontLeft = 0;
        wheelOut.speedFrontRight = 0;
        wheelOut.speedRearLeft = 0;
        wheelOut.speedRearRight = 0;

        dynamics_pub.publish(wheelOut);
        loop_rate.sleep()
    }
return 0;
}

void twistCallback(const geometry_msgs::Twist::ConstPtr& twistCb)
{
    //
    twistIn = *twistCb;
    //
    //ROS_INFO("vehicle_dynamics received the speed: [%s]", scan->ranges[539].c_str());
}

void odomCallback(const mdart::WheelVals::ConstPtr& odomCb)
{
    //
    odomIn = *odomCb;
    //
    //ROS_INFO("vehicle_dynamics received the wheel odometry: [%s]", scan->ranges[539].c_str());
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& imuCb)
{
    //
    imuIn = *imuCb;
    //
    ROS_INFO("vehicle_dynamics received the imu data: [%f]", imuIn.orientation.x;
}
