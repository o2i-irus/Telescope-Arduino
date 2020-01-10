// Motion Control

int RelayControl1 = A0;    // Pan Left
int RelayControl2 = A1;    // Pan Right
int RelayControl3 = A2;    //Tilt Up
int RelayControl4 = A3;    // Tilt Down

const int pwm = 9 ;   //initializing pin 9 as pwm
const int dir =10;    //initializing pin 10 as direction
const int brake=11;   //initializing pin 11 as brake

byte PWM_PIN_1 = 6;   //PAN - Left/Right - RC1
byte PWM_PIN_2 = 7;   //TILT - Up/Down  - RC2
byte PWM_PIN_3 = 8;  // HEIGHT- Up/Down  - RC5

int pwm_value_1=0;
int pwm_value_2=0;
int pwm_value_3=0;

//Zoom Camera pins
int RelayControl5 = A4;   // LED - On/Off
int RelayControl6 = A5;   // ZOOM Camera - On/Off

byte PWM_PIN_4 = 3;     // led/zoom camera - on/off  - RC6
byte PWM_PIN_5 = 4;     // Zoom control -RC3
byte PWM_PIN_6 = 5;     // focus control -RC4

byte FPV_ZOOM_PIN = 0;    // Initializing pin 0 as zoom   (Z)
byte FPV_FOCUS_PIN = 1;   // Initializing pin 1 as focus  (F)
byte FPV_Z_COM_PIN = 2;   // Initializing pin 2 as Common (C) 

int pwm_value_4=0;
int pwm_value_5=0;
int pwm_value_6=0;

// Threshhold values

#define pwm_value_1_min 1000
#define pwm_value_1_mid1 1400
#define pwm_value_1_mid2 1700
#define pwm_value_1_max 2000

#define pwm_value_2_min 1000
#define pwm_value_2_mid1 1300
#define pwm_value_2_mid2 1700
#define pwm_value_2_max 2000

#define pwm_value_3_min 0
#define pwm_value_3_mid1 70
#define pwm_value_3_mid2 170
#define pwm_value_3_max 260

#define pwm_value_4_min 900
#define pwm_value_4_mid1 1500
#define pwm_value_4_mid2 0
#define pwm_value_4_max 2100

#define pwm_value_5_min 900
#define pwm_value_5_mid1 1010
#define pwm_value_5_mid2 1300
#define pwm_value_5_mid3 1750
#define pwm_value_5_max 2100

#define pwm_value_6_min 1000
#define pwm_value_6_mid1 1300
#define pwm_value_6_mid2 1700
#define pwm_value_6_max 2050


