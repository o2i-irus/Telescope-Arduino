char motor_1_dir=false;
char motor_1_run=false;

byte PWM_PIN_1 = 3;
byte PWM_PIN_2 = 4;
byte PWM_PIN_3 = 5;
byte PWM_PIN_4 = 6;
byte PWM_PIN_5 = 7;
byte PWM_PIN_6 = 8;
 
long int pwm_value_1;
long int pwm_value_2;
long int pwm_value_3;
long int pwm_value_4;
long int pwm_value_5;
long int pwm_value_6;

int minPulse = 600;
int maxPulse = 1400;
int refreshTime = 20;

//telescope motor
const int pwm = 13 ;  //initializing pin 13 as pwm
const int in_1 = 22 ;
const int in_2 = 23 ;

// Gripper Yaw motor
const int pwm_g = 12 ;  //initializing pin 13 as pwm
const int in_1_g = 34 ;
const int in_2_g = 35 ;

int pulse1=24;
int direc1=25;
int pulse2=26;
int direc2=27;
int pulse3=28;
int direc3=29;
int pulse4=30;
int direc4=31;



float c,i=1000.0;
int pos;            //commanded servo posistion, 0-180 degrees
int pulseRange;     //max pulse-min pulse
long lastPulse = 0; //recorded time (ms) of the last pulse
int centerServo;    //center servo position
int pulseWidth;     //servo pulse width

void setup() {
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(PWM_PIN_3, INPUT);
  pinMode(PWM_PIN_4, INPUT);
  pinMode(PWM_PIN_5, INPUT);
  pinMode(PWM_PIN_6, INPUT);
  
  Serial.begin(115200);

  pulseRange = maxPulse - minPulse;
  centerServo = maxPulse - ((pulseRange)/2);
  pulseWidth = centerServo;  // Give the servo a starting point (or it floats)
 
  //Motors
  pinMode(pulse1,OUTPUT);
  pinMode(direc1,OUTPUT);
  pinMode(pulse2,OUTPUT); 
  pinMode(direc2,OUTPUT);
  pinMode(pulse3,OUTPUT); 
  pinMode(direc3,OUTPUT);
  
  //Telescope
  pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
  pinMode(in_1,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_2,OUTPUT) ;

  //Gripper Yaw
  pinMode(pwm_g,OUTPUT) ;   //we have to set PWM pin as output
  pinMode(in_1_g,OUTPUT) ;  //Logic pins are also set as output
  pinMode(in_2_g,OUTPUT) ;

  //Rhino-Gripper
  pinMode(pulse4,OUTPUT);
  pinMode(direc4,OUTPUT);

}

void cw1(){
  digitalWrite(direc1,LOW);
  digitalWrite(pulse1,LOW);
}

void ccw1(){
  digitalWrite(direc1,HIGH);
  digitalWrite(pulse1,LOW);
  }

void cw2(){
  digitalWrite(direc2,LOW);
  digitalWrite(pulse2,LOW);
  }

void ccw2(){
  digitalWrite(direc2,HIGH);
  digitalWrite(pulse2,LOW);
  }

void cw3(){
  digitalWrite(direc3,LOW);
  digitalWrite(pulse3,LOW);
  }

void ccw3(){
  digitalWrite(direc3,HIGH);
  digitalWrite(pulse3,LOW);
  }

void cw4(){
  digitalWrite(direc4,LOW);
  digitalWrite(pulse4,LOW);
  }

void ccw4(){
  digitalWrite(direc4,HIGH);
  digitalWrite(pulse4,LOW);
  }


float x1=0;                       //X1 IS COUNTER FOR MOTOR 1//
float x2=0;                       //X2 IS COUNTER FOR MOTOR 2//
float x3=0;                       //X3 IS COUNTER FOR MOTOR 31//
float b1=0;                       //B1 IS COUNTER FOR MOTOR 1//
float b2=0;                       //B2 IS COUNTER FOR MOTOR 2//
float b3=0;                       //B3 IS COUNTER FOR MOTOR 3//
float z;

