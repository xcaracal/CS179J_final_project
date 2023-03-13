#ifndef __RELOAD_H__
#define __RELOAD_H__
#include "holder.h"

const int reloadButton = 4;

enum Reload_States {Reload_Idle, Reload_High};

int Reload_TickFct(int state) {
  switch(state) {
    case Reload_Idle:
      if(digitalRead(reloadButton) == HIGH) {
        state = Reload_High;
      }
    break;
    case Reload_High:
      if(digitalRead(reloadButton) == LOW) {
        state = Reload_Idle;
      }
    break;
    default:
    state = Reload_Idle;
    break;
  }
  
  switch(state){
    case Reload_Idle:
      digitalWrite(reloadPin, HIGH);
    break;
    case Reload_High:
      Serial.println("RELOAD");
      digitalWrite(reloadPin, LOW);
    break;
    default:
    break;
  }
  return state;
}

#endif //__RELOAD_H__