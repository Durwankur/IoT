void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println(analogRead(A0));
delay(1000);
}
