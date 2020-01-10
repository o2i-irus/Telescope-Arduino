#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include <inttypes.h>
#include <stdint.h>
const int ledPin =  13;
#define BAUD 19200                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

#define buffer_length 10
#define min_time 2

unsigned char incomingByte = 0;
unsigned int m_dist = 0;

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
unsigned char dist_MSB = 0;
unsigned char dist_LSB = 0;
unsigned char dist_checksum = 0;

//Error Information
#define err_inst 0xE0
unsigned char err_inf = 0;
unsigned char err_checksum = 0;

unsigned char buffer[buffer_length ];
unsigned char buffer_r[buffer_length ];
int temp = 0;

void setup() {
  Serial.begin(9600);
  Serial1.begin(19200);
  Serial.println("setting Devices");
  delay(100);
  pinMode(ledPin, OUTPUT);
}


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
  Serial1.write(buffer, setbaud_dl);  digitalWrite(ledPin, LOW);
}

//Sending Communication Test packet:0x60 Received if okay
void send_commtest() {
  Serial.println("Comm test Packet Init");
  temp = -1;
  buffer[0] = Slave_ID;
  buffer[1] = comtest_inst;
  buffer[2] = comtest_checksum;
  Serial1.write(buffer, comtest_dl);  digitalWrite(ledPin, LOW);
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
  Serial1.write(buffer, range_dl);
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
    UDR1 = buffer[++temp];
  } while (temp < srange_dl);

}

// function to receive data
unsigned char dist_recieve (void)
{
  /* while (!(UCSR1A) & (1 << RXC1));                // wait while data is being received
    return UDR1;        */                           // return 8-bit data
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();
  }
  return incomingByte;
}

void dread() {
  int t = 0;

  if (Serial1.available()) {
    //  Serial.println("incomming");
    while (Serial1.available() > 0)
    { digitalWrite(ledPin, HIGH);
      buffer_r[t] = dist_recieve();
      t++;
    }
  }
  /*//Packet
     while(t>-1){
      Serial.println(buffer_r[t-1]);
      buffer_r[t-1]=0;
      t--;
      }*/

  if (buffer_r[0] != Slave_ID) {
    Serial.println("______ ModuleMissing ____");
  } else if (buffer_r[1] == 1) {
    if (buffer_r[2] > 127) {
      Serial.println("Incorrect Data");
    } else
    {
      m_dist = ((256 * buffer_r[3]) + buffer_r[4]) * 0.5; // MSB(0x0H - Max =0x04=4) + LSB(Max=0xFF=255)
      Serial.print("Measured Distance: ");
      Serial.print(m_dist);
      Serial.println(" metres");
    }
  } else {
    Serial.println("Instructions Not found"); // FOR ERROR STATUS
  }
}

void loop()
{
  // send_Setbaud();
  delay(50);
  // send_commtest();
  dread();
  delay(50);
  send_ranging();
  // delay(1000);
  // dread();
}


