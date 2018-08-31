#include "ros/ros.h"
#include "mdart/WheelVals.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <string>

geometry_msgs::Twist twistIn;
sensor_msgs::Imu imuIn;
mdart::WheelVals wheelOut;

// params
double doubleHolder;
float yAccelLimit; // max acceleration applied to driver in y-direction
float vehicleWidth; // dimensions to determine vehicle angles and speed
float vehicleLength; // dimensions to determine vehicle angles and speed
float speedLimit;
float wheelCircumference;

// some other stuff
float turnRadius; // used for determining wheel angles and velocities
float vehicleSpeedMod; // placeholder for modified speed
float rpmMod; // for converting m/s to rpm
float scrubRadius;
float scrubRight;
float scrubLeft;

// holders for vehicle dimensions
float xFrontLeft;
float xFrontRight;
float xRearLeft;
float xRearRight;
float yFrontLeft;
float yFrontRight;
float yRearLeft;
float yRearRight;


void twistCallback(const geometry_msgs::Twist::ConstPtr& twistCb)
{
    //
    twistIn = *twistCb;
    //
    ROS_INFO("vehicle_dynamics received the twist: linear.x = [%f] \tangular.z = [%f]", twistIn.linear.x, twistIn.angular.z);
    if (twistIn.linear.x > speedLimit){
        twistIn.angular.z *= speedLimit / twistIn.linear.x;
        twistIn.linear.x = speedLimit;
        ROS_INFO("vehicle_dynamics modified the twist: linear.x = [%f] \tangular.z = [%f]", twistIn.linear.x, twistIn.angular.z);
    }
}

