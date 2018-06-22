#include "geometry_msgs/Twist.h"
#include "mdart/WheelVals.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include <cmath>
#include <string>
// may need, may not
// #include <boost/circular_buffer.hpp>

geometry_msgs::Twist twistIn;
sensor_msgs::Imu imuIn;
//mdart::WheelVals odomIn;
//mdart::WheelVals wheelOut;

float yAccelerationLimit; // max acceleration applied to driver in y-direction
// float yAccelerationDiff; // possibly don't need if just inverse works well
// enough
float vehicleWidth;  // dimensions to determine vehicle angles and speed
float vehicleLength; // dimensions to determine vehicle angles and speed
float speedLimit;
float wheelCircumference;

//
float turnRadius;      // used for determining wheel angles and velocities
float vehicleSpeedMod; // placeholder for modified speed
float rpmMod;

// holders for vehicle dimensions
float xFrontLeft;
float xFrontRight;
float xRearLeft;
float xRearRight;
float yFrontLeft;
float yFrontRight;
float yRearLeft;
float yRearRight;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
void twistCallback(const geometry_msgs::Twist::ConstPtr &twistCb) {
  //
  twistIn = *twistCb;
  //
  // ROS_INFO("vehicle_dynamics received the twist: linear.x = [%f] \tangular.z
  // = [%f]",  twistIn.angular.z);
}

void odomCallback(const mdart::WheelVals::ConstPtr &odomCb) {
  // tbh don't even know if i'll need this like fr what do i need this for
  // lastOdomIn = odomIn;
  odomIn = *odomCb;
  // ROS_INFO("vehicle_dynamics received the wheel odometry: [%s]",
  // scan->ranges[539].c_str());
<<<<<<< HEAD
}

void imuCallback(const sensor_msgs::Imu::ConstPtr &imuCb) {
  //
  imuIn = *imuCb;
  //
  ROS_INFO("vehicle_dynamics received imu data. y accel: [%f]",
           imuIn.linear_acceleration.y);
}

