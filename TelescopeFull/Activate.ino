void activateLinearActuator() {
  if (mapped_data[RC_LINEAR_ACTUATOR_INDEX] < 2) {
    digitalWrite(actuator_brake_pin, LOW);
    digitalWrite(actuator_dir_pin, HIGH);
    analogWrite(actuator_pwm_pin, actuator_pwm_value);
  }
  else if (mapped_data[RC_LINEAR_ACTUATOR_INDEX] > 3) {
    digitalWrite(actuator_brake_pin, LOW);
    digitalWrite(actuator_dir_pin, LOW);
    analogWrite(actuator_pwm_pin, actuator_pwm_value);
  }
  else {
    digitalWrite(actuator_brake_pin, HIGH);
    analogWrite(actuator_pwm_pin, 0);
  }
}

void activateThermalCamera() {
  if (mapped_data[RC_THERMAL_CAM_INDEX] > 3) {
    relay_value[RELAY_THERMAL_CAM_INDEX] = LOW;
    relay_value[RELAY_THERMAL_TRANS_INDEX] = LOW;
  }
  else {
    relay_value[RELAY_THERMAL_CAM_INDEX] = HIGH;
    relay_value[RELAY_THERMAL_TRANS_INDEX] = HIGH;
  }
}

void activateZoomCameraTrans() {
  if (mapped_data[RC_ZOOM_TRANS_INDEX] > 3)
    relay_value[RELAY_ZOOM_TRANS_INDEX] = LOW;
  else
    relay_value[RELAY_ZOOM_TRANS_INDEX] = HIGH;
}

void activateZoomFocus() {
  //Zoom
  if (mapped_data[RC_CAM_ZOOM_INDEX] < 2) {         //Zoom In
    digitalWrite(FPV_COM_PIN, LOW);
    digitalWrite(FPV_ZOOM_PIN, HIGH);
    //    Serial.print("Zoom In ");
  }
  else if (mapped_data[RC_CAM_ZOOM_INDEX] > 3) {      //Zoom Out
    digitalWrite(FPV_COM_PIN, HIGH);
    digitalWrite(FPV_ZOOM_PIN, LOW);
    //    Serial.print("Zoom Out ");
  }

  //Focus
  else if (mapped_data[RC_CAM_FOCUS_INDEX] < 2) {         //Focus 1
    digitalWrite(FPV_COM_PIN, LOW);
    digitalWrite(FPV_ZOOM_PIN, LOW);
    digitalWrite(FPV_FOCUS_PIN, HIGH);
    //    Serial.print("Focus 1");
  }
  else if (mapped_data[RC_CAM_FOCUS_INDEX] > 3) {         //Focus 2
    digitalWrite(FPV_COM_PIN, HIGH);
    digitalWrite(FPV_ZOOM_PIN, HIGH);
    digitalWrite(FPV_FOCUS_PIN, LOW);
    //    Serial.print("Focus 2");
  }

  else {
    digitalWrite(FPV_COM_PIN, LOW);
    digitalWrite(FPV_ZOOM_PIN, LOW);
    digitalWrite(FPV_FOCUS_PIN, LOW);
  }
}

void activatePanTilt() {
  //PAN
  if (mapped_data[RC_PAN_INDEX] < 2) {
    relay_value[RELAY_PAN_LEFT_INDEX] = HIGH;
    relay_value[RELAY_PAN_RIGHT_INDEX] = LOW;
  }
  else if (mapped_data[RC_PAN_INDEX] > 3) {
    relay_value[RELAY_PAN_LEFT_INDEX] = LOW;
    relay_value[RELAY_PAN_RIGHT_INDEX] = HIGH;
  }
  else {
    relay_value[RELAY_PAN_LEFT_INDEX] = HIGH;
    relay_value[RELAY_PAN_RIGHT_INDEX] = HIGH;
  }

  //TILT
  if (mapped_data[RC_TILT_INDEX] < 2) {
    relay_value[RELAY_TILT_UP_INDEX] = LOW;
    relay_value[RELAY_TILT_DOWN_INDEX] = HIGH;
  }
  else if (mapped_data[RC_TILT_INDEX] > 3) {
    relay_value[RELAY_TILT_UP_INDEX] = HIGH;
    relay_value[RELAY_TILT_DOWN_INDEX] = LOW;
  }
  else {
    relay_value[RELAY_TILT_UP_INDEX] = HIGH;
    relay_value[RELAY_TILT_DOWN_INDEX] = HIGH;
  }
}

void activateLED() {
  if (mapped_data[RC_LED_INDEX] > 3 && mapped_data[RC_LED_INDEX] != prev_led_RC) {
    relay_value[RELAY_LED_INDEX] = !relay_value[RELAY_LED_INDEX];
  }
}

void writeToRelay() {
  for (int i = 0; i < RELAY_TOTAL_CHANNEL; i++) {
    digitalWrite(relay_pin[i], relay_value[i]);
  }
}