void motor1(float x1, char dir_flag)
{ 
  int a=0;        // a is just for a loop//
  i=1000;
  a=a+1;
  // HERE OUR MOTOR1 WILL RUN //
/*  while(a<(x1/3)) // We are dividing no of counts in three parts//
  {
     //cw1();
     digitalWrite(pulse1,HIGH);
     delayMicroseconds(i);
     digitalWrite(pulse1,LOW);    //SPEEED INCREASES UPTO 0.2 ms//
     delayMicroseconds(i);
     a=a+1; 
     i=i-(1200/x1);
     if(i<200)
     {
       i=200;
     }                                                 
   }
*/   
     if(dir_flag==false){
        digitalWrite(direc1,LOW);
      }else{
        digitalWrite(direc1,HIGH);
      }
     
     digitalWrite(pulse1,HIGH);
     delayMicroseconds(i);
     digitalWrite(pulse1,LOW);       //SPEED REMAINS CONSTANT i.e. 0.2 ms//
     delayMicroseconds(i);
     //  Serial.println(i);
}
/*
// HERE OUR MOTOR 2 WILL RUN //
void motor2(float b1)
{ 
   int a=0;  // a is just for a loop//
   // HERE OUR MOTOR2 WILL RUN  CLOCKWISE//
   while(a<(b1/3))                   // We are dividing no of counts in three parts//
   {
      //cw2();
      digitalWrite(pulse2,HIGH);
      delayMicroseconds(i);
      digitalWrite(pulse2,LOW);    //SPEEED INCREASES UPTO 0.2 ms//
      delayMicroseconds(i);
      a=a+1; 
      i=i-(1200/b1);
      if(i<200)
      {
         i=200;
       }                                                 
       //Serial.println(i);
    }
     
    while(a<(2*(b1/3)))
    {  
       //cw2();
       digitalWrite(pulse2,HIGH);
       delayMicroseconds(i);
       digitalWrite(pulse2,LOW);       //SPEED REMAINS CONSTANT i.e. 0.2 ms//
       delayMicroseconds(i);
       a=a+1; 
       //Serial.println(i);
     }
}   


// HERE OUR MOTOR 3 WILL RUN //
void motor3(float b3)
{ 
   int a=0;  // a is just for a loop//
   // HERE OUR MOTOR2 WILL RUN  CLOCKWISE//
   while(a<(b3/3))                   // We are dividing no of counts in three parts//
   {
      
      digitalWrite(pulse3,HIGH);
      delayMicroseconds(i);
      digitalWrite(pulse3,LOW);    //SPEEED INCREASES UPTO 0.2 ms//
      delayMicroseconds(i);
      a=a+1; 
      i=i-(1200/b3);
      if(i<200)
      {
         i=200;
       }                                                 
       //Serial.println(i);
    }
     
    while(a<(2*(b3/3)))
    {  

       digitalWrite(pulse3,HIGH);
       delayMicroseconds(i);
       digitalWrite(pulse3,LOW);       //SPEED REMAINS CONSTANT i.e. 0.2 ms//
       delayMicroseconds(i);
       a=a+1; 
       //Serial.println(i);
     }
}   
float x10=0;                       //x10 IS COUNTER FOR MOTOR 4//
float x11=0;                       //x11 IS COUNTER FOR MOTOR 4//

void motor4(float x10)
{ 
  int a=0;        // a is just for a loop//
  // HERE OUR MOTOr4 WILL RUN //
  while(a<(x10/3)) // We are dividing no of counts in three parts//
  {
     //cw4();
     digitalWrite(pulse4,HIGH);
     delayMicroseconds(i);
     digitalWrite(pulse4,LOW);    //SPEEED INCREASES UPTO 0.2 ms//
     delayMicroseconds(i);
     a=a+1; 
     i=i-(1200/x10);
     if(i<200)
     {
       i=200;
     }                                                 
   }
   
   while(a<(2*(x10/3)))
   {
     //cw4();
     digitalWrite(pulse4,HIGH);
     delayMicroseconds(i);
     digitalWrite(pulse4,LOW);       //SPEED REMAINS CONSTANT i.e. 0.2 ms//
     delayMicroseconds(i);
     a=a+1; 
     //  Serial.println(i);
    }
}
*/
void loop() {

  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  pwm_value_1= map(pwm_value_1,1000,1800,0,255);
 // Serial.print(pwm_value_1);
 // Serial.print("\t");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  pwm_value_2= map(pwm_value_2,1000,2000,0,255);
 // Serial.print(pwm_value_2);
//  Serial.print("\t");
  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
  pwm_value_3= map(pwm_value_3,1000,1800,0,255);
  Serial.print(pwm_value_3);
//  Serial.print("\t");
  pwm_value_4 = pulseIn(PWM_PIN_4, HIGH);
  pwm_value_4= map(pwm_value_4,1000,1800,0,255);
 // Serial.print(pwm_value_4);
 // Serial.print("\t");
  pwm_value_5 = pulseIn(PWM_PIN_5, HIGH);
  pwm_value_5= map(pwm_value_5,1000,1800,0,255);
 // Serial.print(pwm_value_5);
 // Serial.print("\t");
  pwm_value_6 = pulseIn(PWM_PIN_6, HIGH);
  pwm_value_6= map(pwm_value_6,1000,1800,0,255);
  //Serial.print(pwm_value_6);
 // Serial.print("\t");
  Serial.println();

   int angle=10;
   float degree=(16200/360)*angle; 
   z=(400*degree)/360;

   int angle2=5;
   float degree2=(16200/360)*angle2; 
   float z2=(400*degree2)/360;
   
   float z3=300;
/*
  //Gripper -claw 5
  if(pwm_value_5<120){
       ccw4();
       motor4(z2);
   }
  else if(pwm_value_5>=120 && pwm_value_5<=210){
    }
  else if(pwm_value_5 > 210){
       cw4();
       motor4(z2); 
    }  
 
  //TeleScope - UP/DOWN
  if(pwm_value_1<120){
    tele_down();
    }
  else if(pwm_value_1>=120 && pwm_value_1<=210){
    }
  else if(pwm_value_1 > 210){
    tele_up();
    }

  //Gripper Yaw - Left/right
  if(pwm_value_2<120){
    grip_yaw_right();
    }
  else if(pwm_value_2>=120 && pwm_value_2<=210){
    }
  else if(pwm_value_2 > 210){
    grip_yaw_left();
    }
*/
/*
  //ARM MOTOR 1
  if(pwm_value_3<120){
       ccw1();
       motor_1_run = true;
   }
  else if(pwm_value_3>=120 && pwm_value_3<=210){
           motor_1_run = false;
    }
  else if(pwm_value_3 > 210){
       cw1();
       motor_1_run = true;
    }  
*/
  while(motor_1_run == true){
     
     if(pwm_value_3<120){
       motor_1_dir = true;
      }else motor_1_dir=false;
     
     motor1(z3,motor_1_dir);
  
     if(pwm_value_3>=120 && pwm_value_3<=210){
       motor_1_run = false;
     }
  }
  if(pwm_value_3>=120 && pwm_value_3<=210){
         motor_1_run = false;
  }else  motor_1_run = true;
  
/*
  //ARM MOTOR 2
  if(pwm_value_4<120){
       ccw2();
       motor2(z);
   }
  else if(pwm_value_4>=120 && pwm_value_4<=210){
    }
  else if(pwm_value_4 > 210){
       cw2();
       motor2(z); 
    }   

  //ARM MOTOR 3
  if(pwm_value_6<120){
       ccw3();
       motor3(z3);
   }
  else if(pwm_value_6>=120 && pwm_value_6<=210){
    }
  else if(pwm_value_6 > 210){
       cw3();
       motor3(z3); 
    }   
*/

}

/*
void tele_up()
{
  //For Clock wise motion , in_1 = High , in_2 = Low
  analogWrite(pwm,70);
  
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  
  //Clockwise for .3 secs
  delay(300) ;     
  
  //For brake
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,HIGH) ;
  delay(1) ;
}

void tele_down(){
  
  analogWrite(pwm,70);
  
  //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  delay(300) ;
  
  //For brake
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,HIGH) ;
  delay(1) ;
}

void grip_yaw_right()
{
  //For Clock wise motion , in_1 = High , in_2 = Low
  analogWrite(pwm,100);
  digitalWrite(in_1_g,HIGH) ;
  digitalWrite(in_2_g,LOW) ;
  
  //Clockwise for .3 secs
  delay(300) ;     
 
  //For brake
  digitalWrite(in_1_g,HIGH) ;
  digitalWrite(in_2_g,HIGH) ;
  delay(1) ;
}

void grip_yaw_left(){
  analogWrite(pwm,100);
  //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
  digitalWrite(in_1_g,LOW) ;
  digitalWrite(in_2_g,HIGH) ;
  delay(300) ;
  
  //For brake
  digitalWrite(in_1_g,HIGH) ;
  digitalWrite(in_2_g,HIGH) ;
  delay(1) ;
}

*/
