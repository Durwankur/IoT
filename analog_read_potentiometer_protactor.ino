void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

}

int angle_val = 0;

void loop() {
  // put your main code here, to run repeatedly:

angle_val = map(analogRead(A0),0,1024,0,180);

Serial.print("Angle:");
Serial.println(angle_val);
delay(1000);
}
