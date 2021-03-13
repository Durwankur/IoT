void setup() {
  // put your setup code here, to run once:
     pinMode(2,OUTPUT);
     pinMode(3,OUTPUT);     

     digitalWrite(2,LOW);
     digitalWrite(3,LOW);     
}

void loop() {
  // put your main code here, to run repeatedly:
     digitalWrite(2,HIGH);
     digitalWrite(3,LOW);
     delay(2000);

     digitalWrite(2,LOW);
     digitalWrite(3,HIGH);
     delay(2000);
}          
