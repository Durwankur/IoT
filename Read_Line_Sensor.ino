int sensorValue0 = 0;  // variable to store the value coming from the sensor
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor

void setup() {
  // put your setup code here, to run once:      
      Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue0 = analogRead(A0);
  sensorValue1 = analogRead(A1);
  sensorValue2 = analogRead(A2);
  sensorValue3 = analogRead(A3);
  sensorValue4 = analogRead(A4);

  
  Serial.print("A0 = ");Serial.print(sensorValue0); 
  Serial.print("A1 = ");Serial.print(sensorValue1); 
  Serial.print("A2 = ");Serial.print(sensorValue2); 
  Serial.print("A3 = ");Serial.print(sensorValue3); 
  Serial.print("A4 = ");Serial.println(sensorValue4); 
  
delay(500);
}
