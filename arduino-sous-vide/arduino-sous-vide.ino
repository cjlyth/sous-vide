/*
 * http://milesburton.com/Main_Page?title=Dallas_Temperature_Control_Library#Code.2FLibrary
 * http://arduino-info.wikispaces.com/LCD-Blue-I2C
 *
 * https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
 *
 * http://hmario.home.xs4all.nl/arduino/LiquidCrystal_I2C/
 *
 * http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 *
 * http://milesburton.com/Dallas_Temperature_Control_Library
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MIN_TEMP 90
#define MAX_TEMP 140
#define ONE_WIRE_BUS 2
#define HEAT_RELAY  7    

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  lcd.begin(16,2);  
  lcd.backlight();
  pinMode(HEAT_RELAY, OUTPUT);
  lcd.clear();
}

void loop(void)
{ 
  sensors.requestTemperatures();
  lcd.setCursor(0,0);
  float tempC = 0;
  float tempF = 0;
  for (uint8_t i = 0; i < sensors.getDeviceCount(); i++)
  {
    tempC = tempC + sensors.getTempCByIndex(i);
  }
  tempC = tempC / sensors.getDeviceCount();
  tempF = DallasTemperature::toFahrenheit(tempC);
  lcd.print(sensors.getDeviceCount());
  lcd.print(" @ ");
  lcd.print(tempC);  
  lcd.print(" C ");
  lcd.setCursor(4,1);
  lcd.print(tempF);
  lcd.print(" F ");

  if (tempF < MAX_TEMP)
  {
    digitalWrite(HEAT_RELAY,HIGH);
  }
  else if (tempF > MIN_TEMP) 
  {
    digitalWrite(HEAT_RELAY,LOW);
  }
  delay(5000);
}



