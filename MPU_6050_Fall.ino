
/*
        Y2g
--The output scale for any setting is [-32768, +32767] for each of the six axes.
--he default setting in the I2Cdevlib class is +/- 2g for the accel and +/- 250 deg/sec for the gyro.        
--Z accel axis should read 1g, which is +16384 at a sensitivity of 2g

MPU-6050      ArduinoMega
VCC           5V            --- MPU has on-board 5V to 3.3V regulator (4A2D)
GND           GND
SCL           SCL(D21) (nano A5)     ---for wire.h library
SDA           SDA(D20)  (nano A4)     ---for wire.h library
XDA           NC
XCL           NC
AD0           GND           ---To get address 68h
INT           NC

Buzzer        ArduinoMega
Buzzer+       D2
Buzzer-       GND 
*/

#include<Wire.h>


const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
float AcX_f,AcY_f,AcZ_f;
void setup(){
  pinMode(13,OUTPUT);     //LED13 to indicate Fall
  digitalWrite(13,LOW);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);
}

float total_G =0;

float total_G_FIFO[4];

int  i=0;

void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print((float)AcX/16384);
  Serial.print(" | AcY = "); Serial.print((float)AcY/16384);
  Serial.print(" | AcZ = "); Serial.print((float)AcZ/16384);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.print(GyZ);

  AcX_f = (float)AcX/16384;
  AcY_f = (float)AcY/16384;
  AcZ_f = (float)AcZ/16384;
  total_G = sqrt(AcX_f*AcX_f+AcY_f*AcY_f+AcZ_f*AcZ_f);
  Serial.print(" | TG = "); Serial.println(total_G);  

  total_G_FIFO[3] = total_G_FIFO[2];
  total_G_FIFO[2] = total_G_FIFO[1];
  total_G_FIFO[1] = total_G_FIFO[0];
  total_G_FIFO[0] = total_G;

  total_G = ((total_G_FIFO[3]-1)+(total_G_FIFO[2]-1)+(total_G_FIFO[1]-1)+(total_G_FIFO[0]-1))/4;
    
  if(total_G>1.5)
    digitalWrite(13,HIGH);
  else  
    digitalWrite(13,LOW);
  delay(10);
}
