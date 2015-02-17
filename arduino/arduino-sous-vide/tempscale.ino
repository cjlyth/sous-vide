#define BOUNCE_LOCK_OUT
#define SCALE_TOGGLE 2

#include <Bounce2.h>

Bounce debouncer = Bounce(); 
boolean celsius = true;

void setupTempScale(void){
  pinMode(SCALE_TOGGLE, INPUT);
  digitalWrite(SCALE_TOGGLE,HIGH);
  debouncer.attach(SCALE_TOGGLE);
  debouncer.interval(5);
}

boolean loopTempScale(String &str) {
  boolean changed = debouncer.update();


  
  if ( changed ) {
       // Get the update value
     int value = debouncer.read();
     if ( value == HIGH) {
       Serial.println("Button released (state 0)");
     } else {
       Serial.println("Button pressed (state 1)");
     }
  }
  if ( debouncer.rose() ) {
    celsius = !celsius;
    str += celsius ? "C" : "F";
    return true;
  }
  return false;
}

//

//
//int buttonState;
//int lastButtonState = LOW;
//long lastDebounceTime = 0;  // the last time the output pin was toggled
//
//
//void checkButton(void) {
//  int reading = digitalRead(SCALE_TOGGLE);
//  if (reading != lastButtonState) {
//    lastDebounceTime = millis();
//  }
//  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
//    if (reading != buttonState) {
//      buttonState = reading;
//      if (buttonState == HIGH) {
//        celsius = !celsius;
//      }
//    }
//  }
//  lastButtonState = reading;
//}

