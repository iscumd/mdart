#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

serial::Serial ser;
ros::Time prevTime;

void write_callback(const std_msgs::String::ConstPtr& msg){
    uint8_t num;
   	uint8_t VESC_data[28]={0xA0,0x1A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBA};
    ROS_INFO_STREAM("Writing VESC data to serial port" << VESC_data);
    num = ser.write(VESC_data,28);
    ROS_INFO("number of bytes %d", num);
    prevTime = ros::Time::now();
}

int main (int argc, char** argv){
    ros::init(argc, argv, "serial_example_node");
    ros::NodeHandle nh;
    std::string port;
    int j = 0,i;

    ros::Subscriber write_sub = nh.subscribe("write", 1000, write_callback);
    ros::Publisher read_pub = nh.advertise<std_msgs::String>("read", 1000);

	ser.setBaudrate(115200);
	serial::Timeout to = serial::Timeout::simpleTimeout(1000);
	ser.setTimeout(to);

    ros::Rate loop_rate(1);

    while(ros::ok()){

        ros::spinOnce();

		if(!ser.isOpen())
		{
			for(i = 0; i < 256;i ++)
			{
				if(!ser.isOpen())
				{
					port = "/dev/ttyUSB"+std::to_string(i);;
					ROS_INFO_STREAM("Trying to open port " << port);
					try
					{
						ser.setPort(port);
						ser.open();
					}
					catch (serial::IOException& e)
					{
						ROS_ERROR_STREAM("Failed to open port" << port);
					}
					
					if(i == 255)
					{
						ROS_ERROR_STREAM("No ports are available");
						return -1;
					}
				}
				else
				{
					ROS_INFO_STREAM("Serial Port initialized on" << port);
					break;
				}
			}
		}
		else
		{
			if(ser.available()){
				ROS_INFO_STREAM("Reading from serial port");
				std_msgs::String result;
				result.data = ser.read(ser.available());
				ROS_INFO_STREAM("Read: " << result.data);

				// char buff[200] = {0},temp;	    

				// for(i = 0; i < 28;i++)
				// {
					// temp = (result.data[i]>>4) &0x0F;
					// if(temp > 0x09)
					// {
						// temp = (temp - 10)+0x41;
					// }
					// else
					// {
						// temp = temp +0x30;
					// }
					// buff[j++] = temp;

					// temp = result.data[i]&0x0F;
					// if(temp > 0x09)
					// {
						// temp = (temp - 10)+0x41;
					// }
					// else
					// {
						// temp = temp +0x30;
					// }
				
					// buff[j++] = temp;
					// buff[j++] = 0x20;
				// }
				// ROS_INFO_STREAM("Read: " << buff);

				// if (result.data[27] == 0xBA)
				// {
					// ROS_INFO_STREAM("Data matches");
				// }
				read_pub.publish(result);
			}

			ros::Time currTime = ros::Time::now();
			ros::Duration diff= currTime-prevTime;
			if(diff.toSec() > 2)
			{
				ROS_INFO_STREAM("Update delayed for more than 2 secs. Perform evasive action");
				prevTime = currTime;
			}
		}
		loop_rate.sleep();
    }
}