int RelayControl1 = 8;    // Pan Left
int RelayControl2 = 9;    // Pan Right
int RelayControl3 = 10;    //Tilt Up
int RelayControl4 = 11;    // Tilt Down

byte PWM_PIN_1 = 4;   //PAN
byte PWM_PIN_2 = 5;   //TILT

int pwm_value_1=0;
int pwm_value_2=0;

 
void setup()  
{   
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);

  Serial.begin(9600);

  pinMode(RelayControl1, OUTPUT);
  pinMode(RelayControl2, OUTPUT);
  pinMode(RelayControl3, OUTPUT);
  pinMode(RelayControl4, OUTPUT);

  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);  

  
}
 
 
void loop()  
{ 
  
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  Serial.print(pwm_value_1);
  Serial.print("                      ");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  Serial.print(pwm_value_2);
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

}
