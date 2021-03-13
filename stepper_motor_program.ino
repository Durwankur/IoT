


void setup() {
  // put your setup code here, to run once:
     pinMode(2,OUTPUT);
     pinMode(3,OUTPUT);     
     pinMode(4,OUTPUT);
     pinMode(5,OUTPUT);     

     digitalWrite(2,LOW);
     digitalWrite(3,LOW);     
     digitalWrite(4,LOW);
     digitalWrite(5,LOW);     

}

void loop() {
  // put your main code here, to run repeatedly:
  
  stepper(1,0,0,1);     //0      Dual   phase
  stepper(1,1,0,0);     //90     Dual   phase
  stepper(0,1,1,0);     //180    Dual   phase
  stepper(0,0,1,1);     //270    Dual   phase    
}

void  stepper(boolean C1,boolean C2,boolean C3,boolean C4)
{
     digitalWrite(2,C1);
     digitalWrite(3,C2);
     digitalWrite(4,C3);
     digitalWrite(5,C4);
     delay(2000);  
}          
