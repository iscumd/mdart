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
float turnRadius // used for determining wheel angles and velocities

float xFrontLeft
float xFrontRight
float xRearLeft
float xRearRight
float yFrontLeft
float yFrontRight
float yRearLeft
float yRearRight

int main(int argc, char **argv)
{
    // define some variables
    xFrontLeft = -vehicleWidth/2;
    xFrontRight = vehicleWidth/2;
    xRearLeft = -vehicleWidth/2;
    xRearRight = vehicleWidth/2;

    yFrontLeft = vehicleHeight/2;
    yFrontRight = vehicleHeight/2;
    yRearLeft = -vehicleHeight/2;
    yRearRight = -vehicleHeight/2;
    

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

        turnRadius = 10; // need some function to turn angular z and linear x into turn radius
        // turnRadius = twistIn.angular.z;

        if(abs(turnRadius) < vehicleWidth/2){
            wheelOut.angleFrontLeft = 0;
            wheelOut.angleFrontRight = 0;
            wheelOut.angleRearLeft = 0;
            wheelOut.angleRearRight = 0;

            wheelOut.speedFrontLeft =  twistIn.linear.x;
            wheelOut.speedFrontRight = twistIn.linear.x;
            wheelOut.speedRearLeft =   twistIn.linear.x;
            wheelOut.speedRearRight =  twistIn.linear.x;
        }else{
            wheelOut.angleFrontLeft = atan(yFrontLeft / (turnRadius - xFrontLeft));
            wheelOut.angleFrontRight = atan(yFrontRight / (turnRadius - xFrontRight));
            wheelOut.angleRearLeft = atan(yRearLeft / (turnRadius - xRearLeft));
            wheelOut.angleRearRight = atan(yRearRight / (turnRadius - xRearRight));

            wheelOut.speedFrontLeft = 0;
            wheelOut.speedFrontRight = 0;
            wheelOut.speedRearLeft = 0;
            wheelOut.speedRearRight = 0;

        }

        

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
