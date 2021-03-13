
# define Sens_cut  2    // ip forward obstacle sensor

// Left Motor Controls
# define Lp  3    // ip B
# define Ln  4    // ip A
# define PWM_L  9    
// Right Motor Controls
# define Rp  5    // ip A
# define Rn  6   // ip B
# define PWM_R  10
// Grid Sensors
# define ELs  A0
# define Ls   A1
# define Ms   A2
# define Rs   A3
# define ERs  A4

int Kp=5,Ki=0.1,Kd=1;

int Max_ELs=0,Max_Ls=0,Max_Ms=0,Max_Rs=0,Max_ERs=0;
int Min_ELs=800,Min_Ls=800,Min_Ms=800,Min_Rs=800,Min_ERs=800;
int Sens_ELs=0,Sens_Ls=0,Sens_Ms=0,Sens_Rs=0,Sens_ERs=0;
int i = 0;


void setup ()
{  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (Lp, OUTPUT);
  pinMode (Ln, OUTPUT);
  pinMode (PWM_L, OUTPUT);
  pinMode (Rp, OUTPUT);
  pinMode (Rn, OUTPUT);
  pinMode (PWM_R, OUTPUT);

  pinMode (Sens_cut, INPUT);      //for forward obstacle sensor
  digitalWrite (Sens_cut,LOW);


  pinMode (A4, INPUT);  
  pinMode (A3, INPUT);
  pinMode (A2, INPUT);
  pinMode (A1, INPUT);
  pinMode (A0, INPUT);
  

//ser pull down
  digitalWrite (A4,LOW);
  digitalWrite (A3,LOW);
  digitalWrite (A2,LOW);
  digitalWrite (A1,LOW);
  digitalWrite (A0,LOW);


/*
  digitalWrite (PWM_L,HIGH);
  digitalWrite (PWM_R,HIGH);
 motorfwd();
 delay(4000);
 motorleft();
 delay(4000);
 motorright();
 delay(4000);
 motorstop();
 while(1);
*/
sensor_calib();
sensor_calib();
sensor_calib();


 int start_flag = 0;
    while(start_flag<3)
    {
    while(digitalRead(Sens_cut)==1);
        while(digitalRead(Sens_cut)==0);
          start_flag++;
    }     
Serial.println("ok4");
}

void loop()
{
 motorfwd();
 pid_control();
  
// obstacle_detect();

}

void obstacle_detect()
{
     if(digitalRead(Sens_cut)==1)
           delay(100);
              if((digitalRead(Sens_cut)==1))
                 while((digitalRead(Sens_cut)==1))
                        motorstop();
}


int sens_EL=0,sens_L=0,sens_M=0,sens_R=0,sens_ER=0;

int error_sens_EL=0,error_sens_L=0,error_sens_M=0,error_sens_R=0,error_sens_ER=0;

int last_error_sens_EL=0,last_error_sens_L=0,last_error_sens_M=0,last_error_sens_R=0,last_error_sens_ER=0;

int L_motor_PWM =0,R_motor_PWM=0;

float left_error=0,right_error=0;
float prev_left_error=0,prev_right_error=0;
float final_left_error=0,final_right_error=0;
float acc_left_error=0,acc_right_error=0;


