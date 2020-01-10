// Relay Control
int RelayControl1 = A0;    // [12v@C]12VDC:IN1: Led light Power Connector
int RelayControl2 = A1;    // [12v@C]12VDC:IN2: TS832(FPV Zoom Camera Transmitter)
int RelayControl3 = A2;    // [5v@C]12VDC:IN3: Thermal Camera Power Connector 
int RelayControl4 = A3;    // [12v@C]12VDC:IN4: TS832(Thermal Camera Transmitter)
int RelayControl5 = A4;    // [220v@C]5 VDC:IN1: Pan F
int RelayControl6 = A5;    // [220v@C]5 VDC:IN2: Pan R
int RelayControl7 = A6;    // [220v@C]5 VDC:IN3: Tilt F
int RelayControl8 = A7;    // [220v@C]5 VDC:IN4: Tilt R

// RC Pins
byte PWM_PIN_1 = 4;     // RC2 : THERMAL CAMERA 
byte PWM_PIN_2 = 5;     // RC4 : FPV ZOOM CAMERA - FOCUS CONTROL
byte PWM_PIN_3 = 6;     // RC5 : LED ON OFF
byte PWM_PIN_4 = 7;     // RC7 : LINEAR ACTUATOR
byte PWM_PIN_5 = 8;     // RC9 : PAN
byte PWM_PIN_6 = 9;     // RC11 : ZOOM CAMERA
byte PWM_PIN_7 = 10;    // RC12 : TILT
byte PWM_PIN_8 = 3;     // Reserved


//ZOOM Camera -->> Control pins ZFC
byte FPV_ZOOM_PIN = 0;    // Initializing pin 0 as zoom   (Z)
byte FPV_FOCUS_PIN = 1;   // Initializing pin 1 as focus  (F)
byte FPV_Z_COM_PIN = 2;   // Initializing pin 2 as Common (C) 

//LMD18200_Driver -->> 48V DC Motor Driver
const int pwm   = 11;   //initializing pin 11 as pwm
const int dir   = 12;   //initializing pin 12 as direction
const int brake = 13;   //initializing pin 13 as brake

//Variables to store RC Values
unsigned int pwm_value_1=0;
unsigned int pwm_value_2=0;
unsigned int pwm_value_3=0;
unsigned int pwm_value_4=0;
unsigned int pwm_value_5=0;
unsigned int pwm_value_6=0;
unsigned int pwm_value_7=0;
unsigned int pwm_value_8=0;

// Threshhold values

#define pwm_value_1_min 1000
#define pwm_value_1_mid1 1400
#define pwm_value_1_mid2 1700
#define pwm_value_1_max 2000

#define pwm_value_2_min 1000
#define pwm_value_2_mid1 1300
#define pwm_value_2_mid2 1700
#define pwm_value_2_max 2000

#define pwm_value_3_min 900
#define pwm_value_3_mid1 1500
#define pwm_value_3_mid2 0
#define pwm_value_3_max 2100

#define pwm_value_4_min 0
#define pwm_value_4_mid1 70
#define pwm_value_4_mid2 170
#define pwm_value_4_max 260

#define pwm_value_5_min 1000
#define pwm_value_5_mid1 1300
#define pwm_value_5_mid2 1700
#define pwm_value_5_max 2000

#define pwm_value_6_min 900
#define pwm_value_6_mid1 1010
#define pwm_value_6_mid2 1300
#define pwm_value_6_mid3 1750
#define pwm_value_6_max 2100

#define pwm_value_7_min 1000
#define pwm_value_7_mid1 1300
#define pwm_value_7_mid2 1700
#define pwm_value_7_max 2000

#define pwm_value_8_min 1000
#define pwm_value_8_mid1 1300
#define pwm_value_8_mid2 1700
#define pwm_value_8_max 2000