int main(int argc, char **argv) {
  // define some stuff -- will probably later be done with rosParams
  vehicleWidth = 3.0;      // m
  vehicleLength = 3.2;     // m
  wheelCircumference = .4; // m/rev
  speedLimit = 12;         // m/s
  yAccelerationLimit = 2;  // m/s^2

  // calculate some thingies too
  rpmMod = speedLimit * 60 / wheelCircumference; // rev/min
  // x coordinates of each wheel in meters
  xFrontLeft = -vehicleWidth / 2;
  xFrontRight = vehicleWidth / 2;
  xRearLeft = -vehicleWidth / 2;
  xRearRight = vehicleWidth / 2;
  // y coordinates of each wheel in meters
  yFrontLeft = vehicleLength / 2;
  yFrontRight = vehicleLength / 2;
  yRearLeft = -vehicleLength / 2;
  yRearRight = -vehicleLength / 2;

  // define name of node and start
  ros::init(argc, argv, "vehicle_dynamics");
  // The first NodeHandle constructed will fully initialize this node
  ros::NodeHandle nodeHandle;
  // define topic name to publish to and queue size
  ros::Publisher dynamics_pub =
      nodeHandle.advertise<mdart::WheelVals>("wheels", 10);
  // define topic names to subscribe to and queue size
  ros::Subscriber twistSub =
      nodeHandle.subscribe("arbitrator_output", 10, twistCallback);
  //   ros::Subscriber imuSub = nodeHandle.subscribe("imu_in", 10, imuCallback);
  //   imuCallback not declared in scope
  // specify loop frequency, works with Rate::sleep to sleep for the correct
  // time
  ros::Rate loop_rate(50);

  while (ros::ok()) {
    // checks for subscription callbacks to update
    ros::spinOnce();

    // input modification
    if ((imuIn.linear_acceleration_covariance[0] != -1) &&
        (abs(imuIn.linear_acceleration.y) > yAccelerationLimit)) { // might be
      // imuIn->linear_acceleration_covariance[0]
      // do some stuff bc lin accel exists
      // this is where the speed control should be done

      // yAccelerationDiff = abs(imuIn.linear_acceleration.y) -
      // yAccelerationLimit;
      // vehicleSpeedMod = yAccelerationLimit / (yAccelerationDiff +
      // yAccelerationLimit);
      vehicleSpeedMod = yAccelerationLimit / abs(imuIn.linear_acceleration.y);

      ROS_INFO("vehicle_dynamics corrected speed from [%f] to [%f]",
               twistIn.linear.x, (twistIn.linear.x * vehicleSpeedMod));

      twistIn.linear.x *= vehicleSpeedMod;
      twistIn.angular.z *= vehicleSpeedMod;
    }

    // input -> output conversion
    if (twistIn.angular.z ==
        0) { // Yeah so if you could not divide by zero, that'd be great...
             // drive straight I guess
             /*
       wheelOut.angleFrontLeft  = 0;
       wheelOut.angleFrontRight = 0;
       wheelOut.angleRearLeft   = 0;
       wheelOut.angleRearRight  = 0;
       
       
       // yeah just keep driving
       wheelOut.speedFrontLeft  = twistIn.linear.x;
       wheelOut.speedFrontRight = twistIn.linear.x;
       wheelOut.speedRearLeft   = twistIn.linear.x;
       wheelOut.speedRearRight  = twistIn.linear.x;
       
             */
    } else {
      // turn angular z and linear x into turn radius
      turnRadius = (twistIn.linear.x / twistIn.angular.z) * (vehicleWidth / 2);

=======
}

void imuCallback(const sensor_msgs::Imu::ConstPtr &imuCb) {
  //
  imuIn = *imuCb;
  //
  ROS_INFO("vehicle_dynamics received imu data. y accel: [%f]",
           imuIn.linear_acceleration.y);
}

int main(int argc, char **argv) {
  // define some stuff -- will probably later be done with rosParams
  vehicleWidth = 3.0;      // m
  vehicleLength = 3.2;     // m
  wheelCircumference = .4; // m/rev
  speedLimit = 12;         // m/s
  yAccelerationLimit = 2;  // m/s^2

  // calculate some thingies too
  rpmMod = speedLimit * 60 / wheelCircumference; // rev/min
  // x coordinates of each wheel in meters
  xFrontLeft = -vehicleWidth / 2;
  xFrontRight = vehicleWidth / 2;
  xRearLeft = -vehicleWidth / 2;
  xRearRight = vehicleWidth / 2;
  // y coordinates of each wheel in meters
  yFrontLeft = vehicleLength / 2;
  yFrontRight = vehicleLength / 2;
  yRearLeft = -vehicleLength / 2;
  yRearRight = -vehicleLength / 2;

  // define name of node and start
  ros::init(argc, argv, "vehicle_dynamics");
  // The first NodeHandle constructed will fully initialize this node
  ros::NodeHandle nodeHandle;
  // define topic name to publish to and queue size
  ros::Publisher dynamics_pub =
      nodeHandle.advertise<mdart::WheelVals>("wheels", 10);
  // define topic names to subscribe to and queue size
  ros::Subscriber twistSub =
      nodeHandle.subscribe("arbitrator_output", 10, twistCallback);
  //   ros::Subscriber imuSub = nodeHandle.subscribe("imu_in", 10, imuCallback);
  //   imuCallback not declared in scope
  // specify loop frequency, works with Rate::sleep to sleep for the correct
  // time
  ros::Rate loop_rate(50);

  while (ros::ok()) {
    // checks for subscription callbacks to update
    ros::spinOnce();

    // input modification
    if ((imuIn.linear_acceleration_covariance[0] != -1) &&
        (abs(imuIn.linear_acceleration.y) > yAccelerationLimit)) { // might be
      // imuIn->linear_acceleration_covariance[0]
      // do some stuff bc lin accel exists
      // this is where the speed control should be done

      // yAccelerationDiff = abs(imuIn.linear_acceleration.y) -
      // yAccelerationLimit;
      // vehicleSpeedMod = yAccelerationLimit / (yAccelerationDiff +
      // yAccelerationLimit);
      vehicleSpeedMod = yAccelerationLimit / abs(imuIn.linear_acceleration.y);

      ROS_INFO("vehicle_dynamics corrected speed from [%f] to [%f]",
               twistIn.linear.x, (twistIn.linear.x * vehicleSpeedMod));

      twistIn.linear.x *= vehicleSpeedMod;
      twistIn.angular.z *= vehicleSpeedMod;
    }

    // input -> output conversion
    if (twistIn.angular.z ==
        0) { // Yeah so if you could not divide by zero, that'd be great...
             // drive straight I guess
             /*
       wheelOut.angleFrontLeft  = 0;
       wheelOut.angleFrontRight = 0;
       wheelOut.angleRearLeft   = 0;
       wheelOut.angleRearRight  = 0;
       
       
       // yeah just keep driving
       wheelOut.speedFrontLeft  = twistIn.linear.x;
       wheelOut.speedFrontRight = twistIn.linear.x;
       wheelOut.speedRearLeft   = twistIn.linear.x;
       wheelOut.speedRearRight  = twistIn.linear.x;
       
             */
    } else {
      // turn angular z and linear x into turn radius
      turnRadius = (twistIn.linear.x / twistIn.angular.z) * (vehicleWidth / 2);

>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
      // I believe you have my stapler.
      wheelOut.angleFrontLeft = atan(yFrontLeft / (turnRadius - xFrontLeft));
      wheelOut.angleFrontRight = atan(yFrontRight / (turnRadius - xFrontRight));
      wheelOut.angleRearLeft = atan(yRearLeft / (turnRadius - xRearLeft));
      wheelOut.angleRearRight = atan(yRearRight / (turnRadius - xRearRight));

      // Illegal? Samir, this is America!
      wheelOut.speedFrontLeft =
          twistIn.linear.x *
          sqrt(pow(yFrontLeft, 2) + pow(turnRadius - xFrontLeft, 2));
      wheelOut.speedFrontRight =
          twistIn.linear.x *
          sqrt(pow(yFrontRight, 2) + pow(turnRadius - xFrontRight, 2));
      wheelOut.speedRearLeft =
          twistIn.linear.x *
          sqrt(pow(yRearLeft, 2) + pow(turnRadius - xRearLeft, 2));
      wheelOut.speedRearRight =
          twistIn.linear.x *
          sqrt(pow(yRearRight, 2) + pow(turnRadius - xRearRight, 2));
<<<<<<< HEAD
=======
int main(int argc, char **argv)
{
    // define some stuff -- will probably later be done with rosParams
    vehicleWidth = 3.0; // m
    vehicleLength = 3.2; // m
    wheelCircumference = .4; // m/rev
    speedLimit = 12; // m/s
    yAccelerationLimit = 2; // m/s^2

    // calculate some thingies too
    rpmMod = speedLimit * 60 / wheelCircumference; // rev/min
    // x coordinates of each wheel in meters
    xFrontLeft = -vehicleWidth/2;
    xFrontRight = vehicleWidth/2;
    xRearLeft = -vehicleWidth/2;
    xRearRight = vehicleWidth/2;
    // y coordinates of each wheel in meters
    yFrontLeft = vehicleLength/2;
    yFrontRight = vehicleLength/2;
    yRearLeft = -vehicleLength/2;
    yRearRight = -vehicleLength/2;


    // define name of node and start
    ros::init(argc, argv, "vehicle_dynamics");
    // The first NodeHandle constructed will fully initialize this node
    ros::NodeHandle nodeHandle;
    // define topic name to publish to and queue size
//    ros::Publisher dynamicsPub = nodeHandle.advertise<mdart::WheelVals>("wheels", 10) 
    // define topic names to subscribe to and queue size
//    ros::Subscriber twistSub = nodeHandle.subscribe("arbitrator_output", 10, twistCallback);
 //   ros::Subscriber imuSub = nodeHandle.subscribe("imu_in", 10, imuCallback);  imuCallback not declared in scope
    // specify loop frequency, works with Rate::sleep to sleep for the correct time
    ros::Rate loop_rate(50);

    
    while(ros::ok())
    {
        //checks for subscription callbacks to update
        ros::spinOnce();

        // input modification
        if((imuIn.linear_acceleration_covariance[0] != -1) && (abs(imuIn.linear_acceleration.y) > yAccelerationLimit)){ // might be imuIn->linear_acceleration_covariance[0]
            // do some stuff bc lin accel exists
            // this is where the speed control should be done
            
            //yAccelerationDiff = abs(imuIn.linear_acceleration.y) - yAccelerationLimit;
            //vehicleSpeedMod = yAccelerationLimit / (yAccelerationDiff + yAccelerationLimit);
            vehicleSpeedMod = yAccelerationLimit / abs(imuIn.linear_acceleration.y);

            ROS_INFO("vehicle_dynamics corrected speed from [%f] to [%f]", twistIn.linear.x, (twistIn.linear.x * vehicleSpeedMod));
            
            twistIn.linear.x  *= vehicleSpeedMod;
            twistIn.angular.z *= vehicleSpeedMod;
        }

        // input -> output conversion
        if(twistIn.angular.z == 0){ // Yeah so if you could not divide by zero, that'd be great...
            // drive straight I guess
			/*
            wheelOut.angleFrontLeft  = 0;
            wheelOut.angleFrontRight = 0;
            wheelOut.angleRearLeft   = 0;
            wheelOut.angleRearRight  = 0;
			

            // yeah just keep driving
            wheelOut.speedFrontLeft  = twistIn.linear.x;
            wheelOut.speedFrontRight = twistIn.linear.x;
            wheelOut.speedRearLeft   = twistIn.linear.x;
            wheelOut.speedRearRight  = twistIn.linear.x;
			
			*/
        }else{
            // turn angular z and linear x into turn radius
            turnRadius = (twistIn.linear.x / twistIn.angular.z) * (vehicleWidth / 2);
			/*
            // I believe you have my stapler.
            wheelOut.angleFrontLeft  = atan(yFrontLeft  / (turnRadius - xFrontLeft));
            wheelOut.angleFrontRight = atan(yFrontRight / (turnRadius - xFrontRight));
            wheelOut.angleRearLeft   = atan(yRearLeft   / (turnRadius - xRearLeft));
            wheelOut.angleRearRight  = atan(yRearRight  / (turnRadius - xRearRight));

            // Illegal? Samir, this is America!
            wheelOut.speedFrontLeft  = twistIn.linear.x * sqrt( pow(yFrontLeft,  2) + pow(turnRadius - xFrontLeft,  2) );
            wheelOut.speedFrontRight = twistIn.linear.x * sqrt( pow(yFrontRight, 2) + pow(turnRadius - xFrontRight, 2) );
            wheelOut.speedRearLeft   = twistIn.linear.x * sqrt( pow(yRearLeft,   2) + pow(turnRadius - xRearLeft,   2) );
            wheelOut.speedRearRight  = twistIn.linear.x * sqrt( pow(yRearRight,  2) + pow(turnRadius - xRearRight,  2) );
			*/
        }

        // I HAVE PEOPLE SKILLS!
        //dynamics_pub.publish(wheelOut);

        // The thing is, Bob, it's not that I'm lazy, it's that I just don't care. 
        loop_rate.sleep();
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
    }

<<<<<<< HEAD
=======
    }

>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
    // I HAVE PEOPLE SKILLS!
    dynamics_pub.publish(wheelOut);

    // The thing is, Bob, it's not that I'm lazy, it's that I just don't care.
    loop_rate.sleep();
  }
  return 0;
}
<<<<<<< HEAD
=======
/*
void twistCallback(const geometry_msgs::Twist::ConstPtr& twistCb)
{
    //
    twistIn = *twistCb;
    //
    //ROS_INFO("vehicle_dynamics received the twist: linear.x = [%f] \tangular.z = [%f]",  twistIn.angular.z);
}
*/
/*
void odomCallback(const mdart::WheelVals::ConstPtr& odomCb)
{
    // tbh don't even know if i'll need this like fr what do i need this for
    //lastOdomIn = odomIn;
    odomIn = *odomCb;
    //ROS_INFO("vehicle_dynamics received the wheel odometry: [%s]", scan->ranges[539].c_str());
}
*/
/*
void imuCallback(const sensor_msgs::Imu::ConstPtr& imuCb)
{
    //
    imuIn = *imuCb;
    //
    ROS_INFO("vehicle_dynamics received imu data. y accel: [%f]", imuIn.linear_acceleration.y);
}
*/
>>>>>>> parent of 4927c38... added msg files to cmakelists & uncommented code to fix
=======
>>>>>>> 0434221792dab840a2a45be5f002358845a55c19
