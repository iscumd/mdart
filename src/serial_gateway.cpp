#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <mdart/WheelVals.h>

#define RPM_MAX				10000
#define DRIVE_CURRENT_MAX	80
#define DUTY_CYCYLE_MAX		1
#define BRAKE_CURRENT_MAX	80

#define SERVO_MUL_FAC		1000

// (UART0_valRxData[2])
// case 0: DutyCycle(000) data/100000
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

    uint8_t ptr = 0, mode = 0,chkSum= 0,i,valWhl,VESC_data[29] = {0};
    uint32_t angFrL,angFrR,angReL,angReR,valWhlFrL, valWhlFrR,valWhlReL,valWhlReR,mulFac = 0;

    if(wheel_vals->angleFrontLeft < 1){
    	angFrL = uint16_t(wheel_vals->angleFrontLeft*SERVO_MUL_FAC);
    }
    else{
		angFrL = .5 * SERVO_MUL_FAC;
    }

    if(wheel_vals->angleFrontRight < 1){
    	angFrR = uint16_t(wheel_vals->angleFrontRight*SERVO_MUL_FAC);
    }
    else{
		angFrR = .5 * SERVO_MUL_FAC;
    }
    
    if(wheel_vals->angleRearLeft < 1){
    	angReL = uint16_t(wheel_vals->angleRearLeft*SERVO_MUL_FAC);
    }
    else{
		angReL = .5 * SERVO_MUL_FAC;
    }
    
    if(wheel_vals->angleRearRight < 1){
    	angReR = uint16_t(wheel_vals->angleRearRight*SERVO_MUL_FAC);
    }
    else{
		angReR = .5 * SERVO_MUL_FAC;
    }

    VESC_data[ptr++] = 0xA0;
    VESC_data[ptr++] = 0x1A;
    VESC_data[ptr++] = mode;

	valWhlFrL = wheel_vals->speedFrontLeft;
	valWhlFrR = wheel_vals->speedFrontRight;
	valWhlReL = wheel_vals->speedRearLeft;
	valWhlReR = wheel_vals->speedRearRight;    

    switch(mode){
    	case 0:{
    		// DutyCycle Mode
    		mulFac = 100000;

    		if((valWhlFrL > 1)||(valWhlFrR > 1)||(valWhlReL > 1)||(valWhlReR > 1)){
				valWhlFrL = 0;
	    		valWhlFrR = 0;
	    		valWhlReL = 0;
	    		valWhlReR = 0;
    		}
		}
    	break;

    	case 2:{
    		// RPM Mode
    		mulFac = 1;

    		if((valWhlFrL > RPM_MAX)||(valWhlFrR > RPM_MAX)||(valWhlReL > RPM_MAX)||(valWhlReR > RPM_MAX)){
				valWhlFrL = 0;
	    		valWhlFrR = 0;
	    		valWhlReL = 0;
	    		valWhlReR = 0;
    		}
    	}
    	break;

    	case 1:
    	default:{
    		// Current Mode for Motion and Braking 
    		mulFac = 1000;

    		if((valWhlFrL > DRIVE_CURRENT_MAX)||(valWhlFrR > DRIVE_CURRENT_MAX)||(valWhlReL > DRIVE_CURRENT_MAX)||(valWhlReR > DRIVE_CURRENT_MAX)){
				valWhlFrL = 0;
	    		valWhlFrR = 0;
	    		valWhlReL = 0;
	    		valWhlReR = 0;
    		}    		
    	}
    }

	// Updating the BLDC motor values
    valWhl = valWhlFrL *mulFac;
    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
    VESC_data[ptr++] = (uint8_t)(valWhl);
    
    valWhl = valWhlFrR *mulFac;
    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
    VESC_data[ptr++] = (uint8_t)(valWhl);
    
    valWhl = valWhlReR *mulFac;
   	VESC_data[ptr++] = (uint8_t)(valWhl >>24);
    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
    VESC_data[ptr++] = (uint8_t)(valWhl);
    
    valWhl = valWhlReL*mulFac;
    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
    VESC_data[ptr++] = (uint8_t)(valWhl);

    // Updating the servo motor values
    VESC_data[ptr++] = (uint8_t)(angFrL >>8);
    VESC_data[ptr++] = (uint8_t)(angFrL);
    
    VESC_data[ptr++] = (uint8_t)(angFrR >>8);
    VESC_data[ptr++] = (uint8_t)(angFrR);
    
    VESC_data[ptr++] = (uint8_t)(angReR >>8);
    VESC_data[ptr++] = (uint8_t)(angReR);
    
    VESC_data[ptr++] = (uint8_t)(angReL >>8);
    VESC_data[ptr++] = (uint8_t)(angReL);     

    for(i = 0; i<27;i++){
    	chkSum = chkSum ^ VESC_data[i];
    }
    VESC_data[ptr] = (uint8_t)(chkSum);

    ROS_INFO_STREAM("Writing VESC data to serial port" << VESC_data);
    ptr = ser.write(VESC_data,28);
    ROS_INFO("number of bytes %d", ptr);
    prevTime = ros::Time::now();
}

