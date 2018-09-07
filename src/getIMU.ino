
#include <SPI.h>

#include <MPU9250.h>
#include <Wire.h>

//Wire.begin()
MPU9250 IMU(Wire, 0x68);
//Wire.begin();
int stat;
int laps = 0;
float ax, ay, az, gx, gy, gz;
//Will set up and configure the IMU for I2C
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
 // Wire.setSDA(18);
 // Wire.setSCL(19);
  //Wire.beginTransmission(0x68);

  stat = IMU.begin();
  Serial.begin(115200);
  while(!Serial){}

   if (stat < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(stat);
    while(1) {}
   }

}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.readSensor();

  
  ax = IMU.getAccelX_mss();
  ay = IMU.getAccelY_mss();
  az = IMU.getAccelZ_mss();

  gx = IMU.getGyroX_rads();
  gy = IMU.getGyroY_rads();
  gz = IMU.getGyroZ_rads();

  Serial.println("Ax: " + String(ax));
  Serial.println("Ay: " + String(ay));
  Serial.println("Az: " + String(az));
  Serial.println("Gx: " + String(gx));
  Serial.println("Gy: " + String(gy));
  Serial.println("Gz: " + String(gz));
  Serial.print("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");

  Serial.write(ax);
  Serial.write(ay);
  Serial.write(az);
  Serial.write(gx);
  Serial.write(gy);
  Serial.write(gz);
}

