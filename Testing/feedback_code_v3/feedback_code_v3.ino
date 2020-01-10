/*
******************************************  ATV FEEDBACK SYSTEM *************************************
*  HARDWARE Used ~ 1X ARDUINO MEGA ;2 X 2CH RELAY MODULE(5VDC,12VDC); 1X LRF(TTL); 1X HC12(TTL); 1X MAX3232 SERIAL(CONNECTED TO KEYA CONTROLLER) TO TTL (TTL); 1X THERMAL CAM; 1X TS832; 1X KINECT; 1X LIDAR; 1X KEYA CONTROLLER
*  2CH RELAY MODULE(12V) - TO ON/OFF  LIDAR & KINECT (DUAL CONTROL)
*  2CH RELAY MODULE(5V) - TO ON/OFF TS832 & THERMAL CAMERA (SINGLE CONTROL)
*  LRF - ON/OFF; LASER RANGE FINDER; DISTANCE DATA & ERROR DATA RECV. WITH MODE CHANGING - TTL - SERIAL3 - BOTH(TRANS-RECV)
*  HC12 - FOR COMMUNICATION B/W ATV & GCS -TTL - SERIAL 1 - BOTH(TRANS-RECV)  
*  MAX3232 - FOR COMM. B/W FEEDBACK CONTROLLER & ATV- KEYA CONTROLLER - TTL - SERIAL2 - BOTH(TRANS-RECV)-ALWAYS(ON) 

-CONNECTIONS
  -Relay Module(12V): VCC-5v, IN2-A0, IN1- A1, JDVCC-12V+, GND- BATTERY GND
  -Relay Module(5V): VCC-5v, IN2-A2, IN1- A3, GND-ARDUINO GND, JD-VCC    
  -LRF - VCC-5V, GND-ARDUINO GND, RxD-14, TxD -15
  -HC12 - VCC-5V, GND-ARDUINO GND, RxD-19, TxD -18
  -MAX3232 - VCC-5V, GND-ARDUINO GND, RxD-16, TxD -17

- BAUD RATE
  -LRF = 19200
  -HC12 = 9600
  -MAX3232 = 9600

-Flags
  -THERMAL_CAM_ON
  -LIDAR_ON
  -KINECT_ON
  -LRF_ON
*/

//Libraries
#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include <inttypes.h>
#include <stdint.h>
const int ledPin =  13;

/*****************************
 * Thermal Camera, Lidar, Kinect & LRF 
 * ACK Frame variables
******************************/
#define ack_start_byte 0x01;
#define ack_stop_byte 0x00;
#define ack_frame_length 3

unsigned char ack_buffer[ack_frame_length];

unsigned char thermal_camera_flag=LOW;
unsigned char lidar_flag=LOW;
unsigned char kinect_flag=LOW;
unsigned char lRF_flag=LOW;

unsigned char thermal_camera_value;
unsigned char lidar_value;
unsigned char kinect_value;
unsigned char lRF_value;

// Relay Control Pins
int RelayControl1 = A0;    // [12v@C]12VDC:IN1: Kinect Power Connector
int RelayControl2 = A1;    // [12v@C]12VDC:IN2: Lidar Power Connector
int RelayControl3 = A2;    // [5v@C]12VDC:IN3(IN1): Thermal Camera Power Connector 
int RelayControl4 = A3;    // [12v@C]12VDC:IN4(IN2): TS832(Thermal Camera Transmitter)


/**********************************************
          KEYA CONTROLLER VARIABLES
**********************************************/

#define All_volts "?V"
#define Internal_volts "?V 1"
#define Main_battery_volts "?V 2"

#define read_temp "?T"
#define read_temp_internal_ic "?T tm"
#define read_temp_side1 "?T t1"
#define read_temp_side2 "?T t2"

#define read_encoder_speed "?S"
#define read_motor_speed "?BS"

#define read_status_flag "?FS"
#define read_fault_flag "?FF"

#define read_motor_amps "?A"
#define read_motor1_amps "?A 1"
#define read_motor2_amps "?A 2"

#define read_battery_amps "?BA"

#define read_motor1_power_applied "?P 1"
#define read_motor2_power_applied "?P 2"

#define keya_start_byte " "

unsigned char volts_function_id 0x0A
unsigned char temp_function_id 0x0B
unsigned char speed_function_id 0x0C
unsigned char amps_function_id 0x0D
/*****************************************
             HC12 Variables
*****************************************/
#define HC12_buffer_length 10
#define HC12_LRF_buffer_length 3
unsigned char HC12_buffer[HC12_buffer_length];
unsigned char HC12_LRF_Module_id = 5;
unsigned char HC12_LRF_DATA_INFO=0;
unsigned int HC12_LRF_DATA_VALUE=0;

/*******************************************************************
                              LRF constants and Functions
*****************************************************************/
#define BAUD 19200                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

#define buffer_length 10
#define min_time 2

unsigned char incomingByte=0;
unsigned int m_dist=0;

//Slave ID
#define Slave_ID 0x10

