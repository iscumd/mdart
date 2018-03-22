#include <stdlib.h>
#include <time.h>
#include "socket.c"
#include "ros/ros.h"
#include <ros/console.h>
#include "sensord_msgs/LaserScan.h"

int hokuyoSocket;
int hokuyoPort = 10940; // default port
char *hokuyoIP = "192.168.0.10"; // default IP address

unsigned int hokuyoData[1081];

char zbuffer[10000];
char hokuyoBuffer[10000];
char *startScanMode = "BM\n";
char *stopScanMode = "QT\n";
char *rebootCmd = "RB\nRB\n";
char *getNewDataCmd = "GD0000108000\n";
char *header = "\n"; //find this three times then data starts
char *footer = "\n\n"; //two line feeds signal end of data

#define NUM_HEADER_CHARS 24
#define MAX_PTS 1081


void initHokuyo() {
	shutdown(hokuyoSocket, 2); // test comment 1
	closesocket(hokuyoSocket);
	hokuyoSocket = initSocket(hokuyoIP, hokuyoPort);              //socket.c
	sendMsg(hokuyoSocket, startScanMode);
	getMsg(hokuyoSocket, hokuyoBuffer);
	ROS_DEBUG("Hokuyo Opened");
}

void shutdownHokuyo() {
	sendMsg(hokuyoSocket, stopScanMode);
	sendMsg(hokuyoSocket, rebootCmd);
	sendMsg(hokuyoSocket, rebootCmd);
	shutdown(hokuyoSocket, 2);
	closesocket(hokuyoSocket);
}


void fillData() {
	long mag = 0;
	int numpts = 0;
	int j = 0;
	int blockCount = 0;

	char *msg = strstr(zbuffer, header);//Look for header string. Move Pointer to begging of Header
	if (msg == NULL || *msg == '\0') return;//don't update if header wasn't found
	msg += strlen(header);//move past length of header.

	msg = strstr(msg, header);//Look for header string. Move Pointer to begging of Header
	if (msg == NULL || *msg == '\0') return;//don't update if header wasn't found
	msg += strlen(header);//move past length of header.

	msg = strstr(msg, header);//Look for header string. Move Pointer to begging of Header
	if (msg == NULL || *msg == '\0') return;//don't update if header wasn't found
	msg += strlen(header);//move past length of header.

	for (numpts = 0; numpts<1081; numpts++) {
		mag = 0;
		for (j = 0; j<3; j++) {
			if (blockCount == 64) {
				msg = msg + 2;
				blockCount = 0;
			}
			mag <<= 6;
			mag &= ~0x3f;
			mag |= (*msg - 0x30);

			msg++;
			blockCount++;
		}
		hokuyoData[numpts] = mag;
		if (mag<0x20)  hokuyoData[numpts] = 15000;
	}
}

void updateHokuyo() {
	int retVal = 1;
	while (retVal > 0 && retVal < 3000) {
		sendMsg(hokuyoSocket, getNewDataCmd);
		Sleep(20);
		retVal = getMsg(hokuyoSocket, hokuyoBuffer);
		memset(zbuffer, 0, 10000);
		strncat(zbuffer, hokuyoBuffer, retVal - 1);
	}
	if (retVal != -1) 
	{
		fillData();
	}
	else {
		ROS_DEBUG("\nError Getting Data\n");
		initHokuyo();
	}
}

void debugHokuyo() {
	int i = 0;
	for (i = 0; i < 1080; i++) {
		ROS_DEBUG("data[%d] = %d\n", i, hokuyoData[i]);
	}
}

int main(int argc, char **argv) 
{

	ros::init(argc, argv, "HokuyoPub");

	ros::NodeHandle node;

	/* publish ROS messages of type "LaserScan" on topic name "HokuyoScan" with a queue length of 100 */
	ros::Publisher lidar_pub = node.advertise<sensor_msgs::LaserScan>("HokuyoScan", 100);

	ros::Rate loop_rate(50);

	// Angelo Hokuyo code
	int i = 0;
	char c;
	double currTime, lastTime, myfps;
	lastTime = clock();
	initHokuyo();


	/*
	ROS_DEBUG("ROS_Debug error msg");
	ROS_INFO("ROS_INFO  error msg");
	ROS_WARN("ROS_WARN  error msg");
	ROS_ERROR("ROS_ERROR  error msg");
	ROS_FATAL("ROS_FATAL error msg");
	*/
	
	while (c != 27) {
		updateHokuyo();
		if (kbhit()) c = getch();
		else c = 0;


		if (i == 40) {
			currTime = clock() - lastTime;
			currTime /= CLOCKS_PER_SEC;

			myfps = i / currTime;
			ROS_DEBUG("%d   %.4f FPS\n", i, myfps);
			lastTime = currTime;
			i = 0;
		}
		else {
			i++;
		}
		debugHokuyo();
	}
	shutdownHokuyo();

	return 0;
}







int getMsg(int socket, char *msgBuf) {
	/*Try to read buffer*/
	int bytesread = recv(socket, sockBuffer, MAXBUFLEN, 0);
	//    int bytesread=recv(socket, msgBuf, MAXBUFLEN, 0);
	if (bytesread < 0) {
		ROS_ERROR("recvfrom() failed");
		return -1;
	}
	sockBuffer[bytesread] = '\0';

	strcpy(msgBuf, sockBuffer);
	return bytesread;
}

int sendMsg(int socket, char *msg) {
	/*Request latest data*/
	int sendbytes = strlen(msg);
	if (send(socket, msg, sendbytes, 0) != sendbytes) {
		ROS_ERROR("send()  sent  a different  number  of bytes  than  expected");
		return 0;
	}
	return 1;
}

int initSocket(char *ServIP, unsigned short ServPort)
{
	struct sockaddr_in ServAddr;    /* Local address */
	int sock;
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
			ROS_ERROR("WSAStartup() failed");
			//exit(1);
		}
	}
	ROS_INFO("serving:  %s:%d\n", ServIP, ServPort);
	/* Create socket for sending/receiving datagrams */
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		ROS_ERROR("socket() failed");
		//exit(1);
	}
	/* Construct local address structure */
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP);
	ServAddr.sin_port = htons(ServPort);

	/*  Establish  the  connection  to  the  echo  server  */
	if (connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) < 0) {
		ROS_ERROR(" connect ()  failed");
	}
	else {
		return sock;
	}
	return 0;
}
