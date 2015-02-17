#define ROOM_TEMP_PIN 3

OneWire roomTempOneWire(ROOM_TEMP_PIN);
DallasTemperature roomTempSensors(&roomTempOneWire);

float roomTemperature = 0.0;

void setupRoomTemp(void){
  roomTempSensors.begin();
  roomTempSensors.setResolution(9);
}

boolean loopRoomTemp(String &str) {
    if (roomTempUpdate()){
      str += roomTemperature;
      str.remove(str.length() - 1);
      return true;
    } else {
      return false;
    }
}

boolean roomTempUpdate(void){
  roomTempSensors.requestTemperatures();
  float nTemp = getAverageTemp(roomTempSensors);
  if (abs(roomTemperature-nTemp) > 0.1) {
    roomTemperature = nTemp;
    return true;
  } else {
    return false;
  }
}