void setup()  
{   

/*  Uncomment below line to diagnose code. Serial.Print Commands display the Input PWM RC Values. */  
  //Serial.begin(9600); //Setting Serial Communication between Serial Monitor and Arduino

  //Setting RC Channels in PWM Input Mode
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(PWM_PIN_3, INPUT);
  pinMode(PWM_PIN_4, INPUT);
  pinMode(PWM_PIN_5, INPUT);
  pinMode(PWM_PIN_6, INPUT);
  pinMode(PWM_PIN_7, INPUT);
  pinMode(PWM_PIN_8, INPUT);

  //Setting Relays INx Pin as Output Pins
  pinMode(RelayControl1, OUTPUT);
  pinMode(RelayControl2, OUTPUT);
  pinMode(RelayControl3, OUTPUT);
  pinMode(RelayControl4, OUTPUT);
  pinMode(RelayControl5, OUTPUT);
  pinMode(RelayControl6, OUTPUT);
  pinMode(RelayControl7, OUTPUT);
  pinMode(RelayControl8, OUTPUT);

  //LMD18200_DRIVER Control Pins
  pinMode(pwm,OUTPUT) ;   //we have to set PWM pin as output
  pinMode(dir,OUTPUT) ;  //Direction pin is set as output
  pinMode(brake,OUTPUT) ;  //Brake pin is set as output

  //FPV Zoom Camera Control Pins
  pinMode(FPV_ZOOM_PIN, OUTPUT);
  pinMode(FPV_FOCUS_PIN, OUTPUT);
  pinMode(FPV_Z_COM_PIN, OUTPUT);

  //Initializing Relays Pin as High(OFF STATE)
  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);  
  digitalWrite(RelayControl5,HIGH);  
  digitalWrite(RelayControl6,HIGH);  
  digitalWrite(RelayControl7,HIGH);  
  digitalWrite(RelayControl8,HIGH);  

  //Initializing LMD18200 Driver Brake Pin as High(Releasing brakes)
  digitalWrite(brake,HIGH) ;

 //Initializing FPV Zoom Camera control pins to LOW( Stable Feed)
  digitalWrite(FPV_Z_COM_PIN,LOW);
  digitalWrite(FPV_ZOOM_PIN,LOW); 
  digitalWrite(FPV_FOCUS_PIN,LOW); 

}
 
 
void loop()  
{ 
  // Reading (PWM) RC Input
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
  //  Serial.print(pwm_value_1);
  //  Serial.print("                      ");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
  //  Serial.print(pwm_value_2);
  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
  pwm_value_3= map(pwm_value_3,980,2050,0,255);
  //  Serial.print("                      ");
  //  Serial.print(pwm_value_3);
   pwm_value_4 = pulseIn(PWM_PIN_4, HIGH);
  //  Serial.print(pwm_value_4);
  //  Serial.print("                ");
  pwm_value_5 = pulseIn(PWM_PIN_5, HIGH);
  //  Serial.print(pwm_value_5);
  //  Serial.print("                ");
  pwm_value_6 = pulseIn(PWM_PIN_6, HIGH);
  //  Serial.print(pwm_value_6);
  //  Serial.print("                ");
  pwm_value_7 = pulseIn(PWM_PIN_7, HIGH);
  //  Serial.print(pwm_value_7);
  //  Serial.print("                ");
  pwm_value_8 = pulseIn(PWM_PIN_8, HIGH);
  //  Serial.print(pwm_value_8);
  //  Serial.print("                ");
  //  Serial.println();

  //Thermal Camera Power Control
  if(pwm_value_1<=pwm_value_1_mid1 && pwm_value_1>pwm_value_1_min ){
      digitalWrite(RelayControl3,HIGH);//(on)
      digitalWrite(RelayControl4,HIGH);  
      //Serial.print("  Thermal Camera Power OFF ");
  }else if(pwm_value_1<=pwm_value_1_max && pwm_value_1>pwm_value_1_mid1 ){
      digitalWrite(RelayControl3,LOW);
      digitalWrite(RelayControl4,LOW);   
      //Serial.print(" Thermal Camera Power ON ");
  }

  //Focus -IN/OUT
  if(pwm_value_2<=pwm_value_2_mid1 && pwm_value_2>pwm_value_2_min){
      //digitalWrite(FPV_Z_COM_PIN,LOW);
      digitalWrite(FPV_FOCUS_PIN,HIGH);  
  }else if(pwm_value_2>pwm_value_2_mid1 && pwm_value_2<pwm_value_2_mid2 ){
      //digitalWrite(FPV_Z_COM_PIN, LOW);
      digitalWrite(FPV_FOCUS_PIN,LOW);    
  }else if(pwm_value_2>=pwm_value_2_mid2 && pwm_value_2<=pwm_value_2_max){
      digitalWrite(FPV_Z_COM_PIN,HIGH);
      digitalWrite(FPV_FOCUS_PIN,LOW); 
      digitalWrite(FPV_ZOOM_PIN,HIGH);       
  }  
  
  //LED toggle
  if(pwm_value_3>pwm_value_3_min && pwm_value_3<pwm_value_3_mid1){
        //Led off
        digitalWrite(RelayControl1,HIGH);   
  }else if(pwm_value_3>=pwm_value_3_mid1 && pwm_value_3<pwm_value_3_max){
        //Led on
        digitalWrite(RelayControl1,LOW);
  } 

  //Linear Actuator - Up/Down
  if(pwm_value_4<pwm_value_4_mid1 && pwm_value_4>pwm_value_4_min){
      //Clockwise
      digitalWrite(brake,LOW);    
      digitalWrite(dir,HIGH);
      analogWrite(pwm,150);
      //Serial.print(" TeleUP ");
 }else if(pwm_value_4>=pwm_value_4_mid1 && pwm_value_4< pwm_value_4_mid2){
      digitalWrite(brake,HIGH);
      analogWrite(pwm,0);
  }else if(pwm_value_4>=pwm_value_4_mid2 && pwm_value_4< pwm_value_4_max){
      //For Anti Clock-wise motion
      digitalWrite(brake,LOW) ;
      digitalWrite(dir,LOW) ;
      analogWrite(pwm,150) ;
     //Serial.print("  Tele Down  ");
  }

  //PAN Control
  if(pwm_value_5<=pwm_value_5_mid1 && pwm_value_5>pwm_value_5_min){
      digitalWrite(RelayControl5,LOW);//(on)
      digitalWrite(RelayControl6,HIGH);  
      //Serial.print("  PAN-Right  ");
  }else if(pwm_value_5<=pwm_value_5_mid2 && pwm_value_5>pwm_value_5_mid1){
      digitalWrite(RelayControl5,HIGH);  
      digitalWrite(RelayControl6,HIGH);  
  }else if(pwm_value_5<=pwm_value_5_max && pwm_value_5>pwm_value_5_mid2){
      digitalWrite(RelayControl5,LOW);
      digitalWrite(RelayControl6,HIGH);   
      //Serial.print(" PAN-Left  ");
  }
 
  //Zoom Control - IN/OUT
   if(pwm_value_6<=pwm_value_6_mid1 && pwm_value_6>pwm_value_6_min){
      digitalWrite(RelayControl2,HIGH);   
      //Zoom camera off
   }else if(pwm_value_6<=pwm_value_6_mid2 && pwm_value_6>pwm_value_6_mid1){
      digitalWrite(RelayControl2,LOW);   
      digitalWrite(FPV_Z_COM_PIN,LOW);
      digitalWrite(FPV_ZOOM_PIN,HIGH);  
    }else if(pwm_value_6>pwm_value_6_mid2 && pwm_value_6<pwm_value_6_mid3 ){
      digitalWrite(RelayControl2,LOW);   
      digitalWrite(FPV_Z_COM_PIN, LOW);
      digitalWrite(FPV_ZOOM_PIN,LOW);    
    }else if(pwm_value_6<=pwm_value_6_max && pwm_value_6>=pwm_value_6_mid3){
      digitalWrite(RelayControl2,LOW);   
      digitalWrite(FPV_Z_COM_PIN,HIGH);
      digitalWrite(FPV_ZOOM_PIN,LOW);         
    }  


 //Tilt Control
 if(pwm_value_7<=pwm_value_7_mid1 && pwm_value_7>pwm_value_7_min){
      digitalWrite(RelayControl7,HIGH);
      digitalWrite(RelayControl8,LOW); 
      //Serial.print("  TILT-UP  ");
  }else if(pwm_value_7<=pwm_value_7_mid2 && pwm_value_7>pwm_value_7_mid1){
      digitalWrite(RelayControl7,HIGH);  
      digitalWrite(RelayControl8,HIGH);    
  }else if(pwm_value_7<=pwm_value_7_max && pwm_value_7>pwm_value_7_mid2 ){ 
      digitalWrite(RelayControl7,HIGH);  
      digitalWrite(RelayControl8,LOW);  
      //Serial.print(" TILT-DOWN "); 
  }
  // Serial.println();

}
