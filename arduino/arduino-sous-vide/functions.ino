float getAverageTemp(DallasTemperature sensors){
  int deviceCount = sensors.getDeviceCount();
  float tempC = 0;
  if (deviceCount > 0){
    for (uint8_t i = 0; i < deviceCount; i++) {
      tempC = tempC + sensors.getTempCByIndex(i);
    }
    tempC = tempC / deviceCount;
  }
  return tempC;
}

int readDial(void){
  return map(analogRead(DIAL_PIN), 0, 1023, 0, TEMP_STEPS) * 5 + MIN_TEMP;
}
