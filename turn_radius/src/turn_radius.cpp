#include "turn_radius/turn.h"
#include "ros/ros.h"

#include "sensor_msgs/Joy.h"

#define Angle 45
#define DeadMan Data->axes[2]       // LTrigger
#define Nmode Data->buttons[0]      // A
#define Omode Data->buttons[1]      // B
#define Smode Data->buttons[2]      // X
#define Cmode Data->buttons[3]      // Y
#define HBrake Data->buttons[4]     // LBummper
#define Throttle Data->axes[1]      // LeftStick_UD
#define Yaw Data->axes[0]           // LeftStick_LR
#define IntYaw ((int)(Yaw * Angle)) // integer value

// BUTTON_A joy->buttons[0]
// BUTTON_B joy->buttons[1]
// BUTTON_X joy->buttons[2]
// BUTTON_Y joy->buttons[3]
// BUTTON_LB joy->buttons[4]
// BUTTON_RB joy->buttons[5]
// BUTTON_BACK joy->buttons[6]
// BUTTON_START joy->buttons[7]
// BUTTON_GUIDE joy->buttons[8]
// BUTTON_LS joy->buttons[9]
// BUTTON_RS joy->buttons[10]

// AXIS_L_LR joy->axes[0]
// AXIS_L_UD joy->axes[1]
// AXIS_LT joy->axes[2]
// AXIS_R_LR joy->axes[3]
// AXIS_R_UD joy->axes[4]
// AXIS_RT joy->axes[5]
// AXIS_DPAD_LR joy->axes[6]
// AXIS_DPAD_UD joy->axes[7]

ros::Publisher wheelInfo;

enum DriveType { Normal, Omni, Swivel, Circle };

void turnRadius(const sensor_msgs::Joy::ConstPtr &Data) {
  turn_radius::turn msg;
  static enum DriveType DriveMode;

  if (Nmode == 1)
    DriveMode = Normal;
  else if (Omode == 1)
    DriveMode = Omni;
  else if (Smode == 1)
    DriveMode = Swivel;
  else if (Cmode == 1)
    DriveMode = Circle;

  if (DeadMan >= 0) { // button isn't atleast half pressed
    msg.Wheels[0] = 0;
    msg.Wheels[1] = 0;
    msg.Wheels[2] = 0;
    msg.Wheels[3] = 0;
    msg.Axis[0] = 0;
    msg.Axis[1] = 0;
    msg.Axis[2] = 0;
    msg.Axis[3] = 0;
  } else if (HBrake == true) { // hard stop
    msg.Wheels[0] = 0;         // right+ left-
    msg.Wheels[1] = 0;
    msg.Wheels[2] = 0;
    msg.Wheels[3] = 0;
    msg.Axis[0] = -Angle;
    msg.Axis[1] = -Angle;
    msg.Axis[2] = Angle;
    msg.Axis[3] = Angle;
  } else if (DriveMode == Normal) { // noraml movement
    msg.Wheels[0] = Throttle;       // right+ left-
    msg.Wheels[1] = Throttle;
    msg.Wheels[2] = -Throttle;
    msg.Wheels[3] = -Throttle;
    msg.Axis[0] = IntYaw; // lock the back wheels to straight
    msg.Axis[1] = 0;
    msg.Axis[2] = 0;
    msg.Axis[3] = IntYaw;
  } else if (DriveMode == Omni) { // greatest turn radius
    msg.Wheels[0] = Throttle;     // right+ left-
    msg.Wheels[1] = Throttle;
    msg.Wheels[2] = -Throttle;
    msg.Wheels[3] = -Throttle;
    msg.Axis[0] = IntYaw;
    msg.Axis[1] = -IntYaw;
    msg.Axis[2] = -IntYaw;
    msg.Axis[3] = IntYaw;
  } else if (DriveMode == Swivel) { // swivel or straifing
    msg.Wheels[0] = Throttle;       // right+ left-
    msg.Wheels[1] = Throttle;
    msg.Wheels[2] = -Throttle;
    msg.Wheels[3] = -Throttle;
    msg.Axis[0] = IntYaw;
    msg.Axis[1] = IntYaw;
    msg.Axis[2] = IntYaw;
    msg.Axis[3] = IntYaw;
  } else if (DriveMode == Circle) { // Spinning in a Circle
    msg.Wheels[0] = -Yaw;
    msg.Wheels[1] = -Yaw;
    msg.Wheels[2] = -Yaw;
    msg.Wheels[3] = -Yaw;
    msg.Axis[0] = -Angle;
    msg.Axis[1] = Angle;
    msg.Axis[2] = Angle;
    msg.Axis[3] = -Angle;
  }

  wheelInfo.publish(msg);
}

int main(int argc, char **argv) // needed for ROS Functions
{
  ros::init(argc, argv, "turn_radius"); // start turn_radius node

  ros::NodeHandle n;
  // messafe location?
  wheelInfo =
      n.advertise<turn_radius::turn>("wheel_vals", 1000); // used for sending
  ros::Subscriber sub =
      n.subscribe("joy", 1000, turnRadius); // used for recieving

  ros::spin();

  return 0;
}
