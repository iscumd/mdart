#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include "mdart/Path.h"

#include <sstream>
#include <vector>


// lidar scan variables
float start, end, resolution;
int numPoints;
float minRange = 1; // must be 1m away to be considered an opening
float vehicleWidth = 1; // TODO: verify once vehicle is complete
float minOpeningWidth = vehicleWidth * 1.2; // should be vehicle width + tolerance (20%)
//TODO: migrate to ros param file

geometry_msgs::Twist path;
ros::Publisher path_pub;

struct PolarPoint
{
  float angle = 0;
  float distance = 0;
};
static PolarPoint tempPoint;

struct Opening 
{
  PolarPoint start, end; // TODO: check that removing middle didn't break stuff
  bool set = false;
};
static Opening potentialOpening;

float distanceBetweenPoints(const PolarPoint &p1, const PolarPoint &p2)
{
  return sqrtf(
  (p1.distance * p1.distance) +
  (p2.distance * p2.distance) -
  (2 * p2.distance * p1.distance * 
  cosf(abs(p2.angle - p1.angle)))
  );
}

void stop()
{
    path.linear.x = 0;
    path.linear.y = 0;
    path.linear.z = 0;
    
    path.angular.x = 0;
    path.angular.y = 0;
    path.angular.z = .0;
}

float getVelocity(const PolarPoint &target)
{
  float numMotors = 4; // using float for math reasons
  float torquePerMotor = 18;
  float radiusOfTire = .1016;
  float massOfCar = 100;
  
  float frictionCoefficient = 0.03;
  float accelerationOfGravity = 9.81;
  
  float velocity = sqrt(2 * numMotors * ( torquePerMotor / radiusOfTire ) * (target.distance / massOfCar) );
  if (abs(target.angle) < .1) // this magic number is OK, ~5.7 degrees - basically close enough to straight
  {
    return velocity;
  }
  // not straight, thus need to take turn speed limit into account
  
  //convert to cartesian, y is right, x is forward
  float y = target.distance * sin(target.angle);
  float x = target.distance * cos(target.angle);
  
  assert(x > 0); // TODO: remove sanity check
  
  float turnRadius = ((x * x) + (y * y)) / (2 * x);
  
  float turnVelocity = sqrt(frictionCoefficient * accelerationOfGravity * turnRadius);
  
  return std::min(turnVelocity, velocity);
}

void flattenPolarPoints(PolarPoint &p1, PolarPoint &p2)
{
  //lowers the distance of the further point such that when comparing the distance between them, it is perpendicular to the point of origin
  
  if (p1.distance > p2.distance)
  {
    p1.distance = p2.distance;
  }
  else
  {
    p2.distance = p1.distance;
  }
}

Opening setCenterOpening(std::vector<Opening> &openings, Opening &result)
{
  result.set = false;
  for (auto &iter : openings)  // c++11 needed for auto iter
  {
    if (false == result.set)
    {
      result = iter;
    }
    else
    {
      if (abs(result.start.angle+result.end.angle) > abs(iter.start.angle+iter.end.angle) )
      {
        result = iter;
      }
      // else the result opening was already closer to center than it
    }
  }
}

void newLidarDataCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  start = scan->angle_min; //radians
  end = scan->angle_max; //radians
  resolution = scan->angle_increment;  //radians
  numPoints = ( end - start ) / resolution;

  ROS_INFO("PathGenerator Received LaserScan: [%f]", scan->ranges[(numPoints/2)]);
  
  std::vector<Opening> openings;
  
  potentialOpening.set = false;
  tempPoint.angle = start;
  for (int i = 0; i < numPoints; ++i)
  {
    tempPoint.angle += resolution;
    if (scan->ranges[i] > minRange)
    {
      if (false == potentialOpening.set)
      {
        //1st point in opening
        
        tempPoint.distance = scan->ranges[i];
        potentialOpening.start = tempPoint;
        potentialOpening.end = tempPoint;
        potentialOpening.set = true;
        
      }
      else
      {
        //move last point to here
        potentialOpening.end = tempPoint;
      }
    }
    else  //no longer potential opening point
    {
      if (potentialOpening.set)
      {
        //has both start and end
        flattenPolarPoints(potentialOpening.start, potentialOpening.end);
        
        if (distanceBetweenPoints(potentialOpening.start, potentialOpening.end) >= minOpeningWidth )
        {
          // opening is large enough for car to fit through
          openings.push_back(potentialOpening);
        }
        potentialOpening.set = false; 
      }
    }
  } // end potentialOpening search
  
  setCenterOpening(openings, potentialOpening);
  
  stop();
  if (false == potentialOpening.set)
  {
    /*
    path.angular.z = .05f;  // TODO: fix magic number, also what are the units? radians per second?
    */ // commenting out for now to not turn in place if no path found for easier testing
    // no opening found, turn in place?
  }
  else
  {
    // TODO: check that path is clear from obstacles before proceeding and/or plan around obstacles
    PolarPoint target = potentialOpening.start;
    target.angle = (potentialOpening.start.angle + potentialOpening.end.angle) / 2;
    float velocity = getVelocity(target);
    path.linear.x = velocity; // TODO: confirm X is forward direction
    path.angular.z = (velocity / (potentialOpening.start.angle + potentialOpening.end.angle)) * (vehicleWidth / 2);
  }
  
  // output path!
  path_pub.publish(path);
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "AVC_path_planner");
  // Q: Should the 3rd argument always be the file name?

  ros::NodeHandle nodeHandle;

  path_pub = nodeHandle.advertise<geometry_msgs::Twist>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the oldest message from the queue or the new one attempted to be added to the queue?

    ros::Subscriber subscriber = nodeHandle.subscribe("scan", 1, newLidarDataCallback);

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok())
  {
    ros::spinOnce();
    // calls newLidarDataCallback if there are messages in it's queue to be run

    stop(); 

    loop_rate.sleep();
    // sleep such as to run at 50hz
    // Q: if this function takes n time to run, will it compensate be removing the n time from the sleep amount in order to maintain 50hz?
  }

  return 0;
}



