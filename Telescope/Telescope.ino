/* Relay Control
  Index Arduino
    0 <-> A6;   // [220vAC]IN4: Pan F
    1 <-> A5;   // [220vAC]IN3: Pan R
    2 <-> A4;   // [220vAC]IN2: Tilt F
    3 <-> A3;   // [220vAC]IN1: Tilt R
    4 <-> A2;   // [12vDC]IN1: Thermal Camera Transmitter
    5 <-> A1;   // [12vDC]IN2: Zoom Camera Transmitter
    6 >-> A0;   // [12vDC]IN3: LED
*/
#define RELAY_TOTAL_CHANNEL 7
#define RELAY_PAN_LEFT_INDEX 0
#define RELAY_PAN_RIGHT_INDEX 1
#define RELAY_TILT_UP_INDEX 2
#define RELAY_TILT_DOWN_INDEX 3
#define RELAY_THERMAL_TRANS_INDEX 4
#define RELAY_ZOOM_TRANS_INDEX 5
#define RELAY_LED_INDEX 6
byte relay_pin[RELAY_TOTAL_CHANNEL] = {A6, A5, A4, A3, A2, A1, A0};
byte relay_value[RELAY_TOTAL_CHANNEL] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

/*RC Channel Pins to Arduino
  Index Channel   Nano    Function          (Taranis) (RadioLink)
    0 <--> 1  <--> 12 <-> Linear Actuator      SB         C            2-way
    1 <--> 2  <--> 11 <-> LED                  SH         H            1-way
    2 <--> 3  <--> 10 <-> PAN                  SA         E            2-way
    3 <--> 4  <--> 09 <-> TILT                 SD         g            2-way
    4 <--> 5  <--> 08 <-> Camera Zoom          SC         VR(A)        Pot
    5 <--> 6  <--> 07 <-> Camera Focus         S2         VR(C)        Pot
    6 <--> 7  <--> 06 <-> Thermal Camera       SF         A            1-way
    7 <--> 8  <--> 05 <1->Zoom Camera          S1         B            1-way
*/
#define RC_TOTAL_CHANNEL 8
#define RC_LINEAR_ACTUATOR_INDEX 0
#define RC_LED_INDEX 1
#define RC_PAN_INDEX 2
#define RC_TILT_INDEX 3
#define RC_CAM_ZOOM_INDEX 7
#define RC_CAM_FOCUS_INDEX 5
#define RC_THERMAL_TRANS_INDEX 6
#define RC_ZOOM_TRANS_INDEX 4
byte RC_channel_pin[RC_TOTAL_CHANNEL] = {12, 11, 10, 9, 8, 7, 6, 5};
volatile int RC_channel_value[RC_TOTAL_CHANNEL] = {0, 0, 0, 0, 0, 0, 0, 0};
int RC_pulse_min = 980;
int RC_pulse_max = 1995;
volatile  int mapped_data[RC_TOTAL_CHANNEL] = {0, 0, 0, 0, 0, 0, 0, 0};


//LMD18200_Driver -->> 48V DC Motor Driver
byte actuator_pwm_pin   = 3;   //initializing pin 11 as pwm
byte actuator_dir_pin = 4;     //initializing pin 12 as direction
byte actuator_brake_pin = 2;   //initializing pin 13 as brak
byte actuator_pwm_value = 255;

//ZOOM Camera -->> Control pins ZFC
byte FPV_ZOOM_PIN = 0;    // Initializing pin A10 as zoom   (Z)
byte FPV_FOCUS_PIN = 1;   // Initializing pin A9 as focus  (F)
byte FPV_COM_PIN = 13;   // Initializing pin A8 as Common (C)

byte prev_led_RC;

void setup() {
  Serial.begin(115200);
  initRC();
  initRelay();
  initCamera();
  initLinearActuator();
  while (RC_channel_value[0] == 0) {    //Check for RC Connection
    getDataFromRC();
    printRCData();
    Serial.println("Connect RC");
  }
}

void loop() {
  getDataFromRC();
  mapRCData();
//  printRCData();
  printMappedData();

  activateLinearActuator();
  activateThermalCamera();
  activateZoomCameraTrans();
  activateZoomFocus();
  activatePanTilt();
  activateLED();

  writeToRelay();
  Serial.println();
}
