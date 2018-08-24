#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/Bool.h"
#include <cmath>
#include <string>

geometry_msgs::Twist twistIn;
geometry_msgs::Twist joyTwist;
geometry_msgs::Twist twistOut;
std_msgs::Bool autoState;
sensor_msgs::Joy joyIn;

/* contents of Joy message
# Reports the state of a joysticks axes and buttons.
Header header           # timestamp in the header is the time the data is received from the joystick
float32[] axes          # the axes measurements from a joystick
int32[] buttons         # the buttons measurements from a joystick 
*/

//bool boostState;
bool lastState;

double doubleHolder;
float speedLimit;


//wireless 360 controller mapping
int buttonA;
int buttonB;
int buttonX;
int buttonY;
int buttonLB;
int buttonRB;
int buttonBack;
int buttonStart;
int buttonPower;
int buttonLS;
int buttonRS;

int axisLeftHorizontal;
int axisLeftVertical;
int axisRightHorizontal;
int axisRightVertical;
int axisRT;
int axisLT;
int dPadHorizontal;
int dPadVertical;



void twistCallback(const geometry_msgs::Twist::ConstPtr& twistCb)
{
    //
    twistIn = *twistCb;
    //
    ROS_INFO("arbitrator received the twist: linear.x = [%f] \tangular.z = [%f]", twistIn.linear.x, twistIn.angular.z);
    if (twistIn.linear.x > speedLimit){
        twistIn.angular.z *= speedLimit / twistIn.linear.x;
        twistIn.linear.x = speedLimit;
        ROS_INFO("arbitrator modified the twist: linear.x = [%f] \tangular.z = [%f]", twistIn.linear.x, twistIn.angular.z);
    }

}

void joyCallback(const sensor_msgs::Joy::ConstPtr& joyCb)
{
    //
    joyIn = *joyCb;

    /*
    if(joyIn.buttons[0] == 1){ // come up with way to input super secret code to toggle on boostmode
        boostState = true;
    }
    */

    if(joyIn.buttons[7] == 1 && lastState == 0){ // button to toggle manual/autonomous mode
        autoState.data = !autoState.data;
    }

    lastState = joyIn.buttons[7];

    if(joyIn.axes[2] < 0){ // deadman switch, switch to greater than something?
        
        if(abs(joyIn.axes[1]) < .15){
            joyTwist.linear.x = 0;
        }else{
            joyTwist.linear.x = joyIn.axes[1];
        }

        if(abs(joyIn.axes[3]) < .15){
            joyTwist.angular.z = 0;
        }else{
            joyTwist.angular.z = joyIn.axes[3];
        }

    }else{ //if deadman is not held, be immobile
        joyTwist.linear.x = .1;
        joyTwist.angular.z = .1;
    }

}

int main(int argc, char **argv)
{

    // define name of node and start
    ros::init(argc, argv, "arbitrator_node");
    // The first node handle constructed will fully initialize this node
    ros::NodeHandle n;
    // define topic name to publish to and queue size
    ros::Publisher arbitrator_pub = n.advertise<geometry_msgs::Twist>("arbitrator_output", 10);
    ros::Publisher autostate_pub = n.advertise<std_msgs::Bool>("autostate", 10);
    // define topic names to subscribe to and queue size
    ros::Subscriber twistSub = n.subscribe("da_wae", 10, twistCallback);
    ros::Subscriber joySub = n.subscribe("joy", 10, joyCallback);
    // specify loop frequency, works with Rate::sleep to sleep for the correct time
    ros::Rate loop_rate(50);

    //boostState = false;
    autoState.data = false;
    lastState = false;
    
    int buttonA = 0;
    int buttonB = 1;
    int buttonX = 2;
    int buttonY = 3;
    int buttonLB = 4;
    int buttonRB = 5;
    int buttonBack = 6;
    int buttonStart = 7;
    int buttonPower = 8;
    int buttonLS = 9;
    int buttonRS = 10;

    int axisLeftHorizontal = 0;
    int axisLeftVertical = 1;
    int axisRightHorizontal = 3;
    int axisRightVertical = 4;
    int axisRT = 5;
    int axisLT = 2;
    int dPadHorizontal = 6;
    int dPadVertical = 7;


    if(n.param("speedLimit", doubleHolder, 4.5)){
        speedLimit = (float)doubleHolder;
        ROS_INFO("Got speedLimit: %f", speedLimit);
    }else{ROS_INFO("Failed to get speedLimit param, defaulting to 4.5");}
    
    while(ros::ok())
    {
        //checks for subscription callbacks to update
        ros::spinOnce();

        if(autoState.data){ // autonomous state just passes along the twist

            twistOut = twistIn;
            //boostState = false; // definitely don't want any speed boosts included in this

        }else{ // joystick control needs to convert the joy message into a twist
            
            twistOut = joyTwist;

            /*
            if(boostState){
                twistOut.linear.x *= 2;
                twistOut.angular.z *= 2;// switch to 1 + trigger maybe for controllable boost
            }
            */
        }

        arbitrator_pub.publish(twistOut);
        autostate_pub.publish(autoState);

        loop_rate.sleep();
    }

return 0;
}

