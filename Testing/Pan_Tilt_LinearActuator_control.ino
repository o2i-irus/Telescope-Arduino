int RelayControl1 = 8;    // Pan Left
int RelayControl2 = 9;    // Pan Right
int RelayControl3 = 10;    //Tilt Up
int RelayControl4 = 11;    // Tilt Down

const int pwm = 3 ;   //initializing pin 3 as pwm
const int dir =12;    //initializing pin 4 as direction
const int brake=13;   //initializing pin 5 as brake

byte PWM_PIN_1 = 4;   //PAN
byte PWM_PIN_2 = 5;   //TILT
byte PWM_PIN_3 = 6;

int pwm_value_1=0;
int pwm_value_2=0;
int pwm_value_3=0;
 
void setup()  
{   
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(PWM_PIN_3, INPUT);

  Serial.begin(9600);

  pinMode(RelayControl1, OUTPUT);
  pinMode(RelayControl2, OUTPUT);
  pinMode(RelayControl3, OUTPUT);
  pinMode(RelayControl4, OUTPUT);

  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);  

  pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
  pinMode(dir,OUTPUT) ;  //Direction pin is set as output
  pinMode(brake,OUTPUT) ;  //Brake pin is set as output
  digitalWrite(brake,HIGH) ;

}
 
 
void loop()  
{ 
  
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  Serial.print(pwm_value_1);
  Serial.print("                      ");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  Serial.print(pwm_value_2);
  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
  pwm_value_3= map(pwm_value_3,1000,2000,0,255);
  Serial.print("                      ");
  Serial.print(pwm_value_3);
  Serial.println("  ");

  if(pwm_value_1<=1400 && pwm_value_1>1000 ){
    digitalWrite(RelayControl1,LOW);//(on)
    digitalWrite(RelayControl2,HIGH);  
    Serial.print("  PAN-Right  ");
  }else if(pwm_value_1<=1700 && pwm_value_1>1400 ){

  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  
  }else if(pwm_value_1<=2000 && pwm_value_1>1700 ){
  digitalWrite(RelayControl2,LOW);
  digitalWrite(RelayControl1,HIGH);   
  Serial.print(" PAN-Left  ");

  }

 if(pwm_value_2<=1300 && pwm_value_2>1000 ){
  digitalWrite(RelayControl3,HIGH);
  digitalWrite(RelayControl4,LOW); 

  Serial.print("  TILT-UP  ");
  
  }else if(pwm_value_2<=1700 && pwm_value_2>1300 ){
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);  
    
  }else if(pwm_value_2<=2000 && pwm_value_2>1700 ){ 
  digitalWrite(RelayControl4,HIGH);  
  digitalWrite(RelayControl3,LOW);
  
  Serial.print(" TILT-DOWN "); 
  }

  if(pwm_value_3<70 && pwm_value_3>0){
    //Clockwise
    digitalWrite(brake,LOW) ;    
    digitalWrite(dir,HIGH) ;
    analogWrite(pwm,150) ;
    Serial.print("  Tele UP  ");

  }else if(pwm_value_3>=70 && pwm_value_3< 170){

      digitalWrite(brake,HIGH) ;
      analogWrite(pwm,0) ;

  }else if(pwm_value_3>=170 && pwm_value_3< 260){
    //For Anti Clock-wise motion
     digitalWrite(brake,LOW) ;
     digitalWrite(dir,LOW) ;
     analogWrite(pwm,150) ;
     Serial.print("  Tele Down  ");

  }



}
