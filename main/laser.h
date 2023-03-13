#ifndef __LASER_H__
#define __LASER_H__

//#include "wifi.h"
#include "holder.h"

int LASER_OUTPUT = 9;
int BUTTON_INPUT = 3;

enum Laser_States { Laser_Init, Laser_Depress, Laser_Press1, Laser_Press2, Laser_Wait };

int Laser_TickFct(int state) {
  switch (state) {
    case Laser_Init:
      state = Laser_Depress;
      Serial.println("test");
      break;
    case Laser_Depress:
       if (digitalRead(BUTTON_INPUT) == HIGH) state = Laser_Press1;
       Serial.println("test2");
      break;
    case Laser_Press1:
      state = Laser_Press2;
      break;
    case Laser_Press2:
      state = Laser_Wait;
      break;
    case Laser_Wait:
      if (digitalRead(BUTTON_INPUT) == LOW) state = Laser_Depress;
      break;
    default:
      state = Laser_Init;
      break;
  }

  switch (state) {
    case Laser_Init:
    case Laser_Depress:
    case Laser_Wait:
      digitalWrite(LASER_OUTPUT, LOW);
      digitalWrite(shootPin, LOW);
      break;
    case Laser_Press1:
      digitalWrite(LASER_OUTPUT, HIGH);
      digitalWrite(shootPin, HIGH);
      break;
    case Laser_Press2:
      digitalWrite(LASER_OUTPUT, HIGH);
      Serial.println("SHOOT");
      break;
    default:
      break;
  }
  
  return state;
}

#endif //__LASER_H__
