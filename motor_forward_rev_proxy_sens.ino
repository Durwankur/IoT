void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

digitalWrite(3,HIGH);
digitalWrite(4,LOW);
delay(3000);
digitalWrite(4,HIGH);
digitalWrite(3,LOW);
delay(3000);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
}


void loop() 
{
wait_for_sens_count(3);
digitalWrite(3,HIGH);
digitalWrite(4,LOW);
wait_for_sens_count(3);
digitalWrite(3,LOW);
digitalWrite(4,HIGH);
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
