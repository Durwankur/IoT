void setup() {
  // put your setup code here, to run once:
  pinMode(3,OUTPUT);      
       
}

void loop() {
  // put your main code here, to run repeatedly:

     analogWrite(3,127);      //0   degree
     delay(2000);
      
     analogWrite(3,191);      //90  degree
     delay(2000);

     analogWrite(3,250);      //180 degree
     delay(2000);

}
