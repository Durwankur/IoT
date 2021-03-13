void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(2, INPUT);

}

int count =0;

void loop() {
  // put your main code here, to run repeatedly:

if(digitalRead(2)==0)
{
  count++;
  Serial.println(count);
}

}
