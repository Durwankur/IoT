void setup() {
  // put your setup code here, to run once:
    pinMode(2, INPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    Serial.begin(9600);
}
int sensor=0;
void loop() {
  // put your main code here, to run repeatedly:
sensor=!digitalRead(2);
if(sensor == 1){
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  Serial.println("Clockwise");
} 
else
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  Serial.println("Anti Clockwise");
}
/*
else if(sensor==0)
{
    digitalWrite(4,HIGH);
    digitalWrite(3,LOW);
    delay(2000);
   
  } */

}
