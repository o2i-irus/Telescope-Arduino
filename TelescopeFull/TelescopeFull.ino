/* Relay Control
  Index Arduino
    0 <-> A4;   // [220vAC]IN4: Pan F
    1 <-> A5;   // [220vAC]IN3: Pan R
    2 <-> A6;   // [220vAC]IN2: Tilt F
    3 <-> A7;   // [220vAC]IN1: Tilt R
    4 <-> A3;   // [12vDC]IN1: Thermal Camera Transmitter
    5 <-> A2;   // [5vDC}IN2: Thermal Camera Power
    6 >-> A1;   // [12vDC]IN3; Zoom Camera Transmitter
    7 <-> A0;   // [12vDC]IN4; LED
*/
#define RELAY_TOTAL_CHANNEL 8
#define RELAY_PAN_LEFT_INDEX 0
#define RELAY_PAN_RIGHT_INDEX 1
#define RELAY_TILT_UP_INDEX 2
#define RELAY_TILT_DOWN_INDEX 3
#define RELAY_THERMAL_TRANS_INDEX 4
#define RELAY_THERMAL_CAM_INDEX 5
#define RELAY_ZOOM_TRANS_INDEX 6
#define RELAY_LED_INDEX 7
byte relay_pin[RELAY_TOTAL_CHANNEL] = {A4, A5, A6, A7, A3, A2, A1, A0};
byte relay_value[RELAY_TOTAL_CHANNEL] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

/*RC Channel Pins to Arduino
  Index Channel Arduino Function          RC Switch Name
    0 <--> 1  <--> 7 <-> Linear Actuator  SB
    1 <--> 2  <--> 6 <-> LED              SH
    2 <--> 3  <--> 5 <-> PAN              SA
    3 <--> 4  <--> 4 <-> TILT             SD
    4 <--> 5  <--> 3 <-> Camera Zoom      SC
    5 <--> 6  <--> 8 <-> Camera Focus     S2
    6 <--> 7  <--> 9 <-> Thermal Camera   SF
    7 <--> 8  <--> 10<-> Zoom Camera      S1
*/
#define RC_TOTAL_CHANNEL 8
#define RC_LINEAR_ACTUATOR_INDEX 0
#define RC_LED_INDEX 1
#define RC_PAN_INDEX 2
#define RC_TILT_INDEX 3
#define RC_CAM_ZOOM_INDEX 4
#define RC_CAM_FOCUS_INDEX 5
#define RC_THERMAL_CAM_INDEX 6
#define RC_ZOOM_TRANS_INDEX 7
byte RC_channel_pin[RC_TOTAL_CHANNEL] = {7, 6, 5, 4, 3, 8, 9, 10};
volatile int RC_channel_value[RC_TOTAL_CHANNEL] = {0, 0, 0, 0, 0, 0, 0, 0};
int RC_pulse_min = 980;
int RC_pulse_max = 1995;
volatile  int mapped_data[RC_TOTAL_CHANNEL] = {0, 0, 0, 0, 0, 0, 0, 0};


//LMD18200_Driver -->> 48V DC Motor Driver
byte actuator_pwm_pin   = 11;   //initializing pin 11 as pwm
byte actuator_dir_pin = 12;     //initializing pin 12 as direction
byte actuator_brake_pin = 13;   //initializing pin 13 as brak
byte actuator_pwm_value = 255;

//ZOOM Camera -->> Control pins ZFC
byte FPV_ZOOM_PIN = A10;    // Initializing pin A10 as zoom   (Z)
byte FPV_FOCUS_PIN = A9;   // Initializing pin A9 as focus  (F)
byte FPV_COM_PIN = A8;   // Initializing pin A8 as Common (C)

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

byte prev_led_RC;

void setup() {
  Serial.begin(115200);
  Serial1.begin(19200);
  initRC();
  initRelay();
  initCamera();
  initLinearActuator();
  while (RC_channel_value[0] == 0) {    //Check for RC Connection
    getDataFromRC();
    Serial.println("Connect RC");
  }
}

void loop() {
  getDataFromRC();
  mapRCData();
  printRCData();
  printMappedData();

  activateLinearActuator();
  activateThermalCamera();
  activateZoomCameraTrans();
  activateZoomFocus();
  activatePanTilt();
  activateLED();
  activateLRF();

  writeToRelay();
  Serial.println();
}
