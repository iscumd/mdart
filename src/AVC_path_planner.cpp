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
float minOpeningWidth = 1.2; // should be vehicle width + tolerance
//TODO: migrate to ros param file

struct PolarPoint
{
	float angle = 0;
	float distance = 0;
};
static PolarPoint tempPoint;

struct Opening 
{
  PolarPoint start, end, middle;
  bool set = false;
};
static Opening potentialOpening;

float distanceBetweenPoints(PolarPoint p1, PolarPoint p2)
{
	return sqrtf(
	(p1.distance * p1.distance) +
	(p2.distance * p2.distance) -
	(2 * p2.distance * p1.distance * 
	cosf(abs(p2.angle - p1.angle)))
	);
}

void flattenPolarPoints(PolarPoint p1, PolarPoint p2)
{
	if (p1.distance > p2.distance)
	{
		p1.distance = p2.distance;
	}
	else
	{
		p2.distance = p1.distance;
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
		else
		{
			if (potentialOpening.set)
			{
				
				//has both start and end
				if (distanceBetweenPoints(potentialOpening.start, potentialOpening.end) >= minOpeningWidth )
				{
					// opening is large enough for car to fit through
					
				}
						
			}
		}
	}
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "AVC_path_planner");
  // Q: Should the 3rd argument always be the file name?

  ros::NodeHandle nodeHandle;

  ros::Publisher path_pub = nodeHandle.advertise<geometry_msgs::Twist>("da_wae", 1);
  // last parameter: queue depth of 1, "low" depth as this info will probably become stale relatively fast
  // Q: if the queue fills, messages seem to be discarded - will it discard the oldest message from the queue or the new one attempted to be added to the queue?

    ros::Subscriber subscriber = nodeHandle.subscribe("scan", 1, newLidarDataCallback);

  ros::Rate loop_rate(50);
  // 50 hz publish rate

  while (ros::ok())
  {

    ros::spinOnce();
    // calls newLidarDataCallback if there are messages in it's queue to be run

    geometry_msgs::Twist path;

    /*
    float64 speed
    float64 turnRadius
    float64 distance
    */

 //     msg.speed = 1;
 //     msg.turnRadius = 0;
 //     msg.distance = 1;
 
 
//msg.linear.x = double(rand())/double(RAND_MAX); // vehicle speed in meters per second
//msg.angular.z = 2*double(rand())/double(RAND_MAX) - 1; // vehicle rotation in radians per second

	path_pub.publish(path);



      loop_rate.sleep();
      // sleep such as to run at 50hz
      // Q: if this function takes n time to run, will it compensate be removing the n time from the sleep amount in order to maintain 50hz?
  }

  return 0;
}



