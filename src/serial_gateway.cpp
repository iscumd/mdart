
#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>

serial::Serial ser;

void write_callback(const std_msgs::String::ConstPtr& msg){
    uint8_t num;
   uint8_t VESC_data[28]={0xA0,0x1A,	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xBA};
    ROS_INFO_STREAM("Writing VESC data to serial port" << VESC_data);
    num = ser.write(VESC_data,28);
    ROS_INFO("number of bytes %d", num);
}

int main (int argc, char** argv){
    ros::init(argc, argv, "serial_example_node");
    ros::NodeHandle nh;

    ros::Subscriber write_sub = nh.subscribe("write", 1000, write_callback);
    ros::Publisher read_pub = nh.advertise<std_msgs::String>("read", 1000);

    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(115200);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(100);
    while(ros::ok()){

        ros::spinOnce();

        if(ser.available()){
            ROS_INFO_STREAM("Reading from serial port");
            std_msgs::String result;
            result.data = ser.read(ser.available());
            ROS_INFO_STREAM("Read: " << result.data);

	    int j = 0,i;
	    char buff[200] = {0},temp;	    

	    for(i = 0; i < 28;i++)
	    {
		temp = (result.data[i]>>4) &0x0F;
		if(temp > 0x09)
		{
		    temp = (temp - 10)+0x41;
		}
		else
		{
		    temp = temp +0x30;
		}
		buff[j++] = temp;

		temp = result.data[i]&0x0F;
		if(temp > 0x09)
		{
		    temp = (temp - 10)+0x41;
		}
		else
		{
		    temp = temp +0x30;
		}
		buff[j++] = temp;
		buff[j++] = 0x20;
	    }
	    ROS_INFO_STREAM("Read: " << buff);

	    if (result.data[27] == 0xBA)
	    {
		ROS_INFO_STREAM("Data matches");
	    }

            read_pub.publish(result);
        }

        loop_rate.sleep();
    }
}
