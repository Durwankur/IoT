void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);

}

int count =0;

void loop() 
{
  if(digitalRead(2)==0)
  {
       if(digitalRead(2)==0)
          {
          while(digitalRead(2)==0);   
          count++;
          Serial.println(count);
          }         
  }   
}