int main (int argc, char** argv){
    ros::init(argc, argv, "serial_gateway_node");
    ros::NodeHandle nh;
    std::string port;
    int i;
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
				port = "/dev/ttyUSB"+std::to_string(i);
				ser.setPort(port);
				ROS_INFO_STREAM("Trying to open port " << port);

				try{
					status = 0;
					ser.open();
				}
				catch (serial::IOException& e){
					ROS_ERROR_STREAM("Failed to open port" << port);
					status = 1;
				}
		
				if(status == 0){
					ROS_INFO_STREAM("Serial Port initialized on" << port);
					break;
				}

				if(i == 255){
					ROS_ERROR_STREAM("No ports are available. Gateway function disabled");
					while(1);
				}
			}
		}
		else{
			if(ser.available()){
				ROS_INFO_STREAM("Reading from serial port");
				std_msgs::String result;
				result.data = ser.read(ser.available());
				ROS_INFO_STREAM("Read: " << result.data);

				read_pub.publish(result);
			}

			ros::Time currTime = ros::Time::now();
			ros::Duration diff= currTime-prevTime;

			if(diff.toSec() > 1){
				uint8_t ptr = 0 ,chkSum=0,VESC_data[28]={0};
				uint16_t mulFac = 1000;
				uint32_t angFrL,angFrR,angReL,angReR,valWhl;
				float valWhlFrL,valWhlFrR,valWhlReL,valWhlReR;

				valWhlFrL = BRAKE_CURRENT_MAX;
				valWhlFrR = BRAKE_CURRENT_MAX;
				valWhlReL = BRAKE_CURRENT_MAX;
				valWhlReR = BRAKE_CURRENT_MAX;

				angFrL = 0.99 * SERVO_MUL_FAC;
				angFrR = 0.00 * SERVO_MUL_FAC;
				angReL = 0.99 * SERVO_MUL_FAC;
				angReR = 0.00 * SERVO_MUL_FAC;

	    		VESC_data[ptr++] = 0xA0;
	    		VESC_data[ptr++] = 0x1A;
	    		VESC_data[ptr++] = 0x03;

				// Updating the BLDC motor values
			    valWhl = (uint32_t)(valWhlFrL *mulFac);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
			    VESC_data[ptr++] = (uint8_t)(valWhl);
			    
			    valWhl = (uint32_t)(valWhlFrR *mulFac);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
			    VESC_data[ptr++] = (uint8_t)(valWhl);
			    
			    valWhl = (uint32_t)(valWhlReR *mulFac);
			   	VESC_data[ptr++] = (uint8_t)(valWhl >>24);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
			    VESC_data[ptr++] = (uint8_t)(valWhl);
			    
			    valWhl = (uint32_t)(valWhlReL*mulFac);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>24);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>16);
			    VESC_data[ptr++] = (uint8_t)(valWhl >>8);
			    VESC_data[ptr++] = (uint8_t)(valWhl);

			    // Updating the servo motor values
			    VESC_data[ptr++] = (uint8_t)(angFrL >>8);
			    VESC_data[ptr++] = (uint8_t)(angFrL);
			    
			    VESC_data[ptr++] = (uint8_t)(angFrR >>8);
			    VESC_data[ptr++] = (uint8_t)(angFrR);
			    
			    VESC_data[ptr++] = (uint8_t)(angReR >>8);
			    VESC_data[ptr++] = (uint8_t)(angReR);
			    
			    VESC_data[ptr++] = (uint8_t)(angReL >>8);
			    VESC_data[ptr++] = (uint8_t)(angReL);

			    for(i = 0; i<27;i++){
			    	chkSum = chkSum ^ VESC_data[i];
			    }
			    VESC_data[ptr] = (uint8_t)(chkSum);

				ROS_INFO_STREAM("Update delayed for more than 1 secs. Perform evasive action"); 	

				if(diff.toSec() > 1)
				{
	    			ROS_INFO_STREAM("Writing failsafe data to serial port" << VESC_data);
	    			ser.write(VESC_data,28);
	    			prevTime = currTime;
				}
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