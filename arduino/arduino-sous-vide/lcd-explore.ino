

//https://github.com/thomasfredericks/Bounce-Arduino-Wiring/archive/master.zip
#include <Wire.h>
#include <OneWire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define DIAL_PIN 3


// Ideal temp for a steak 55c
#define MIN_TEMP 40
#define MAX_TEMP 90
#define DEBOUNCE_DELAY 50

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const int TEMP_STEPS = ((MAX_TEMP - MIN_TEMP) / 10) * 2;

void setup(void)
{
  Serial.begin(9600);
  setupRoomTemp();
  setupTempScale();
  lcd.begin(16,2);  
  lcd.backlight();
  lcd.clear();
  lcd.noCursor();

}

void loop(void)
{ 
  lcd.home();
  
  String tempScale;
  if (loopTempScale(tempScale)) {
    lcd.setCursor(0,0);
    lcd.print(tempScale);
  }
  
  String strRoomTemp;
  if (loopRoomTemp(strRoomTemp)){
    lcd.setCursor(0,1);
    lcd.print(strRoomTemp);
  }
  
  lcd.setCursor(15,0);
}