void setup()  
{   
  // Motion Control Setup
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(PWM_PIN_3, INPUT);

  //Serial.begin(9600);

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

  // LED PIN
  pinMode(RelayControl5, OUTPUT);
  digitalWrite(RelayControl5,HIGH);  

  //Zoom Focus Camera SetUp
  pinMode(RelayControl6, OUTPUT);
  digitalWrite(RelayControl6,HIGH);  

  pinMode(PWM_PIN_5, INPUT);
  pinMode(PWM_PIN_6, INPUT);
  pinMode(FPV_ZOOM_PIN, OUTPUT);
  pinMode(FPV_FOCUS_PIN, OUTPUT);
  pinMode(FPV_Z_COM_PIN, OUTPUT);
  digitalWrite(FPV_Z_COM_PIN,LOW);
  digitalWrite(FPV_ZOOM_PIN,LOW); 
  digitalWrite(FPV_FOCUS_PIN,LOW); 

}
 
 
void loop()  
{ 
  // Motion Control Loop
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  //Serial.print(pwm_value_1);
  //Serial.print("                      ");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  //Serial.print(pwm_value_2);
  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
  pwm_value_3= map(pwm_value_3,980,2050,0,255);
  //Serial.print("                      ");
  //Serial.print(pwm_value_3);
 // Serial.println("  ");

  //PAN Control
  if(pwm_value_1<=pwm_value_1_mid1 && pwm_value_1>pwm_value_1_min ){
    digitalWrite(RelayControl1,LOW);//(on)
    digitalWrite(RelayControl2,HIGH);  
  //  Serial.print("  PAN-Right  ");
  }else if(pwm_value_1<=pwm_value_1_mid2 && pwm_value_1>pwm_value_1_mid1 ){
  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  }else if(pwm_value_1<=pwm_value_1_max && pwm_value_1>pwm_value_1_mid2 ){
  digitalWrite(RelayControl2,LOW);
  digitalWrite(RelayControl1,HIGH);   
  //Serial.print(" PAN-Left  ");
  }

 //Tilt Control
 if(pwm_value_2<=pwm_value_2_mid1 && pwm_value_2>pwm_value_2_min ){
  digitalWrite(RelayControl3,HIGH);
  digitalWrite(RelayControl4,LOW); 
  //Serial.print("  TILT-UP  ");
  }else if(pwm_value_2<=pwm_value_2_mid2 && pwm_value_2>pwm_value_2_mid1 ){
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);    
  }else if(pwm_value_2<=pwm_value_2_max && pwm_value_2>pwm_value_2_mid2 ){ 
  digitalWrite(RelayControl4,HIGH);  
  digitalWrite(RelayControl3,LOW);  
  //Serial.print(" TILT-DOWN "); 
  }

  //Linear Actuator - Up/Down
  if(pwm_value_3<pwm_value_3_mid1 && pwm_value_3>pwm_value_3_min){
    //Clockwise
    digitalWrite(brake,LOW) ;    
    digitalWrite(dir,HIGH) ;
    analogWrite(pwm,150) ;
//    Serial.print("  Tele UP  ");
  }else if(pwm_value_3>=pwm_value_3_mid1 && pwm_value_3< pwm_value_3_mid2){
      digitalWrite(brake,HIGH) ;
      analogWrite(pwm,0) ;
  }else if(pwm_value_3>=pwm_value_3_mid2 && pwm_value_3< pwm_value_3_max){
    //For Anti Clock-wise motion
     digitalWrite(brake,LOW) ;
     digitalWrite(dir,LOW) ;
     analogWrite(pwm,150) ;
  //   Serial.print("  Tele Down  ");
  }

  //LED toggle
  pwm_value_4 = pulseIn(PWM_PIN_4, HIGH);
  //  Serial.print(pwm_value_4);
  //  Serial.print("                ");
  if(pwm_value_4>pwm_value_4_min && pwm_value_4<pwm_value_4_mid1){
        //Led off
        digitalWrite(RelayControl5,HIGH);   
  }else if(pwm_value_4>=pwm_value_4_mid1 && pwm_value_4<pwm_value_4_max){
        //Led on
        digitalWrite(RelayControl5,LOW);
  } 

  
  //Zoom Focus Camera Loop
  pwm_value_5 = pulseIn(PWM_PIN_5, HIGH);
//  Serial.print(pwm_value_5);
//  Serial.print("                ");

  pwm_value_6 = pulseIn(PWM_PIN_6, HIGH);
//  Serial.print(pwm_value_6);
//  Serial.print("                ");

  //Zoom Control - IN/OUT
   if(pwm_value_5<=pwm_value_5_mid1 && pwm_value_5>pwm_value_5_min){
   digitalWrite(RelayControl6,HIGH);   
    //Zoom camera off
   }else if(pwm_value_5<=pwm_value_5_mid2 && pwm_value_5>pwm_value_5_mid1){
   digitalWrite(RelayControl6,LOW);   
    digitalWrite(FPV_Z_COM_PIN,LOW);
    digitalWrite(FPV_ZOOM_PIN,HIGH);  
    }else if(pwm_value_5>pwm_value_5_mid2 && pwm_value_5<pwm_value_5_mid3 ){
   digitalWrite(RelayControl6,LOW);   
    digitalWrite(FPV_Z_COM_PIN, LOW);
    digitalWrite(FPV_ZOOM_PIN,LOW);    
    }else if(pwm_value_5<=pwm_value_5_max && pwm_value_5>=pwm_value_5_mid3){
   digitalWrite(RelayControl6,LOW);   
    digitalWrite(FPV_Z_COM_PIN,HIGH);
    digitalWrite(FPV_ZOOM_PIN,LOW);         
    }  

  //Focus -IN/OUT
  if(pwm_value_6<=pwm_value_6_mid1 && pwm_value_6>pwm_value_6_min){
   // digitalWrite(FPV_Z_COM_PIN,LOW);
    digitalWrite(FPV_FOCUS_PIN,HIGH);  
    }else if(pwm_value_6>pwm_value_6_mid1 && pwm_value_6<pwm_value_6_mid2 ){
   // digitalWrite(FPV_Z_COM_PIN, LOW);
    digitalWrite(FPV_FOCUS_PIN,LOW);    
    }else if(pwm_value_6>=pwm_value_6_mid2 && pwm_value_6<=pwm_value_6_max){
    digitalWrite(FPV_Z_COM_PIN,HIGH);
    digitalWrite(FPV_FOCUS_PIN,LOW); 
    digitalWrite(FPV_ZOOM_PIN,HIGH);       
    }  
//    Serial.println();

}

