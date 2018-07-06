#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <mdart/WheelVals.h>

// (UART0_valRxData[2])
// case 0: DutyCycle(000) data/100000

// case 1: Current(100) data/1000
// case 2: RPM(300) data/1
// default/3: brake(200) data/1000
// CAN_valMot1Data = ((uint32_t) UART0_valRxData[3]) << 24 | ((uint32_t) UART0_valRxData[4]) << 16 |
// 					((uint32_t) UART0_valRxData[5]) << 8 |  ((uint32_t) UART0_valRxData[6]);
// CAN_valMot2Data = ((uint32_t) UART0_valRxData[7]) << 24 | ((uint32_t) UART0_valRxData[8]) << 16 |
// 					((uint32_t) UART0_valRxData[9]) << 8 |  ((uint32_t) UART0_valRxData[10]);
// CAN_valMot3Data = ((uint32_t) UART0_valRxData[11]) << 24 | ((uint32_t) UART0_valRxData[12]) << 16 |
// 					((uint32_t) UART0_valRxData[13]) << 8 |  ((uint32_t) UART0_valRxData[14]);
// CAN_valMot4Data = ((uint32_t) UART0_valRxData[15]) << 24 | ((uint32_t) UART0_valRxData[16]) << 16 |
// 					((uint32_t) UART0_valRxData[17]) << 8 |  ((uint32_t) UART0_valRxData[18]);
// CAN_degMot1Ang = ((uint32_t) UART0_valRxData[19]) << 8 | ((uint32_t) UART0_valRxData[20]);
// CAN_degMot2Ang=  ((uint32_t) UART0_valRxData[21]) << 8 | ((uint32_t) UART0_valRxData[22]);
// CAN_degMot3Ang = ((uint32_t) UART0_valRxData[23]) << 8 | ((uint32_t) UART0_valRxData[24]);
// CAN_degMot4Ang = ((uint32_t) UART0_valRxData[25]) << 8 | ((uint32_t) UART0_valRxData[26]);


serial::Serial ser;
ros::Time prevTime;

void write_callback(const mdart::WheelVals::ConstPtr& wheel_vals){
    uint8_t num;
    // ROS_INFO_STREAM("Writing VESC data to serial port" << VESC_data);
    // num = ser.write(VESC_data,28);
    ROS_INFO("number of bytes %d", num);
    prevTime = ros::Time::now();
}

int main (int argc, char** argv){
    ros::init(argc, argv, "serial_example_node");
    ros::NodeHandle nh;
    std::string port;
    int j = 0,i;
    char status = 0;

    ros::Subscriber write_sub = nh.subscribe("wheels", 100, write_callback);
    ros::Publisher read_pub = nh.advertise<std_msgs::String>("read", 1000);

	ser.setBaudrate(115200);
	serial::Timeout to = serial::Timeout::simpleTimeout(1000);
	ser.setTimeout(to);

    ros::Rate loop_rate(100);

    while(ros::ok()){

        ros::spinOnce();

		if(!ser.isOpen())
		{
			for(i = 0; i < 256;i ++)
			{
				status = 0;

				port = "/dev/ttyUSB"+std::to_string(i);
				ser.setPort(port);
				ROS_INFO_STREAM("Trying to open port " << port);

				try
				{
					ser.open();
				}
				catch (serial::IOException& e)
				{
					ROS_ERROR_STREAM("Failed to open port" << port);
					status = 1;
				}
				
				if(status == 0)
				{
					break;
				}

				if(i == 255)
				{
					ROS_ERROR_STREAM("No ports are available");
					return -1;
				}
			}
			ROS_INFO_STREAM("Serial Port initialized on" << port);
		}
		else
		{
			if(ser.available()){
				ROS_INFO_STREAM("Reading from serial port");
				std_msgs::String result;
				result.data = ser.read(ser.available());
				ROS_INFO_STREAM("Read: " << result.data);

				read_pub.publish(result);
			}

			ros::Time currTime = ros::Time::now();
			ros::Duration diff= currTime-prevTime;
			if(diff.toSec() > 1)
			{
				// uint8_t VESC_data[28]={0xA0,0x1A,0x00,0x00,0x00,0x27,0x10,0x00,0x00,0x27,0x10,
				// 	0x00,0x00,0x27,0x10,0x00,0x00,0x27,0x10,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0xBA};
				uint8_t VESC_data[28]={0xA0,0x1A,0x03,0x00,0x01,0x86,0xA0,0x00,0x01,0x86,0xA0,
				 	0x00,0x01,0x86,0xA0,0x00,0x01,0x86,0xA0,0x03,0xE8,0x03,0xE8,0x03,0xE8,0x03,0xE8,0xB9};
				ROS_INFO_STREAM("Update delayed for more than 2 secs. Perform evasive action"); 	
    			ROS_INFO_STREAM("Writing failsafe data to serial port" << VESC_data);
    			ser.write(VESC_data,28);
    			prevTime = currTime;
			}
		}
		loop_rate.sleep();
    }
}

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