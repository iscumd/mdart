#include <gtest/gtest.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"

#include <sstream>
#include <vector>

#include "test/AVC_path_planner.cpp"
/*
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
*/

TEST(TestSuite, testCase1)
{
	PolarPoint N = new PolarPoint;
	PolarPoint E = new PolarPoint;
	PolarPoint W = new PolarPoint;
	PolarPoint NE = new PolarPoint;
	PolarPoint NW = new PolarPoint;
	
	N.distance = 1;
	E.distance = 1;
	W.distance = 1;
	NE.distance = 1;
	NW.distance = 1;
	
	N.angle = M_PI/2;
	E.angle = 0;
	W.angle = M_PI;
	NE.angle = M_PI/4;
	NW.angle = M_PI*3/4;
	
	delete N;
	delete E;
	delete W;
	delete NE;
	delete NW;
	
	ASSERT_EQ(true);
}
/*
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
*/

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "tester");
  ros::NodeHandle nh;
  return RUN_ALL_TESTS();
}