void pid_control()
{
/*here when sensor detect white line it reads max value around 900-1023 (logic-1)*/
/*  other wise sensor reads min value for Dark, around 0-200 (Logic-0)*/
/*The sensor values are mapped to get uniform range (Normalization),
        this is done to make further calculations range independant*/
        
sens_EL = map(analogRead(A0),Max_ELs,Min_ELs,100,0);    // left sensor
sens_L = map(analogRead(A1),Max_Ls,Min_Ls,100,0);    // left sensor
sens_M = map(analogRead(A2),Max_Ms,Min_Ms,100,0);    // middle sensor
sens_R = map(analogRead(A3),Max_Rs,Min_Rs,100,0);    // right sensor
sens_ER = map(analogRead(A4),Max_ERs,Min_ERs,100,0);    // right sensor

/*In case Sensor value maps beyond range 0-100 then make it 0 or 100*/
if(sens_EL<0)sens_EL=0;if(sens_EL>100)sens_EL=100;
if(sens_L<0)sens_L=0;if(sens_L>100)sens_L=100;
if(sens_M<0)sens_M=0;if(sens_M>100)sens_M=100;
if(sens_R<0)sens_R=0;if(sens_R>100)sens_R=100;
if(sens_ER<0)sens_ER=0;if(sens_ER>100)sens_ER=100;

/*evaluate the errot*/ 
/*error will be zero if EL=0,L=0,M=1,R=0,ER=0
Subtract set points from sensed values, so as to ger +ve error*/

error_sens_EL = (sens_EL-0);
error_sens_L = (sens_L-0);
error_sens_M = (sens_M-100);
error_sens_R = (sens_R-0);
error_sens_ER = (sens_ER-0);


/************** to remember the last known best guess********************/
if((error_sens_L<25)&&(error_sens_M>25)&&(error_sens_R<25))
    { 
    error_sens_EL=last_error_sens_EL;
    error_sens_L=last_error_sens_L;
    error_sens_M=last_error_sens_M;
    error_sens_R=last_error_sens_R;
    error_sens_ER=last_error_sens_ER;
    }
last_error_sens_EL =error_sens_EL;
last_error_sens_L =error_sens_L;
last_error_sens_M =error_sens_M;
last_error_sens_R =error_sens_R;
last_error_sens_ER =error_sens_ER;
/*******************************************************************************/

/*THE ERRORS ARE GVEN WEIGHTS AS PER THEIR POSITIONS AND THEN AVERAGED*/
left_error = ((4*error_sens_EL +1*error_sens_L + error_sens_M)/6);
right_error =((4*error_sens_ER +1*error_sens_R + error_sens_M)/6);

/*FUNDAMENTAL PID EQUATION*/
if(left_error>25)       {final_left_error = Kp*left_error-Kd*(left_error-prev_left_error)+Ki*acc_left_error;}
else if (right_error>25){final_right_error = Kp*right_error-Kd*(right_error-prev_right_error)+Ki*acc_right_error;}
else                    {final_left_error=0;final_right_error=0;}

      //here correction is applied to the base Speed of 255 
      L_motor_PWM = 255 - final_left_error;   if(L_motor_PWM<0)L_motor_PWM=0;
      R_motor_PWM = 255 - final_right_error;  if(R_motor_PWM<0)R_motor_PWM=0;
          analogWrite(PWM_L,L_motor_PWM);  //update motor speed
          analogWrite(PWM_R,R_motor_PWM);  //update motor speed

acc_left_error += left_error;
acc_right_error+= right_error;

prev_left_error = left_error;
prev_right_error = right_error;


//display_sens_vals();

}



void display_sens_vals()
{
Serial.print(error_sens_EL); 
Serial.print('\t');
Serial.print(error_sens_L); 
Serial.print('\t');
Serial.print(error_sens_M); 
Serial.print('\t');
Serial.print(error_sens_R); 
Serial.print('\t');
Serial.print(error_sens_ER); 
Serial.print('\n');

Serial.print((int)left_error);
Serial.print('\t');
Serial.print((int)right_error);
Serial.print('\n');


Serial.print(L_motor_PWM);
Serial.print('\t');
Serial.print(R_motor_PWM);
Serial.print('\n');


delay(2000);

}

void motorfwd()
{
                 // lft FORWARD
      digitalWrite (Ln,LOW);
      digitalWrite (Lp,HIGH);

                  // rgt FORWARD
      digitalWrite (Rn,LOW);
      digitalWrite (Rp,HIGH); 


}


void motorleft()
{
                 // lft FORWARD
      digitalWrite (Ln,HIGH);
      digitalWrite (Lp,LOW);

                  // rgt FORWARD
      digitalWrite (Rn,LOW);
      digitalWrite (Rp,HIGH); 


}



void motorright()
{
                 // lft FORWARD
      digitalWrite (Ln,LOW);
      digitalWrite (Lp,HIGH);

                  // rgt FORWARD
      digitalWrite (Rn,HIGH);
      digitalWrite (Rp,LOW); 


}

void motorstop()
{
                 // lft FORWARD
      digitalWrite (Ln,LOW);
      digitalWrite (Lp,LOW);

                  // rgt FORWARD
      digitalWrite (Rn,LOW);
      digitalWrite (Rp,LOW); 


}

