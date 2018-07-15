#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <string>

geometry_msgs::Twist twistIn;
geometry_msgs::Twist joyTwist;
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

    if(joyIn.buttons[0] == 1){ // come up with way to input super secret code to toggle on boostmode
        boostState = true;
    }

    if(joyIn.buttons[0] == 1){ // button to toggle manual/autonomous mode
        autoState = !autoState;
    }

    if(joyIn.buttons[0] == 1){ // deadman switch, needs to be mapped properly
        
        /* placeholder for whenever joy stuff is actually figured out
        joyTwist.linear.x = 1;
        joyTwist.angular.z = .25;
        */

    }else{ //if deadman is not held, be immobile
        joyTwist.linear.x = 0;
        joyTwist.angular.z = 0;
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
    autoState = true;
    
    
    while(ros::ok())
    {
        //checks for subscription callbacks to update
        ros::spinOnce();

        if(autoState){ // autonomous state just passes along the twist

            twistOut = twistIn;
            boostState = false; // definitely don't want any speed boosts included in this

        }else{ // joystick control needs to convert the joy message into a twist
            
            
            twistOut = joyTwist;

            if(boostState){
                twistOut.linear.x *= 2;
                twistOut.angular.z *= 2;// switch to 1 + trigger maybe for controllable boost
            }
        }

        arbitrator_pub.publish(twistOut);

        loop_rate.sleep();
    }

return 0;
}

