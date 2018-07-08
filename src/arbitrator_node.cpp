#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <string>

geometry_msgs::Twist twistIn;
geometry_msgs::Twist JoyTwist;
geometry_msgs::Twist twistOut;
sensor_msgs::Joy joyIn;
/* contents of Joy message
# Reports the state of a joysticks axes and buttons.
Header header           # timestamp in the header is the time the data is received from the joystick
float32[] axes          # the axes measurements from a joystick
int32[] buttons         # the buttons measurements from a joystick 
*/

bool boostState;
bool controlState;


void twistCallback(const geometry_msgs::Twist::ConstPtr& twistCb)
{
    //
    twistIn = *twistCb;
    //
    ROS_INFO("arbitrator received the twist: linear.x = [%f] \tangular.z = [%f]", twistIn.linear.x, twistIn.angular.z);
}

void joyCallback(const sensor_msgs::Joy::ConstPtr& joyCb)
{
    //
    joyIn = *joyCb;
    if(joyIn.button.x = 0){
        boostState = !boostState;
    }
    // do some conversions here I guess
    // joyTwist = stuff;
}

int main(int argc, char **argv)
{

    // define name of node and start
    ros::init(argc, argv, "arbitrator_node");
    // The first NodeHandle constructed will fully initialize this node
    ros::NodeHandle nodeHandle;
    // define topic name to publish to and queue size
    ros::Publisher arbitrator_pub = nodeHandle.advertise<geometry_msgs::Twist>("arbitrator_output", 10);
    // define topic names to subscribe to and queue size
    ros::Subscriber twistSub = nodeHandle.subscribe("da_wae", 10, twistCallback);
    ros::Subscriber joySub = nodeHandle.subscribe("joy", 10, joyCallback);
    // specify loop frequency, works with Rate::sleep to sleep for the correct time
    ros::Rate loop_rate(50);

    boostState = false;
    controlState = false;
    

    
    while(ros::ok())
    {
        //checks for subscription callbacks to update
        ros::spinOnce();

        if(controlState = 1){
            twistOut = twistIn;
            boostState = false;
        }else{
            twistOut = joyTwist;
            if(boostState){
                twistOut.linear.x *= 2;
                twistOut.angular.z *= 2;
            }
        }


        arbitrator_pub.publish(twistOut);

        loop_rate.sleep();
    }
return 0;
}

