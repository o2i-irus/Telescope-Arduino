byte PWM_PIN_1 = 3;
byte PWM_PIN_2 = 4;
byte FPV_ZOOM_PIN = 5;
byte FPV_FOCUS_PIN = 6;
byte FPV_Z_COM_PIN = 7;

int pwm_value_1=0;
int pwm_value_2=0;

void setup() {
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(FPV_ZOOM_PIN, OUTPUT);
  pinMode(FPV_FOCUS_PIN, OUTPUT);
  pinMode(FPV_Z_COM_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(FPV_Z_COM_PIN,LOW);
  digitalWrite(FPV_ZOOM_PIN,LOW); 
  digitalWrite(FPV_FOCUS_PIN,LOW); 

}


void loop() {
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  Serial.print(pwm_value_1);
  Serial.print("                ");

  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  Serial.print(pwm_value_2);
  Serial.print("                ");
  
  if(pwm_value_1<=1300){
    digitalWrite(FPV_Z_COM_PIN,LOW);
    digitalWrite(FPV_ZOOM_PIN,HIGH);  
    }else if(pwm_value_1>1300 && pwm_value_1<1750 ){
    digitalWrite(FPV_Z_COM_PIN, LOW);
    digitalWrite(FPV_ZOOM_PIN,LOW);    
    }else if(pwm_value_1>=1750){
    digitalWrite(FPV_Z_COM_PIN,HIGH);
    digitalWrite(FPV_ZOOM_PIN,LOW);         
    }  

  if(pwm_value_2<=1300){
   // digitalWrite(FPV_Z_COM_PIN,LOW);
    digitalWrite(FPV_FOCUS_PIN,HIGH);  
    }else if(pwm_value_2>1300 && pwm_value_2<1700 ){
   // digitalWrite(FPV_Z_COM_PIN, LOW);
    digitalWrite(FPV_FOCUS_PIN,LOW);    
    }else if(pwm_value_2>=1700){
    digitalWrite(FPV_Z_COM_PIN,HIGH);
    digitalWrite(FPV_FOCUS_PIN,LOW); 
    digitalWrite(FPV_ZOOM_PIN,HIGH);  
       
    }  

  Serial.println();
}