void sensor_calib()
{
  
    int start_flag = 0;
    while(start_flag<3)
    {
    while(digitalRead(Sens_cut)==1);
        while(digitalRead(Sens_cut)==0);
          start_flag++;
    }     
    Serial.println("ok1");
  
  
  analogWrite(PWM_L,255);
  analogWrite(PWM_R,255);

   i=0; 
   motorleft();
        do
       {
          Sens_ELs=analogRead(A0);
          if(Sens_ELs>Max_ELs)Max_ELs=Sens_ELs;          if(Sens_ELs<Min_ELs)Min_ELs=Sens_ELs;
          Sens_Ls=analogRead(A1);
          if(Sens_Ls>Max_Ls)Max_Ls=Sens_Ls;              if(Sens_Ls<Min_Ls)Min_Ls=Sens_Ls;
          Sens_Ms=analogRead(A2);
          if(Sens_Ms>Max_Ms)Max_Ms=Sens_Ms;              if(Sens_Ms<Min_Ms)Min_Ms=Sens_Ms;
          Sens_Rs=analogRead(A3);
          if(Sens_Rs>Max_Rs)Max_Rs=Sens_Rs;              if(Sens_Rs<Min_Rs)Min_Rs=Sens_Rs;
          Sens_ERs=analogRead(A4);
          if(Sens_ERs>Max_ERs)Max_ERs=Sens_ERs;          if(Sens_ERs<Min_ERs)Min_ERs=Sens_ERs;
          i++;
//          delay(2);
      } while(i<3000);

motorstop();
delay(50);

  i=0;
  motorright();
        do
       {
          Sens_ELs=analogRead(A0);
          if(Sens_ELs>Max_ELs)Max_ELs=Sens_ELs;          if(Sens_ELs<Min_ELs)Min_ELs=Sens_ELs;
          Sens_Ls=analogRead(A1);
          if(Sens_Ls>Max_Ls)Max_Ls=Sens_Ls;              if(Sens_Ls<Min_Ls)Min_Ls=Sens_Ls;
          Sens_Ms=analogRead(A2);
          if(Sens_Ms>Max_Ms)Max_Ms=Sens_Ms;              if(Sens_Ms<Min_Ms)Min_Ms=Sens_Ms;
          Sens_Rs=analogRead(A3);
          if(Sens_Rs>Max_Rs)Max_Rs=Sens_Rs;              if(Sens_Rs<Min_Rs)Min_Rs=Sens_Rs;
          Sens_ERs=analogRead(A4);
          if(Sens_ERs>Max_ERs)Max_ERs=Sens_ERs;          if(Sens_ERs<Min_ERs)Min_ERs=Sens_ERs;
          i++;
//          delay(2);  
      } while(i<6000);

motorstop();
delay(50);

 i=0;
 motorleft();
        do
       {
          Sens_ELs=analogRead(A0);
          if(Sens_ELs>Max_ELs)Max_ELs=Sens_ELs;          if(Sens_ELs<Min_ELs)Min_ELs=Sens_ELs;
          Sens_Ls=analogRead(A1);
          if(Sens_Ls>Max_Ls)Max_Ls=Sens_Ls;              if(Sens_Ls<Min_Ls)Min_Ls=Sens_Ls;
          Sens_Ms=analogRead(A2);
          if(Sens_Ms>Max_Ms)Max_Ms=Sens_Ms;              if(Sens_Ms<Min_Ms)Min_Ms=Sens_Ms;
          Sens_Rs=analogRead(A3);
          if(Sens_Rs>Max_Rs)Max_Rs=Sens_Rs;              if(Sens_Rs<Min_Rs)Min_Rs=Sens_Rs;
          Sens_ERs=analogRead(A4);
          if(Sens_ERs>Max_ERs)Max_ERs=Sens_ERs;          if(Sens_ERs<Min_ERs)Min_ERs=Sens_ERs;
          i++;
//          delay(2);  
      } while(i<3000);

motorstop();
delay(50);

Serial.print(Max_ELs);
Serial.print('\t');
Serial.print(Max_Ls);
Serial.print('\t');
Serial.print(Max_Ms);
Serial.print('\t');
Serial.print(Max_Rs);
Serial.print('\t');
Serial.print(Max_ERs);
Serial.print('\n');

Serial.print(Min_ELs);
Serial.print('\t');
Serial.print(Min_Ls);
Serial.print('\t');
Serial.print(Min_Ms);
Serial.print('\t');
Serial.print(Min_Rs);
Serial.print('\t');
Serial.print(Min_ERs);
Serial.print('\n');


}
