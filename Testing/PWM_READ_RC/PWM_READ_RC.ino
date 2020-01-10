byte PWM_PIN_1 = 3;
byte PWM_PIN_2 = 4;
byte PWM_PIN_3 = 5;
byte PWM_PIN_4 = 6;
byte PWM_PIN_5 = 7;
byte PWM_PIN_6 = 8;
byte PWM_PIN_7 = 9;
byte PWM_PIN_8 = 10;
byte PWM_PIN_9 = 11;
byte PWM_PIN_10 = 12; 

int pwm_value_1=0;
int pwm_value_2=0;
int pwm_value_3=0;
int pwm_value_4=0;
int pwm_value_5=0;
int pwm_value_6=0;
int pwm_value_7=0;
int pwm_value_8=0;
int pwm_value_9=0;
int pwm_value_10=0;



void setup() {
  pinMode(PWM_PIN_1, INPUT);
  pinMode(PWM_PIN_2, INPUT);
  pinMode(PWM_PIN_3, INPUT);
  pinMode(PWM_PIN_4, INPUT);
  pinMode(PWM_PIN_5, INPUT);
  pinMode(PWM_PIN_6, INPUT);
  pinMode(PWM_PIN_7, INPUT);
  pinMode(PWM_PIN_8, INPUT);
  pinMode(PWM_PIN_9, INPUT);
  pinMode(PWM_PIN_10, INPUT);
  Serial.begin(9600);
}


void loop() {
  pwm_value_1 = pulseIn(PWM_PIN_1, HIGH);
 // pwm_value_1= map(pwm_value_1,1000,1800,0,255);
  Serial.print(pwm_value_1);
  Serial.print("\t");
  pwm_value_2 = pulseIn(PWM_PIN_2, HIGH);
 // pwm_value_2= map(pwm_value_2,1000,2000,0,255);
  Serial.print(pwm_value_2);
  Serial.print("\t");
  pwm_value_3 = pulseIn(PWM_PIN_3, HIGH);
 // pwm_value_3= map(pwm_value_3,1000,1800,0,255);
  Serial.print(pwm_value_3);
  Serial.print("\t");
  pwm_value_4 = pulseIn(PWM_PIN_4, HIGH);
 // pwm_value_4= map(pwm_value_4,1000,1800,0,255);
  Serial.print(pwm_value_4);
  Serial.print("\t");
  pwm_value_5 = pulseIn(PWM_PIN_5, HIGH);
  //pwm_value_5= map(pwm_value_5,1000,1800,0,255);
  Serial.print(pwm_value_5);
  Serial.print("\t");
  pwm_value_6 = pulseIn(PWM_PIN_6, HIGH);
  //pwm_value_6= map(pwm_value_6,1000,1800,0,255);
  Serial.print(pwm_value_6);
  Serial.print("\t");
  pwm_value_7 = pulseIn(PWM_PIN_7, HIGH);
  //pwm_value_7= map(pwm_value_7,1000,1800,0,255);
  //Serial.print(pwm_value_7);
  Serial.print("\t");
  pwm_value_8 = pulseIn(PWM_PIN_8, HIGH);
  //pwm_value_8= map(pwm_value_8,1000,1800,0,255);
  //Serial.print(pwm_value_8);
  Serial.print("\t");
  pwm_value_9 = pulseIn(PWM_PIN_9, HIGH);
  //pwm_value_9= map(pwm_value_9,1000,1800,0,255);
  //Serial.print(pwm_value_9);
  Serial.print("\t");
  pwm_value_10 = pulseIn(PWM_PIN_10, HIGH);
  //pwm_value_10= map(pwm_value_10,1000,1800,0,255);
  //Serial.print(pwm_value_10);
  Serial.print("\t");
  Serial.println();
  Serial.println();
  delay(200);

}
