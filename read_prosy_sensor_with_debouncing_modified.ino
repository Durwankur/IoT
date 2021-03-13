void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);

}

int count =0;

void loop() 
{
  if(digitalRead(2)==0)
  {
    delay(100);
       if(digitalRead(2)==0)
          {
          while(digitalRead(2)==0);   
          count++;
          Serial.println(count);
          if(count%3==0){
            digitalWrite(13,HIGH);
            delay(2000);
            digitalWrite(13,LOW);
              
          }
          }         
  }   }
