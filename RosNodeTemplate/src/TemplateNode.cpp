#include "ros/ros.h"
#include "NodeFolder/MsgFileName.h"
#include "ReadingNodeFolder/ReadingMsgFileName.h"

ros::Publisher SamplePublisher;
// makes a global publisher for use in functions and main

void FunctionName(const SubcriberBase::SubscriberName::ConstPtr& Data){
	
	NodeFolder::MsgFileName msg;
	//Grabs the variables from the msg file

	//set variable values
	//For Example
	msg.variableA = 25;
	msg.variableB = 1.337;
	msg.variableC[2] = 6.6;
 
	//publish new variable values
	SamplePublisher.publish(msg);
}

int main(int argc, char **argv) 

	ros::init(argc, argv, "NodeName"); //start node

	ros::NodeHandle n;	//Ros handler don't need to touch
	
	SamplePublisher = n.advertise<NodeFolder::MsgFileName>("NodeTopicWriting", 1000);//used for sending

	ros::Subscriber sub = n.subscribe("NodeTopicReading", 1000, FunctionName);//used for recieving
	
	ros::spin();	

	return 0;	
}
