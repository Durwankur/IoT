void setup() {
  pinMode(9,OUTPUT);
  pinMode(A0, INPUT);


}

int speed_val = 0;

void loop(){
  
speed_val = map(analogRead(A0),0,1023,0,255);  
analogWrite(9,speed_val);
}
