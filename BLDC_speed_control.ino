#include <Servo.h>

Servo my_BLDC; 
void setup() {

  my_BLDC.attach(9);  
  my_BLDC.writeMicroseconds(1000);
  delay(2000);  
}
int speed_val=0;
void loop() {
  for(speed_val = 1000;speed_val<=1500;speed_val = speed_val+100)
  {
  my_BLDC.writeMicroseconds(speed_val);
  delay(2000);
  }

  for(speed_val = 1500;speed_val>=1000;speed_val = speed_val-100)
  {
  my_BLDC.writeMicroseconds(speed_val);  
  delay(2000);
  }
}
