const int pwm = 3 ;   //initializing pin 3 as pwm
const int dir =4;    //initializing pin 4 as direction
const int brake=5;   //initializing pin 5 as brake
byte PWM_PIN_3 = 6;

int pwm_value_3=0;


void setup()
{
  pinMode(PWM_PIN_3, INPUT);
  pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
  pinMode(dir,OUTPUT) ;  //Direction pin is set as output
  pinMode(brake,OUTPUT) ;  //Brake pin is set as output
  digitalWrite(brake,HIGH) ;
 
}

void loop()
{

  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
  pwm_value_3= map(pwm_value_3,1100,2000,0,255);

  if(pwm_value_3<90){
    //Clockwise
    digitalWrite(brake,LOW) ;    
    digitalWrite(dir,HIGH) ;
    analogWrite(pwm,150) ;

  }else if(pwm_value_3>=90 && pwm_value_3< 200){

      digitalWrite(brake,HIGH) ;
      analogWrite(pwm,0) ;

  }else {
    //For Anti Clock-wise motion
     digitalWrite(brake,LOW) ;
     digitalWrite(dir,LOW) ;
     analogWrite(pwm,150) ;
  }
}

