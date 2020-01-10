//LRF
#define slave_ID 0x10
#define buffer_length 10
unsigned char buffer_s[buffer_length];
unsigned char buffer_r[buffer_length];
unsigned int distance = 0;
int temp = 0;

//For single ranging
#define range_inst 0x83
#define range_insdes 0x00
#define range_checksum 0x7D
#define range_dl 4
//For Stop Ranging
#define srange_inst 0x84
#define srange_checksum 0x7C
#define srange_dl 3

void activateLRF() {
  getLRFData();
  if (buffer_r[0] != slave_ID) {
    Serial.print("ModuleMissing");
  }
  else if (buffer_r[1] == 1) {
    if (buffer_r[2] > 127) {
      Serial.print("Object too close");
    }
    else {
      distance = ((256 * buffer_r[3]) + buffer_r[4]) * 0.5; // MSB(0x0H - Max =0x04=4) + LSB(Max=0xFF=255)
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.print(" metres");
    }
  }
  else {
    Serial.print("\tInstructions Not found"); // FOR ERROR STATUS
  }
  delay(50);
  send_ranging();

  delay(50);
}

void getLRFData() {
  int t = 0;
  if (Serial1.available()) {
    while (Serial1.available() > 0)    {
      buffer_r[t++] = Serial1.read();
    }
  }
}

//Sending commands for single ranging
void send_ranging() {
  // Serial.println("TX DATA");
  temp = -1;
  buffer_s[0] = slave_ID;
  buffer_s[1] = range_inst;
  buffer_s[2] = range_insdes;
  buffer_s[3] = range_checksum;
  Serial1.write(buffer_s, range_dl);
}

//Sending commands to stop ranging
void stop_ranging() {
  temp = -1;
  buffer_s[0] = slave_ID;
  buffer_s[1] = srange_inst;
  buffer_s[2] = srange_checksum;

  do {
    while (!(UCSR1A & (1 << UDRE1)));
    UDR1 = buffer_s[++temp];
  } while (temp < srange_dl);
}

void setup() {
  Serial.begin(19200);
}

void loop() {
  activateLRF();
}
