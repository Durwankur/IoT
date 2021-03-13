

void setup() {
Serial.begin(9600);
pinMode(2,INPUT);
  
  // put your setup code here, to run once:
}
int count=0;
int sensor=0;
void loop() {
  // put your main code here, to run repeatedly:

 sensor=!digitalRead(2);
if(sensor==1)
{
  delay(10);
while(sensor==1)
{
  sensor=!digitalRead(2);
  
}
count++;
  Serial.println(count);
  }

}
