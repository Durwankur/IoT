// Introduction to Serial print

// Serial.print    https://www.arduino.cc/en/Serial/Println
// Serial.println  https://www.arduino.cc/en/Serial/Print


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}


void loop() {
  // put your main code here, to run repeatedly:
int count = 0;
int N = 73;
//Serial.print(73);
Serial.print("Hello World:");
Serial.print(N);
Serial.print('\n');
count=count+1;
Serial.println(count);
delay(1000);
}