//For single ranging
#define range_inst 0x83
#define range_insdes 0x00
#define range_checksum 0x7D
#define range_dl 4

//For Baud Rate 9600
#define setbaud_inst 0x9E
#define setbaud_insdes0 0x90
#define setbaud_insdes1 0x00
#define setbaud_insdes2 0x00
#define setbaud_insdes3 0x04
#define setbaud_checksum 0xCE
#define setbaud_dl 7

//For comm test
#define comtest_inst 0xC0
#define comtest_checksum 0x40
#define comtest_dl 3

//For Stop Ranging
#define srange_inst 0x84
#define srange_checksum 0x7C
#define srange_dl 3

//DISTANCE DATA PARAMS
#define dist_inst 0x01
#define dist_data_valid 0x7F 
unsigned char dist_MSB=0;
unsigned char dist_LSB=0;
unsigned char dist_checksum=0;

//Error Information
#define err_inst 0xE0
unsigned char err_inf=0;
unsigned char err_checksum=0;

unsigned char buffer[buffer_length ];
unsigned char buffer_r[buffer_length ];
int temp = 0;

// functions to send data
//Sending Baud Rate Info
void send_Setbaud() {
  Serial.println("Baud Packet Init");
  temp = -1;
  buffer[0] = Slave_ID;
  buffer[1] = setbaud_inst;
  buffer[2] = setbaud_insdes0;
  buffer[3] = setbaud_insdes1;
  buffer[4] = setbaud_insdes2;
  buffer[5] = setbaud_insdes3;
  buffer[6] = setbaud_checksum;
 Serial3.write(buffer, setbaud_dl);  digitalWrite(ledPin, LOW);
}

//Sending Communication Test packet:0x60 Received if okay
void send_commtest() {
  Serial.println("Comm test Packet Init");
  temp = -1;
  buffer[0] = Slave_ID;
  buffer[1] = comtest_inst;
  buffer[2] = comtest_checksum;
  Serial3.write(buffer, comtest_dl);  digitalWrite(ledPin, LOW);
}

//Sending commands for single ranging
void send_ranging() {
 // Serial.println("TX DATA"); 
 digitalWrite(ledPin, LOW);
  temp = -1;
  buffer[0] = Slave_ID;
  buffer[1] = range_inst;
  buffer[2] = range_insdes;
  buffer[3] = range_checksum;
  Serial3.write(buffer, range_dl);
   digitalWrite(ledPin, LOW);
}

//Sending commands to stop ranging
void stop_ranging() {
  temp = -1;
  buffer[0] = Slave_ID;
  buffer[1] = srange_inst;
  buffer[2] = srange_checksum;

  do {
    while (!(UCSR1A & (1 << UDRE1)));
    UDR3 = buffer[++temp];
  } while (temp < srange_dl);
 
}

unsigned char dist_recieve (void)
{
 /* while (!(UCSR3A) & (1 << RXC3));                // wait while data is being received
  return UDR3;        */                           // return 8-bit data
  if (Serial3.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial3.read(); }
     return incomingByte;
}

// function to receive data
void dist_read(){
  int t=0;
  if (Serial3.available()) {
    while(Serial3.available()>0)
    {  digitalWrite(ledPin, LOW);
       buffer_r[t]=dist_recieve();
       t++;
     }
   }

   if(buffer_r[0]!=Slave_ID){
     Serial.println("______ ModuleMissing ____");
     HC12_LRF_DATA_INFO=5;
     HC12_LRF_DATA_VALUE=2;
    }else
    if(buffer_r[2]>127){
        Serial.println("Incorrect Data");
     HC12_LRF_DATA_INFO=6;
     HC12_LRF_DATA_VALUE=3;

    }else 
    {
       m_dist=((256*buffer_r[3])+buffer_r[4])*0.5; // MSB(0x0H - Max =0x04=4) + LSB(Max=0xFF=255)
       Serial.print("Measured Distance: ");
       Serial.print(m_dist);
       Serial.println(" metres");  
       HC12_LRF_DATA_INFO=7;
       HC12_LRF_DATA_VALUE=m_dist;
      digitalWrite(ledPin, HIGH);
      //delay(200);
    }
    
    HC12_buffer[0]=HC12_LRF_Module_id;
    HC12_buffer[1]=HC12_LRF_DATA_INFO;
    HC12_buffer[2]=HC12_LRF_DATA_VALUE;
    
    Serial1.write(HC12_buffer,HC12_LRF_buffer_length );  //digitalWrite(ledPin, LOW);
    Serial.println("DATA TRANSMITTED TO HC MODULE");
    delay(50);

}
/**************************************************************************************************/

/**********************************KEYA FUNCT.******************************************/
//Sending commands for voltage
void send_volts() {
 // Serial.println("TX DATA"); 
 digitalWrite(ledPin, LOW);
  temp = -1;
  buffer[0] = keya_start_byte;
  buffer[1] = Main_battery_volts;
  Serial2.write(buffer, 2);
   digitalWrite(ledPin, LOW);
}
//Sending commands for Temperature
void send_Temp() {
 // Serial.println("TX DATA"); 
 digitalWrite(ledPin, LOW);
  temp = -1;
  buffer[0] = keya_start_byte;
  buffer[1] = read_temp;
  Serial2.write(buffer, 2);
   digitalWrite(ledPin, LOW);
}

