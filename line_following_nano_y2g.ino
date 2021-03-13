

#define LMF  3
#define LMR  4
#define RMF  5
#define RMR  6

#define SL  A1
#define SM  A2
#define SR  A3

int thresh = 0;

void setup() {

Serial.begin(9600);
pinMode(2,INPUT);

pinMode(SL,INPUT);
pinMode(SM,INPUT);
pinMode(SR,INPUT);
  
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);

digitalWrite(LMF,LOW);
digitalWrite(LMR,LOW);
digitalWrite(RMF,LOW);
digitalWrite(RMR,LOW);

motor_forward();
delay(2000);
motor_reverse();
delay(2000);
motor_left();
delay(2000);
motor_right();
delay(2000);
motor_stop();

wait_for_sens_count(4);
int min_val = (analogRead(SL)+analogRead(SM)+analogRead(SR))/3;
Serial.print("minval:");Serial.println(min_val);

wait_for_sens_count(4);
int max_val = (analogRead(SL)+analogRead(SM)+analogRead(SR))/3;
Serial.print("maxval:");Serial.println(max_val);

thresh = (min_val + max_val)/2;

wait_for_sens_count(4);
Serial.println("OK_begin");

thresh =500;
}


void loop(){
  if ((analogRead(SL)<thresh) && (analogRead(SM)>thresh) && (analogRead(SR)<thresh))         // if middle sensors on white and rest on black
     motor_forward();  // drive motors fwd
  else if ((analogRead(SL>thresh)) && (analogRead(SM)>thresh) && (analogRead(SR)<thresh))    
     motor_left();  // drive motors to turn Left
  else if ((analogRead(SL)>thresh) && (analogRead(SM)<thresh) && (analogRead(SR)<thresh))    
     motor_left();  // drive motors to turn Left
  else if ((analogRead(SL)<thresh) && (analogRead(SM)>thresh) && (analogRead(SR)>thresh))   
     motor_right();  // drive motors to turn Right
  else if ((analogRead(SL)<thresh) && (analogRead(SM)<thresh) && (analogRead(SR)>thresh))  
     motor_right();  // drive motors to turn Right

  
  
}


void motor_forward()
{
digitalWrite(LMF,HIGH);
digitalWrite(LMR,LOW);
digitalWrite(RMF,HIGH);
digitalWrite(RMR,LOW);
}

void motor_reverse()
{
digitalWrite(LMF,LOW);
digitalWrite(LMR,HIGH);
digitalWrite(RMF,LOW);
digitalWrite(RMR,HIGH);
}


void motor_right()
{
digitalWrite(LMF,LOW);
digitalWrite(LMR,LOW);
digitalWrite(RMF,HIGH);
digitalWrite(RMR,LOW);
}

void motor_left()
{
digitalWrite(LMF,HIGH);
digitalWrite(LMR,LOW);
digitalWrite(RMF,LOW);
digitalWrite(RMR,LOW);
}


void motor_stop()
{
digitalWrite(LMF,LOW);
digitalWrite(LMR,LOW);
digitalWrite(RMF,LOW);
digitalWrite(RMR,LOW);
}


void wait_for_sens_count(int count_val)
{

    int count = 0;
    while(count<count_val)
    {
      if(digitalRead(2)==0)
      {
           delay(40);
           if(digitalRead(2)==0)
              {
              while(digitalRead(2)==0);   
              count++;
              Serial.println(count);
              }         
           
      }   
    }
}
