#include <ros/ros.h>
#include <vector>
#include <math.h>
#include "std_msgs/String.h"
#include <sstream>


using namespace std;

class LineDetection
{



}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "talker");
	
	ros::NodeHandle n;
	
	ros::Publisher pubNode= n.advertise<std_msgs::String>("Line_Detection_msg", 1000);
	
	ros::Rate loop_rate(10);
	
	int count = 0;
	
	while(ros::ok)
	{
		std_msgs::String msg;
		
		std::stringstream ss;
		
		//float64 numPoints
		//float64 numRows
		//float64 numColumns
		//float64[][] confMatrix
		
		int numPoints=64, numRows = 12, numColumns = 6;
		int confMatrix[5][5] =0;
		
		ss<< "Number of Points: " << numPoints << " Number of Rows: " << numRows << " Number of Columns: " << numColumns << "Confidence Matrix: " << confMatrix;
		
		msg.data = ss.str();
		
		
		ROS_INFO("%s", msg.data.c_str());
		
		
		pubNode.publish(msg);
		
		ros::spinOnce();
		
		loop_rate.sleep();
	}
	
	return 0;
	
}