//Sending commands for motor speed
void send_Motor_speed() {
 // Serial.println("TX DATA"); 
 digitalWrite(ledPin, LOW);
  temp = -1;
  buffer[0] = keya_start_byte;
  buffer[1] = read_motor_speed;
  Serial2.write(buffer, 2);
   digitalWrite(ledPin, LOW);
}

//Sending commands for motor amps
void send_Motor_current() {
 // Serial.println("TX DATA"); 
 digitalWrite(ledPin, LOW);
  temp = -1;
  buffer[0] = keya_start_byte;
  buffer[1] = read_motor_amps;
  Serial2.write(buffer, 2);
   digitalWrite(ledPin, LOW);
}

unsigned char keya_data_recieve (void)
{
  if (Serial2.available() > 0) {
    incomingByte = Serial2.read(); }
     return incomingByte;
}

// function to receive data
void keya_data_read(unsigned char func_id){
  int t=0;
  if (Serial2.available()) {
    while(Serial2.available()>0)
    {  digitalWrite(ledPin, LOW);
       buffer_r[t]=keya_data_recieve();
       t++;
     }
   }
   Serial.print(buffer_r[1]); 
}

/********************************** MAINS ***************************************/

void setup() {
  // initialize both serial ports:
  Serial.begin(9600);
  Serial.println("setting Devices");

  Serial1.begin(9600);  //HC12
  Serial2.begin(9600); //MAX3232
  Serial3.begin(19200); //LRF

  delay(50);
  pinMode(ledPin, OUTPUT);

  //Setting Relays INx Pin as Output Pins
  pinMode(RelayControl1, OUTPUT);
  pinMode(RelayControl2, OUTPUT);
  pinMode(RelayControl3, OUTPUT);
  pinMode(RelayControl4, OUTPUT);

  //Initializing Relays Pin as High(OFF STATE)
  digitalWrite(RelayControl1,HIGH);  
  digitalWrite(RelayControl2,HIGH);  
  digitalWrite(RelayControl3,HIGH);  
  digitalWrite(RelayControl4,HIGH);  
 
}

unsigned int byte_rec()
{
  if (Serial1.available()) {
    int inByte = Serial1.read();
    return inByte;
  }
}

void loop() {
  int temp=0;
  thermal_camera_value=0;
  lidar_value=0;
  kinect_value=0;
  lRF_value=0;
    
 //Keya battery Voltage data// 
  send_volts();
  keya_data_read(volts_function_id);

 //Keya Temp data  //
  send_Temp();
  keya_data_read(temp_function_id);

 //Motor Speed data  // 
  send_Motor_speed();
  keya_data_read(speed_function_id);

 //Motor Current data  // 
  send_Motor_current();
  keya_data_read(amps_function_id);

  //Reading Data from ground feedback circuit/Box
  while(Serial1.available()){
    ack_buffer[temp]=byte_rec();
    temp++;
    }

  //Checkinf for switches
  if(ack_buffer[0]==ack_start_byte && ack_buffer[2]==ack_stop_byte){
    thermal_camera_value=ack_buffer[1]&0x80;
    lidar_value=ack_buffer[1]&0x20;
    kinect_value=ack_buffer[1]&0x08;
    lRF_value=ack_buffer[1]&0x02;

    if(thermal_camera_value==0x80){thermal_camera_flag=LOW;}else{thermal_camera_flag=HIGH;}
    if(lidar_value==0x20){lidar_flag=LOW;}else{lidar_flag=HIGH;}
    if(kinect_value==0x08){kinect_flag=LOW;}else{kinect_flag=HIGH;}
    if(lRF_value==0x02){lRF_flag=LOW;}else{lRF_flag=HIGH;}
      
    }
    delay(50);

    //If LRF swtich on-->> Read LRF Distance Data  
    if(lRF_flag==HIGH){
        //Laser Range Finder
        delay(50);
        send_ranging();
        delay(50);
        dist_read();
    }

    if(kinect_flag==HIGH){
      //KINECT ON
       digitalWrite(RelayControl1,LOW); 
    }else{
      //KINECT OFF
       digitalWrite(RelayControl1,HIGH); 
      }
    if(lidar_flag==HIGH){
      //Lidar power Relay on
      digitalWrite(RelayControl2,LOW); 
    }else {
    //Lidar power relay off
    digitalWrite(RelayControl2,HIGH); 
    }
    
    if(thermal_camera_flag==HIGH){
      //Relay On - 2 Channel - Thermal camera + Transmitter 
      digitalWrite(RelayControl3,LOW); 
      digitalWrite(RelayControl4,LOW); 
    }else{ 
      //Relay Off - 2 Channel - Thermal camera + Transmitter
      digitalWrite(RelayControl3,HIGH); 
      digitalWrite(RelayControl4,HIGH); 
    }
    
}
