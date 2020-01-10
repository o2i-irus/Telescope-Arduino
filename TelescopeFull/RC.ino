void getDataFromRC() {
  for (int i = 0; i < RC_TOTAL_CHANNEL; i++) {
    RC_channel_value[i] = pulseIn(RC_channel_pin[i], HIGH);
    if (RC_channel_value[i] == 0) {
      Serial.println("Check Receiver Connection");
      initRelay();
      initLinearActuator();
      getDataFromRC();
    }
  }
  prev_led_RC = mapped_data[RC_LED_INDEX];
}

void printRCData() {
  for (int i = 0; i < RC_TOTAL_CHANNEL; i++) {
    Serial.print(RC_channel_value[i]);
    Serial.print("\t");
  }
}

void mapRCData() {
  for (int i = 0; i < RC_TOTAL_CHANNEL; i++) {
    if (RC_channel_value[i] != 0)
      mapped_data[i] = map(RC_channel_value[i], RC_pulse_min, RC_pulse_max, 0, 5);
  }
}

void printMappedData() {
  for (int i = 0; i < RC_TOTAL_CHANNEL; i++) {
    Serial.print(mapped_data[i]);
    Serial.print("\t");
  }
}