void imuCallback(const sensor_msgs::Imu::ConstPtr& imuCb)
{
    //
    imuIn = *imuCb;
    //
    ROS_INFO("vehicle_dynamics received imu data. y accel: [%f]", imuIn.linear_acceleration.y);
}

 
int main(int argc, char **argv)
{
    // define name of node and start
    ros::init(argc, argv, "vehicle_dynamics");
    // The first nodehandle constructed will fully initialize this node
    ros::NodeHandle n;
    ros::NodeHandle nprivate("~");
    // define topic name to publish to and queue size
    ros::Publisher dynamics_pub = n.advertise<mdart::WheelVals>("wheels", 10);
    // define topic names to subscribe to and queue size
    ros::Subscriber twistSub = n.subscribe("arbitrator_output", 10, twistCallback);
    ros::Subscriber imuSub = n.subscribe("imu_in", 10, imuCallback);  //imuCallback not declared in scope
    // specify loop frequency, works with Rate::sleep to sleep for the correct time
    ros::Rate loop_rate(50);


    // get ros params
    if(n.param("vehicleWidth", doubleHolder, 3.0)){
        vehicleWidth = (float)doubleHolder;
        ROS_INFO("Got vehicleWidth: %f", vehicleWidth);
    }else{ROS_INFO("Failed to get vehicleWidth param, defaulting to 3");}

    if(n.param("vehicleLength", doubleHolder, 3.2)){
        vehicleLength = (float)doubleHolder;
        ROS_INFO("Got vehicleLength: %f", vehicleLength);
    }else{ROS_INFO("Failed to get vehicleLength param, defaulting to 3.2");} 

    if(n.param("wheelCircumference", doubleHolder, 0.638)){
        wheelCircumference = (float)doubleHolder;
        ROS_INFO("Got wheelCircumference: %f", wheelCircumference);
    }else{ROS_INFO("Failed to get wheelCircumference param, defaulting to .638");}

    if(nprivate.param("scrubRadius", doubleHolder, 0.0762)){
        scrubRadius = (float)doubleHolder;
        ROS_INFO("Got scrubRadius: %f", scrubRadius);
    }else{ROS_INFO("Failed to get scrubRadius param, defaulting to 0.0762");}

    if(nprivate.param("yAccelLimit", doubleHolder, 2.0)){
        yAccelLimit = (float)doubleHolder;
        ROS_INFO("Got yAccelLimit: %f", yAccelLimit);
    }else{ROS_INFO("Failed to get yAccelLimit param, defaulting to 2");}

    if(nprivate.param("speedLimit", doubleHolder, 4.5)){
        speedLimit = (float)doubleHolder;
        ROS_INFO("Got speedLimit: %f", speedLimit);
    }else{ROS_INFO("Failed to get speedLimit param, defaulting to 4.5");}


    // calculate some thingies too
    rpmMod = 60 / wheelCircumference; // rev/ m / min

    // x coordinates of each wheel in meters
    xFrontRight = vehicleWidth/2; xRearRight = vehicleWidth/2;
    xFrontLeft = -vehicleWidth/2; xRearLeft = -vehicleWidth/2;
    
    // y coordinates of each wheel in meters
    yFrontLeft = vehicleLength/2; yFrontRight = vehicleLength/2;
    yRearLeft = -vehicleLength/2; yRearRight = -vehicleLength/2;
    
    
    while(ros::ok())
    {
        //checks for subscription callbacks to update
        ros::spinOnce();

        // input modification
        if((imuIn.linear_acceleration_covariance[0] != -1) && ((float) abs(imuIn.linear_acceleration.y) > yAccelLimit)){ // might be imuIn->linear_acceleration_covariance[0]
            // do some stuff bc lin accel exists
            // this is where the speed control should be done
            
            //yAccelerationDiff = (float) abs(imuIn.linear_acceleration.y) - yAccelLimit;
            //vehicleSpeedMod = yAccelLimit / (yAccelerationDiff + yAccelLimit);
            vehicleSpeedMod = yAccelLimit / ((float) abs(imuIn.linear_acceleration.y));

            ROS_INFO("vehicle_dynamics corrected speed from [%f] to [%f]", twistIn.linear.x, (twistIn.linear.x * vehicleSpeedMod));

            twistIn.linear.x  *= vehicleSpeedMod;
            twistIn.angular.z *= vehicleSpeedMod;
        }

        // input -> output conversion
        if(twistIn.angular.z == 0){ // Yeah so if you could not divide by zero, that'd be great...
            // drive straight I guess
			
            wheelOut.angleFrontLeft  = 0;
            wheelOut.angleFrontRight = 0;
            wheelOut.angleRearLeft   = 0;
            wheelOut.angleRearRight  = 0;
            
            // yeah just keep driving
            wheelOut.speedFrontLeft  = rpmMod * twistIn.linear.x;
            wheelOut.speedFrontRight = rpmMod * twistIn.linear.x;
            wheelOut.speedRearLeft   = rpmMod * twistIn.linear.x;
            wheelOut.speedRearRight  = rpmMod * twistIn.linear.x;
			
        }else if(twistIn.linear.x == 0){
            
            turnRadius = (.15 * 4.5 / twistIn.angular.z) * (vehicleWidth / 2);

            wheelOut.speedFrontLeft  = 0;
            wheelOut.speedFrontRight = 0;
            wheelOut.speedRearLeft   = 0;
            wheelOut.speedRearRight  = 0;

            wheelOut.angleFrontLeft  = ((float) atan(yFrontLeft  / (turnRadius - xFrontLeft))) * 180 / 3.14159;
            wheelOut.angleFrontRight = ((float) atan(yFrontRight / (turnRadius - xFrontRight))) * 180 / 3.14159;
            wheelOut.angleRearLeft   = ((float) atan(yRearLeft   / (turnRadius - xRearLeft))) * 180 / 3.14159;
            wheelOut.angleRearRight  = ((float) atan(yRearRight  / (turnRadius - xRearRight))) * 180 / 3.14159;

        }else{
            
            // turn angular z and linear x into turn radius

            turnRadius = (twistIn.linear.x / twistIn.angular.z) * (vehicleWidth / 2);
			
            if(turnRadius < 0){
                scrubLeft = -scrubRadius;
                scrubRight = scrubRadius;
            }else{
                scrubLeft = scrubRadius;
                scrubRight = -scrubRadius;
            }

            // I believe you have my stapler.
            wheelOut.angleFrontLeft  = ((float) atan(yFrontLeft  / (turnRadius - xFrontLeft))) * 180 / 3.14159;
            wheelOut.angleFrontRight = ((float) atan(yFrontRight / (turnRadius - xFrontRight))) * 180 / 3.14159;
            wheelOut.angleRearLeft   = ((float) atan(yRearLeft   / (turnRadius - xRearLeft))) * 180 / 3.14159;
            wheelOut.angleRearRight  = ((float) atan(yRearRight  / (turnRadius - xRearRight))) * 180 / 3.14159;

            // Illegal? Samir, this is America!
            wheelOut.speedFrontLeft  = rpmMod * twistIn.linear.x * (sqrtf( yFrontLeft * yFrontLeft + (turnRadius - xFrontLeft) * (turnRadius - xFrontLeft)) + scrubLeft) / abs(turnRadius);
            wheelOut.speedFrontRight = rpmMod * twistIn.linear.x * (sqrtf( yFrontRight * yFrontRight + (turnRadius - xFrontRight) * (turnRadius - xFrontRight)) + scrubRight) / abs(turnRadius);
            wheelOut.speedRearLeft   = rpmMod * twistIn.linear.x * (sqrtf( yRearLeft * yRearLeft + (turnRadius - xRearLeft) * (turnRadius - xRearLeft)) + scrubLeft) / abs(turnRadius);
            wheelOut.speedRearRight  = rpmMod * twistIn.linear.x * (sqrtf( yRearRight * yRearRight + (turnRadius - xRearRight) * (turnRadius - xRearRight)) + scrubRight) / abs(turnRadius);
			
        }

        // I HAVE PEOPLE SKILLS!

        //ROS_INFO("vehicle_dynamics published: linear.x = [%f] \tangular.z = [%f]",  twistIn.angular.z);
        dynamics_pub.publish(wheelOut);

        // The thing is, Bob, it's not that I'm lazy, it's that I just don't care. 
        loop_rate.sleep();
    }
return 0;
}
